#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    //creating server and client pipes
    if (mkfifo("SERVER",0666) < 0){
        perror("Error creating SERVER!");
        return 0;
    }

    if (mkfifo("CLIENT",0666) < 0){
        perror("Error creating client!");
        return 0;
    }

    //opening the pipes
    int pipe_server= open("SERVER", O_WRONLY );
    int pipe_client= open("CLIENT", O_RDONLY );
    
    
    
    fflush(stdin);
    
    //getting file name from user
    char file_name[20];
    size_t size;
    size =read(pipe_client, file_name,20);


    //composing the instruction for counting words
    //+redirecting output to client
    char instruction[15]= "wc -w ";
    strncat(instruction, file_name, size);
    strcat(instruction," >> SERVER ");

    //had to do it this way, redirectin stderr did not send full error
    if(system(instruction) > 0)
	    write(pipe_server,"Error opening file!\n",20);

  
    //deleting links
    remove("SERVER");
    remove("CLIENT");
    //closing pipes
    close(pipe_server);
    close(pipe_client);

    //return 0;
}
