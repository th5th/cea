#!/usr/bin/python
from sys import argv, exc_info, exit
from os import listdir

_,_,gen = argv[0].rpartition('/')
path = argv[1]

project = 'cea'
omain = 'all.cpp'
oheader = omain.replace('.cpp', '.hpp')
oexec = omain.replace('.cpp', '')
ocmakelists = 'CMakeLists.txt'

failure_msg = 'Test failed.'
success_msg = 'Test succeeded.'

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
    f.write('// {0} generated automatically from test files in {1} by {2}.\n'.format(oheader.capitalize(), path, gen))
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
    f.write('// {0} generated automatically from test files in {1} by {2}.\n'.format(omain.capitalize(), path, gen))
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
        f.write('\ttest_failed = {0};\n\n'.format(fn))
        f.write('\tstd::cout << "Test {0}: ";\n'.format(fn))
        f.write('\tif(!test_failed)\n'.format(fn))
        f.write('\t\tstd::cout << "{0}" << std::endl;\n'.format(success_msg))
        f.write('\telse\n')
        f.write('\t\tstd::cout << "{0}" << std::endl;\n\n'.format(failure_msg))
        f.write('\toverall_failed |= test_failed;\n\n')

    f.write('\treturn overall_failed;\n')
    f.write('}')
    
# Finally, remetamake (!) cmakelists file.
with open(path+ocmakelists, 'w') as f:
    f.write('# {0} generated automatically from test files in {1} by {2}.\n'.format(ocmakelists.capitalize(), path, gen))
    f.write('\n')
    f.write('include_directories(${PROJECT_SOURCE_DIR})\n')
    f.write('\n')
    add_exec_cmd = 'add_executable({0} {1}'.format(oexec, omain)
    for fle in files:
        add_exec_cmd += (' ' + fle)
    add_exec_cmd += ')\n'
    f.write(add_exec_cmd)

exit(0)
