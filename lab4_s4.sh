#A word and n files are given as parammeters.
#Werite the word in front of every lowercase letter you find.


for  ((i=2; $i<=$#;i++))
do
	sed -i 's/\([a-z]\)/'"$1"'\1/g' ${!i}
done
