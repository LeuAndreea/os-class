#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
bool isLetter(char c){
	if ( ( c >= 65 && c <= 90) || ( c >= 97 && c <= 122))
		return true;
	return false;

}

int main(int argc, char *argv[]){
	
	int wordCount = 0;
	int file=open(argv[1], O_RDONLY);
	int lineNumber = 1;
	
	char ch1[1], ch2[1];

	
	printf("Numbers of words per line: \n");

	read(file, ch1, 1);
	while ( read(file, ch2, 1) !=0){

		if ( isLetter(ch1[0]) ){
			if ( ch2[0] == '\n'){	

				wordCount++;
				
				printf("%d : %d \n",lineNumber,wordCount);
				wordCount=0;
				lineNumber++;
			}

			else if ( !isLetter(ch2[0]) )
				       wordCount++;	

		}
		
		//considering the case of multiple empty lines
		else if ( ch1[0] == '\n')
			if ( ch2[0] == '\n'){
				printf("%d : %d \n",lineNumber,wordCount);
				lineNumber++;
			}
		
		ch1[0]=ch2[0];

	}

	
	//considering the case when last line ends in special character
	//and is not counted
	lseek(file, -2, SEEK_END);

	read(file, ch1, 1);

	if (!isLetter(ch1[0]))
		printf("%d : %d \n", lineNumber, wordCount);
	
	return 0;
}
