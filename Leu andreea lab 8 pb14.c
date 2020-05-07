/*Count the numbers of characters on a line 
(using only the read function as a restriction) */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>


int main (int argc, char *argv[]){

	int characterCount=0;
	int file=open(argv[1], O_RDONLY);
	int lineNumber=1;

	char ch[1];

	printf("Number of characters per line: \n");
	
	while ( read(file, ch, 1) !=0){
		if ( ch[0] == '\n'){
			printf("%d : %d\n",lineNumber++, characterCount);
			characterCount=0;
		}
		else
			characterCount++;
	
	}	
}
