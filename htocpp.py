#!/usr/bin/python

from os import listdir

ipath = 'inc/'
ifile = 'cea-rand.h'
opath = 'lib/'
classes = []
total_fns = 0

with open(ipath+ifile, 'r') as f:
	cls = []
	# Wait for first class line.
	state = 'c'
	for line in f:
		line = line.strip()
		#print('{0} in state {1}'.format(line[:10],state))
		# Is this line a class line?
		if state is 'c' and line.startswith('class'):
			line = line.split(None, 2)
			cls.append(line[1])
			state = 'b'
		elif state is 'b' and line == '{':
			state = 'f'
		elif state is 'f':
		 	if line.endswith(');') and not line.startswith('//'):
				# Found a function. Split into 'return_type ' (with space) and 'name(args)'.
				total_fns += 1
				if line.startswith(cls[0] + '('):
					# Constructor - no type so just use empty string.
					cls.append(('',line))
				else:
					# Regular function
					cls.append((line.split(None,1)[0] + ' ', line.split(None,1)[1]))
			elif line == '{':
				# Nested class / struct
				state = 'n'
			elif line == '};':
				# End of class!
				classes.append(cls)
				cls = []
				# Go back into 'class' mode...
				state = 'c'
		elif state is 'n' and line == '};':
			# Nested class / struct. Can deal with, but will ignore for now.
			# This only fixes one level - dang.
			state = 'f'
		
print('Scanned {0} and found {1} classes totalling {2} member functions.'.format(ipath+ifile, len(classes), total_fns))
print('Building .cpp files...')

for cls in classes:
	cname = cls[0]
	fname = cname.lower() + '.cpp'

	if fname in listdir(opath):
		print('File {0} already exists. Skipping.'.format(fname))
	else:
		print('Creating {0} for class {1}.'.format(fname, cname))

		with open(opath + fname, 'w') as f:
			f.write('// {0} generated automatically from {1} by htocpp.py\n'.format(fname.capitalize(), ifile))
			f.write('\n')
			#f.write('#include <cea.h>\n')
			f.write('#include <cea-rand.h>\n')
			f.write('\n')
			f.write('namespace cea\n')
			f.write('{')
			for fn in cls[1:]:
				t,body = fn
				f.write('\n\t{0}{1}::{2}\n'.format(t, cname, body.rstrip(';')))
				f.write('\t{\n\t}\n')
			f.write('}\n')
