#Read a directory name from std input and count the lines of all its files
# and all the files of its subdirectory

shopt -s globstar
wc -l $1/**/*.txt
