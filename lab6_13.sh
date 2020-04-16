# a file is given
# create a directory with the following files:
#0.txt contatining all the words from the file starting with 0
#..
#0.txt conatining all the words starting with 9
#the files need to be sorted


mkdir dictionary
cd dictionary
for i in {0..9}
do
	
	awk -v nb=$i '{regex="^"nb".*"; for(i=1; i<=NF; i++) { if ($i ~ regex ) { print $i} } }' ../$1 | sort -d >> $i.txt
		
done
