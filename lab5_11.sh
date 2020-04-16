#n files are given
#print the name of the file containing the max nb of lines,
#and print the nb of lines as well


maxNbOfWords=0
for f in $*; do

	nbOfWords=`awk '	{i=0;
	        nbOfWords=0;
		while (i < FNR) {
			nbOfWords += NF;
			i++;
		}} END {printf nbOfWords;}' $f` 
	if [ $nbOfWords -gt $maxNbOfWords ]
	then
		maxNbOfWords=$nbOfWords
		file=$f
	fi


done

echo $file $nbOfWords



