#Read a directory name from std input and change the extension txt to ascii
# for all its files and files from subdirectories

shopt -s globstar
for f in $1/**/*.txt; do
mv -- "$f" "${f%.txt}.ascii"
done
