for f in $*; do
echo $f
awk '
	BEGIN {sum=0; linesWtihNbs =0; linesWithoutnbs=0 }

	{	
	nbFound=0
	for (i=1; i<=NF; i++){
		if ( $i == ($i + 0)){
		     sum+=$i;
		     nbFound=1;
		}
		     
	
	}
	if (nbFound==1)
		linesWithNbs+=1
	else
		linesWithoutNbs+=1
	}	

	END {	printf "sum is " sum"\n" ; 
		if (linesWithoutNbs==0) printf "linesWithNbs/linesWithoutNbs=" linesWithNbs "/0\n" 
		else printf "linesWithNbs/linesWithoutNbs =" linesWithNbs/linesWithoutNbs"\n";  }' $f
done
