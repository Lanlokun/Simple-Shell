#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>



extern char **environ;

char *_getenv(const char *name);



char *_getenv(const char *name){
    int i = 0;
    char *env;
    char *env_name;
    char *env_value;

    while (environ[i])
    {
        env = environ[i];
        env_name = strtok(env, "=");
        env_value = strtok(NULL, "=");
        if (strcmp(env_name, name) == 0)
        {
                return (env_value);
        }
        i++;
    }
    return (NULL);
}

int main(void)
{
   char *buff;
   size_t size = 100;

    
   buff = malloc(size);

   if (buff == NULL)
   {
       perror("Unable to allocate buffer");
       exit(1);
   }

    while(printf("Enter any Environment Variable : ") && getline(&buff, &size, stdin) != -1)
    {
         size_t len = strlen(buff);
        if (len > 0 && buff[len-1] == '\n') {
            buff[--len] = '\0';
        }
        printf("Value of %s is %s\n", buff, _getenv(buff));
    }

// char *path = _getenv("PATH");

// printf("PATH: %s\n", path);


}