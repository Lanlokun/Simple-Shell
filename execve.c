#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    char *argv[] = {"/bin/ls", "-l", NULL};

    pid_t my_pid;

    my_pid = fork();
    if (my_pid == -1)
    {
        return (-1);
    }
       
    if (my_pid == 0)
    {
        int val = execve(argv[0], argv, NULL);
         if (val == -1)
         {
        perror("Error");
         }
    }
    else
    {
        wait(NULL);
        printf("Done\n");

    }

    return (0);
}