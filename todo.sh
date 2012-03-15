#!/bin/bash
# Scan source base for lines containing // TODO
# and compile a list to be inserted into the
# target file.
if [ $# -ne 1 ]; then
    echo "Usage: `basename $0` target-file"
    exit 1
else
    target="$1"
fi

directories='Cea/ tests/'

list=$(grep -r TODO $directories | sed -e 's/\/\/ TODO//' -e 's/^/+ /')
# Here we escape unescaped _ and * with \ - so no accidental emphasis.
list=$(echo "$list" | sed -e 's/\([^\\]\)_/\1\\_/g')
list=$(echo "$list" | sed -e 's/\([^\\]\)\*/\1\\\*/g')

# Appends list under a todo list heading to file f.
output()
{
    echo 'Todo List' >> $f
    echo '---------' >> $f
    echo  >> $f
    echo "$list" >> $f
}

if [ -e $target ]; then
    if [ $(grep -c 'Todo List' $target) -gt 0 ]; then
        # At least 1 todo list heading found. Delete everything after it!
        delete_from=$(grep -m 1 -n 'Todo List' $target | sed -e 's/:.*$//')
        temp_target='/var/tmp/temp_'$target''
        sed -e ''$delete_from',$d' $target > $temp_target
        f=$temp_target
        output
        mv -f $temp_target $target
    else
        # No todo list found - append this one.
        echo >> $target
        f=$target
        output
    fi
else
    # No target - make one with the todo list in.
    f=$target
    output
fi
