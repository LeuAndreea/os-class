#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

int main()
{
    //creating the server-client pipe
    int status;

    pid_t pid;

    int fd[2];
    pipe(fd);

    pid = fork();
    //child will be the client
    if (pid == 0)
    {
        char *file_name = NULL;
        ;
        size_t size, line_size;

        line_size = getline(&file_name, &size, stdin);
        write(fd[1], file_name, line_size - 1);

        //making sure both processea re not waiting to read at the samee time
        sleep(1);

        //reading result
        char output[40];
        size = read(fd[0], &output, 40);
        write(2, output, size);

        exit(-1);
    }

    else
    {
        printf("Enter the file name:");

        char file_name[10];
        size_t size;
        //reading file name from client
        size = read(fd[0], &file_name, 30);

        //composing the instruction for counting lines
        char instruction[15] = "wc -l ";
        strncat(instruction, file_name, size);
        strcat(instruction, " &");

        //redirecting output to pipe
        dup2(fd[1], 1);
        dup2(fd[1], 2);
        system(instruction);
    }

    while (wait(&status) != -1);

    return 0;
}