#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
* Function Declarations for builtin shell commands:
* File: shell.c
* Author: Malik K Lanlokun and Okuhle Nsibande
*/

char *strip_cmd(char *token)
{
	char *cmd;
	int i = 0;

	if (!access(token, F_OK))
		return (token);
	else
	{
		cmd = malloc(sizeof(token) * strlen(token));
		if (!cmd)
			return (NULL);
		while (token)
		{
			if (*token == '\n')
				break;
			cmd[i++] = *token++;
		}
		cmd[i] = '\0';
	}
	return (cmd);
}


/*
* Function to check the equality of two provided strings:
*/
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	return (0);
}

char *cmd_path(char *token)
{
	int i = 0, j = 0;
	char *prefix = "/bin/", *cmd, *path;

	cmd = strip_cmd(token);
	if (!cmd)
		return (NULL);
	if (!access(cmd, F_OK) || !strcmp(cmd, "cd"))
		return (cmd);

	path = malloc(sizeof(cmd) * strlen(cmd) + 5);
	if (!path)
	{
		perror("Error");
		free(cmd);
		return(NULL);
	}

	while (prefix[i])
		path[j++] = prefix[i++];

	i = 0;
	while (cmd[i])
		path[j++] = cmd[i++];
	path[j] = '\0';

	if (access(path, F_OK))
	{
		perror("Error");
		free(path);
		free(cmd);
		return (NULL);
	}
	return (path);
}

char *_strcat(char *dest, char *src)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
		;
	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
char **params(char *buff)
{
	char *command, *token, **av;
	int i = 0, j = 0;

	if (*buff == '\n')
		return (NULL);

	av = malloc(10);
	if (!av)
		return (NULL);

	token = strtok(buff, " ");

	while (token)
	{
		// printf("token: %s", token);
		if (i == 0)
		{
			token = cmd_path(token);
			if (!token)
			{
				free(av);
				return (NULL);
			}
			command = token;
			printf("command: %s\n", command);
		}

		av[i] = malloc(strlen(token));

		while (*token && (*token != '\n'))
			av[i][j++] = *token++;
		av[i++][j] = '\0';
		j = 0;
		token = strtok(NULL, " ");
	}
	return (&*av);
}

extern char **environ;

int main(int argc, char **argv)
{
	int run = 1, nb, i;
	size_t size = 10;
	pid_t pid, ppid;
	char *buff, *tmpbuff, **av;

    
	while(run)
	{
		size = 10;

		buff = malloc(size);

		if (!buff)
			return (1);
		
		if (isatty(STDIN_FILENO) == 1)
			printf(":) ");
		nb = getline(&buff, &size, stdin);
		


		/*
		*statement that executes the exit command
		*/
	
		if (!strcmp(buff, "exit\n"))
		{
			break;
		}

		/*
		*statement that prints the env variables
		*/

		if(!strcmp(buff, "env\n"))
		{
			for (nb = 0; environ[nb]; nb++)
			{
				printf("%s/n", environ[nb]);
			}
			continue;
		}

		/*
		*statement that executes the clear command
		*/

		if (!strcmp(buff, "clear\n"))
		{
			system("clear");
			continue;
		}

		// if (!strcmp(buff, "cd"))
		// {
		// 		if (!chdir(av[1]))
		// 			perror("Error");
		// 		free(av);
		// }
	
		if (buff[nb - 1] != '\n')
			break;

		av = params(buff);

		if (!strcmp(buff, "cd"))
		{
			char *path = av[1];
			chdir(path);
			if(!chdir(path))
				perror("Error");
		}

		if (!av)
		{
			free(buff);
			continue;
		}

		/*
		* child process created for the execution of commands passed
		*/
	
		pid = fork();

		if (pid == -1)
		{	
			return (-1);
		}
		if(nb != -1 && ppid == -1)
		{
			printf("terminating...");
		}
		
		if (pid == 0)
		{

			if (execve(*av, av, environ) == -1)
			{
				perror("Error");
				free(buff);
				free(av);
				return (-1);
			}
		
		}
		else
		{
			wait(NULL);
		}

		 if (nb == -1)
       		 printf("CTRL + D captured\n");
	/*
	 *release of all memory used
	 */

		free(av);
		free(buff);
		}

	/*
	 * program terminates here
	 */

		printf("\nBye\n");
		return (0);

}


