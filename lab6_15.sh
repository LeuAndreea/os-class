#Se dă un fișier cu studenții grupei ordonați în funcție de media notelor primite la sesiunea din iarna. 
#Dându-se pentru fiecare student notele la cele 5 examene din vară (în fișierul 'notevara') 
#să se actualizeze fișierul inițial și să se afișeze studenții care vor primi bursă (media peste 8.50).



cat notevara.txt | sort -d -o notevara.txt
cat noteiarna.txt | sort -d -o noteiarna.txt
nbOfLines=`wc -l notevara.txt | cut -c 1`
i=1
while [ $i -le $nbOfLines ]
do
	summerGrade=0
	j=2
	while [ $j -le 6 ]
	do
		grade=$(sed -n "$i"'p' notevara.txt | cut -d " " -f$j)
		summerGrade=$(( $summerGrade + $grade ))	
		j=$(( $j + 1 ))
	done
	

	summerGrade=$(bc <<< "scale=2; $summerGrade/5")
	
	winterGrade=$(sed -n "$i"'p' noteiarna.txt | cut -d " " -f2)

	finalGrade=$(bc <<< "scale=2; ($summerGrade + $winterGrade)/2")
	echo "$finalGrade"	

	sed -i "$i"'s/'"$winterGrade"'/'"$finalGrade"'/' noteiarna.txt
	
	i=$(( $i + 1))

done

awk '{ if ($2 > 8.50) print $1; }' noteiarna.txt



