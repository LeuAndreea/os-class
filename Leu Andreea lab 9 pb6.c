
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	
	int i, id=1;
	char c= 96;

	//creating a process for every letter
	while (c < 122){
		if (id != 0){
			c++;
			id =fork();
		}
		else
			break;
	}
	//checking for both lowercase and uppercase
	for (i=0; argv[1][i] ; (argv[1][i] == c) || (argv[1][i] == c - 32)  ? i++ : *argv[1]++);
	
	printf("Letter %c : %d times\n",c,i);

	return 0;
}

		
