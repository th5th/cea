#!/usr/bin/python
from sys import argv, exc_info, exit
from os import listdir
from os.path import abspath, basename

_,_,gen = argv[0].rpartition('/')
path = abspath(argv[1])
pretty_path = basename(path) + '/'
path = path + '/'

# Target definitions.
project = 'cea'
omain = 'all_tests.cpp'
oheader = omain.replace('.cpp', '.hpp')
oexec = omain.replace('.cpp', '')
ocmakelists = 'CMakeLists.txt'

# Messages to cout from the test binary.
failure_msg = ' + Test failed.'
success_msg = ' + Test succeeded.'

# Function to easily add various testing functionality
# without making enormous test_xxx.cpp files by putting
# all that stuff into static libraries.
def cmake_lib_lines(libname, execname):
    line1 = 'add_library({0} STATIC {0}.cpp)\n'.format(libname)
    line2 = 'target_link_libraries({0} {1})\n'.format(execname, libname)
    return [line1, line2]

# Any special targets (test libraries) to
# manually add to CMakeLists.txt.
cmake_extra = cmake_lib_lines("kstest", oexec)

def get_fn(fl):
    with open(path+fl, 'r') as f:
        for line in f:
            # Found a function
            if line.strip() == ('bool ' + fl[:-4] + '()'):
                return line.strip()

files = [fl for fl in listdir(path) if fl.startswith('test_') and fl.endswith('.cpp')]

# Use filter to cut out files without functions, then map to get the functions.
files = filter(get_fn, files)
test_fns = map(get_fn, files)

# Write to oheader
with open(path+oheader, 'w') as f:
    guard = '{0}'.format(oheader.upper().replace('.','_'))
    f.write('// {0} generated automatically from test files in {1} by {2}.\n'.format(oheader.capitalize(), pretty_path, gen))
    f.write('#ifndef {0}\n'.format(guard))
    f.write('#define {0}\n'.format(guard))
    f.write('\n')
    for fn in test_fns:
        f.write(fn + ';\n')
    f.write('\n')
    f.write('#endif // {0}\n'.format(guard))

# ADD NEW BOOL TO MAKE OUTPUT READ RIGHT
# Write to omain
with open(path+omain, 'w') as f:
    f.write('// {0} generated automatically from test files in {1} by {2}.\n'.format(omain.capitalize(), pretty_path, gen))
    f.write('\n')
    f.write('#include <iostream>\n')
    f.write('#include "{0}"\n'.format(oheader))
    f.write('\n')
    f.write('int main(int argc, char* argv[])\n')
    f.write('{\n')
    f.write('\tbool test_failed = false;\n')
    f.write('\tbool overall_failed = false;\n\n')

    for fn in test_fns:
        # Trim the unnecessary type from the front.
        fn = fn[5:]
        f.write('\tstd::cout << "Test {0}:" << std::endl;\n'.format(fn))
        f.write('\ttest_failed = {0};\n'.format(fn))
        f.write('\tif(!test_failed)\n'.format(fn))
        f.write('\t\tstd::cout << "{0}" << std::endl;\n'.format(success_msg))
        f.write('\telse\n')
        f.write('\t\tstd::cout << "{0}" << std::endl;\n\n'.format(failure_msg))
        f.write('\toverall_failed |= test_failed;\n\n')

    f.write('\treturn overall_failed;\n')
    f.write('}')
    
# Finally, remetamake (!) cmakelists file.
with open(path+ocmakelists, 'w') as f:
    f.write('# {0} generated automatically from test files in {1} by {2}.\n'.format(ocmakelists.capitalize(), pretty_path, gen))
    f.write('\n')
    f.write('include_directories(${PROJECT_SOURCE_DIR})\n')
    f.write('\n')
    f.write('add_executable(\n');
    f.write('\t{0}\n'.format(oexec))
    f.write('\t{0}\n'.format(omain))
    for fle in files:
        f.write('\t{0}\n'.format(fle))
    f.write(')\n\n')
    for line in cmake_extra:
        f.write(line)

exit(0)
