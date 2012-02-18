#!/usr/bin/python
from sys import argv, exc_info, exit
from os import listdir

gen = argv[0]
path = argv[1]

project = 'cea'
omain = 'all_tests.cpp'
oheader = omain.replace('.cpp', '.h')
oexec = omain.replace('.cpp', '')
ocmakelists = 'CMakeLists.txt'

failure_msg = 'failed.'
success_msg = 'succeeded.'

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
	guard = '__{0}'.format(oheader.upper().replace('.','_'))
	f.write('// {0} generated automatically from test files in {1} by {2}.\n'.format(oheader.capitalize(), path, gen))
	f.write('\n')
	f.write('#ifndef {0}\n'.format(guard))
	f.write('#define {0}\n'.format(guard))
	f.write('\n')
	for fn in test_fns:
		f.write(fn + ';\n')
	f.write('\n')
	f.write('#endif\n')

# Write to omain
with open(path+omain, 'w') as f:
	f.write('// {0} generated automatically from test files in {1} by {2}.\n'.format(omain.capitalize(), path, gen))
	f.write('\n')
	f.write('#include <iostream>\n')
	f.write('#include "{0}"\n'.format(oheader))
	f.write('\n')
	f.write('int main(int argc, char* argv[])\n')
	f.write('{\n')
	f.write('\tbool return_val = 1;\n')
	for fn in test_fns:
		# Trim the unnecessary type from the front.
		fn = fn[5:]
		f.write('\tstd::cout << "Test {0}: ";\n'.format(fn))
		f.write('\tif(!(return_val = {0}))\n'.format(fn))
		f.write('\t\tstd::cout << "{0}" << std::endl;\n'.format(success_msg))
		f.write('\telse\n')
		f.write('\t\tstd::cout << "{0}" << std::endl;\n\n'.format(failure_msg))
	f.write('\treturn return_val;\n')
	f.write('}')
	
# Finally, remetamake (!) cmakelists file.
with open(path+ocmakelists, 'w') as f:
	f.write('# {0} generated automatically from test files in {1} by {2}.\n'.format(ocmakelists.capitalize(), path, gen))
	f.write('\n')
	f.write('include_directories(${PROJECT_SOURCE_DIR}/inc)\n')
	f.write('link_directories(${PROJECT_SOURCE_DIR}/bin)\n')
	f.write('\n')
	add_exec_cmd = 'add_executable({0} {1}'.format(oexec, omain)
	for fle in files:
		add_exec_cmd += (' ' + fle)
	add_exec_cmd += ')\n'
	f.write(add_exec_cmd)
	f.write('set_target_properties({0} PROPERTIES COMPILE_FLAGS "--std=c++0x")\n'.format(oexec))
	f.write('target_link_libraries({0} {1})\n'.format(oexec, project))

exit(0)
