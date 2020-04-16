#A directory name is given as parameter
#Print all the binary files name from it and its subdirectories.

for d in $*; do
	shopt -s globstar
	for f in $d/**/*.bin; do
		echo $f | sed 's/.*\/\(.*\).bin/\1/'
	done
 
done

