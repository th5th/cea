#!/usr/bin/python
path = 'tests/'
project = 'cea'
omain = 'all_tests.cpp'
oheader = omain.replace('.cpp', '.h')
oexec = omain.replace('.cpp', '')
ocmakelists = 'CMakeLists.txt'

failure_msg = 'Function {0} returned failure.'
success_msg = 'Function {0} returned success.'

from os import listdir

files = [f for f in listdir(path) if f.startswith('test_') and f.endswith('.cpp')]

test_fns = []

for fle in files:
	with open(path+fle, 'r') as f:
		fns_found = 0
		for line in f:
			line = line.strip()
			# Found a function
			if line == ('bool ' + fle[:-4] + '()'):
				if fns_found == 0:
					test_fns.append(line) 
					fns_found += 1

		# Non-compliant
		if fns_found < 1:
			print('File {0} found to contain no compliant functions. Functions must have the same name as the file, be of return type bool, and take no arguments. Skipping file.'.format(fle))
			files.remove(fle)
		elif fns_found > 1:
			print('File {0} found to contain more than one compliant function. Only the first one will be used in the main test function.'.format(fle))
			files.remove(fle)

# Write to oheader
with open(path+oheader, 'w') as f:
	guard = '__{0}'.format(oheader.upper().replace('.','_'))
	f.write('// {0} generated automatically from test files in {1} by gentests.py\n'.format(oheader.capitalize(), path))
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
	f.write('// {0} generated automatically from test files in {1} by gentests.py\n'.format(omain.capitalize(), path))
	f.write('\n')
	f.write('#include <iostream>\n')
	f.write('#include "{0}"\n'.format(oheader))
	f.write('\n')
	f.write('int main(int argc, char* argv[])\n')
	f.write('{\n')
	for fn in test_fns:
		# Trim the unnecessary type from the front.
		fn = fn[5:]
		f.write('\tif({0})\n'.format(fn))
		f.write('\t\tstd::cout << "{0}" << std::endl;\n'.format(failure_msg).format(fn))
		f.write('\tif(!{0})\n'.format(fn))
		f.write('\t\tstd::cout << "{0}" << std::endl;\n\n'.format(success_msg).format(fn))
	f.write('\treturn 0;\n')
	f.write('}')
	
# Finally, remetamake (!) cmakelists file.
with open(path+ocmakelists, 'w') as f:
	f.write('# {0} generated automatically from test files in {1} by gentests.py\n'.format(ocmakelists.capitalize(), path))
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

		
	
