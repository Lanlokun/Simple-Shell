#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


char *strconcat(char *argv1, char *argv2)
{
	int i = 0, j = 0;
	char *result = malloc(sizeof(char) * 100);

	while (argv1[i])
	{
		result[j] = argv1[i];
		i++;
		j++;
	}

	i = 0; 

	while (argv2[i])
	{
		result[j] = argv2[i];
		i++;
		j++;
	}

	result[j] = '\0';

	return (result);
}

int main(void)
{
	
	size_t size = 20;
	char *command, *token;
	char *buff = malloc(sizeof(char) * size);
	char *delim = " ";

	pid_t my_pid;

    my_pid = fork();
    
	while(1)
	{
			if (my_pid == -1)
			{
				return (-1);
			}
       
			if (my_pid == 0)
			{
				printf(": ");
				getline(&buff, &size, stdin);

				if (strcmp(buff, "exit\n") == 0)
				{
					break;
				}

				token = strtok(buff, delim);
				while(token)
				{
					command = strconcat("/bin/", token);
					char *argv[] = {command, NULL};
					int val = execve(argv[0], argv, NULL);
					if (val == -1)
						{
							perror("Error");
						}
					token = strtok(NULL, delim);
				}
				printf("%s", command);

				
			}

	}

	free(buff);
	return (0);
}