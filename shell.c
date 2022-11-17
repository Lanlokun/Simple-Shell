/*
* Function Declarations for builtin shell commands:
* File: shell.c
* Author: Malik K Lanlokun and Okuhle Nsibande
*/

#include "shell.h"

/**
 * main - shell entry point
 * @argc: number of arguments
 * @argv: list of arguments
 *
 * Return: 0 on success
 */

extern char **environ;

int main(int argc, char **argv)
{
	int run = 1, nb;
	size_t size;
	char *input, **av, *PROG_NAME = argv[0], *path;
	pid_t pid;

	while(run)
	{
		size = 10;
		input = malloc(size);
		if (isatty(STDIN_FILENO) == 1)
			printf(":) ");
		nb = getline(&input, &size, stdin);
		if (input[nb - 1] != '\n')
			break;

		/*
		*statement that executes the exit command
		*/
	
		if (!_strcmp(input, "exit\n"))
			break;

		/*
		*statement that prints the env variables
		*/

		if(!_strcmp(input, "env\n"))
		{
			for (nb = 0; environ[nb]; nb++)
			{
				printf("%s\n", environ[nb]);
			}
			continue;
		}

		/*
		*statement that executes the clear command
		*/

		av = params(input);
		if (!av)
		{
			free(input);
			continue;
		}

		if (!_strcmp(input, "clear\n"))
		{
			system("clear");
			continue;
		}

	

		/*
		* child process created for the execution of commands passed
		*/

		pid = fork();

		if (pid)
		{
			wait(NULL);
		}
		else
		{
			if (!_strcmp(*av, "cd"))
			{
				path = av[1];

				if(!path)
					path = "/";
				if(chdir(path))
					perror("Error");
				free(av);
				free(input);
			}
			else if (execve(av[0], av, NULL) == -1)
			{
				printf("%s: ", PROG_NAME);
				perror("");
			}
			free(av);
		}
		free(input);
	}

	/*
	 * program terminates here
	 */

	printf("\nBye\n");
	return (0);

}
