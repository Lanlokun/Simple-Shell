#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>



extern char **environ;


int main(void)
{
    char *path = getenv("PATH");
    int length = strlen(path) -1;
    for(int i=0;i<=length;i++){
        if (path[i] == ':')
            path[i] = '\n';
        printf("%c",path[i]);
    }
    printf("\n");
    return 0;
  
}