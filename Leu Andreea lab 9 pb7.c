#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[]){
	int i,sum=0,id=0,childrenStatus,cube=0;
  	
	//allocating memory for array of numbers
	int *arr = malloc(sizeof(int) * (argc-1));
	
	//converting command line args into ints
	for (i=1; i<argc; i++){
		arr[i-1]=atoi(argv[i]);
	}
	
	i=-1;
	while (i<argc-2){
		if (id == 0){
			//child process
			i++;
			id = fork();		
		}	
		else{
			//parent waiting for the children results to come in
			while((childrenStatus = wait(&sum))>0);
			break;	
		}
   	}	

	//computing the cube and the new sum
	cube=arr[i]*arr[i]*arr[i];
	sum=sum/255+cube;
 
	if (i!=0){
		//passing value to parent
		exit(sum);
	
   	}
   	else
		//init process showing result
		printf("Sum is %d\n",sum);

   	return 0;

}
