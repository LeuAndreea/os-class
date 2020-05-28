#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    //opening file pipes
    int pip_server =open("SERVER",O_RDONLY );
    int pip_client =open("CLIENT",O_WRONLY ) ;

  
    fflush(stdin);
   
  
    //getting file name from the client
    printf("Please introduce a file name: ");
    
    char *file_name=NULL;
    size_t size,line_size;
    line_size=getline(&file_name,&size,stdin);

    fflush(stdin);
    write(pip_client,file_name,line_size-1);

    //getting back nb of lines from server
    char message[50];
    size=read(pip_server,&message,50);

    write(1,message,size);

    close(pip_server);
    close(pip_client);
}
