#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

bool isLetter(char c)
{
    if (((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122)))
        return true;
    return false;
}

bool isNumber(char c)
{
    if ((c >= 48) && (c <= 57))
        return true;
    return false;
}

int main()
{
    pid_t pid;

    //creating pipe for 1-2 on the diagram
    int fd1_2[2];
    pipe(fd1_2);

    pid = fork();
    
    //child  process for linest starting with letters
    if (pid == 0)
    {
        //closing writing end for child
        close(fd1_2[1]);

        char lines_letters[300] = {'\0'};
        char line[30];
        size_t size;

        while ((size = read(fd1_2[0], &line, 30)) > 0)
            strncat(lines_letters, line, size);
       
        printf("Lines starting with letters:\n");
        printf("%s", lines_letters);

        exit(-1);
    }
    //parent code
    else
    {
        //closing reading end for parent
        close(fd1_2[0]);

        //creating pipe for 1-3 on the diagram
        int fd1_3[2];
        pipe(fd1_3);
        pid = fork();

        //child process for lines starting with numbers
        if (pid == 0)
        {
            //closing writing end for the child
            close(fd1_3[1]);

            char lines_numbers[300] = {'\0'};
            char line[30];
            size_t size;

            while ((size = read(fd1_3[0], &line, 30)) > 0)
                strncat(lines_numbers, line, size);
            
            printf("Lines starting with numbers: \n");
            printf("%s", lines_numbers);

            exit(-1);
        }

        //more parent code
        else
        {
            //closing reading end for the  parent
            close(fd1_3[0]);

            //creating pipe for 1-4
            int fd1_4[2];
            pipe(fd1_4);
            pid = fork();
           
            //child process for lines starting with other characters
            if (pid == 0)
            {
                //closing writing end for child
                close(fd1_4[1]);

                char lines_others[300] = {'\0'};
                char line[30];
                size_t size;

                while ((size = read(fd1_4[0], &line, 30)) > 0)
                    strncat(lines_others, line, size);
                

                printf("Lines starting with other characters: \n");
                printf("%s", lines_others);

                exit(-1);
            }

            else
            {
                //closing reading end for parent
                close(fd1_4[0]);

                int status;
                size_t line_size, size;
                char *line = NULL, first_char;
                line_size = getline(&line, &size, stdin);
                
                while (line[0] != '\n')
                {
                    first_char = line[0];

                    if (isLetter(first_char))
                        write(fd1_2[1], line, line_size);
                    else if (isNumber(first_char))
                        write(fd1_3[1], line, line_size);
                    else
                        write(fd1_4[1], line, line_size);

                    getline(&line, &size, stdin);
                }

                //closing all pipes
                close(fd1_2[1]);
                close(fd1_2[0]);
                close(fd1_3[1]);
                close(fd1_3[0]);
                close(fd1_4[0]);
                close(fd1_4[1]);

                //waiting for the children input
                while (wait(&status) != -1);
                
                return 0;
            }
        }
    }
}