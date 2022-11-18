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

int main(__attribute__((unused)) int argc, char **argv)
{
	int run = 1, nb;
	size_t size;
	char *input, **av;
	pid_t pid;

	//progName = _strcat(argv[0], ": ");
	char *_nam;
	_nam = _strcat(__progname, ": ");
	
	while (run)
	{
		size = 10;
		input = malloc(size);
		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, "$ ", 2);
		nb = getline(&input, &size, stdin);
		if (input[nb - 1] != '\n' || nb == -1)
			break;

		av = params(input);
		if (!av)
		{
			free(input);
			continue;
		}

		pid = fork();
		if (pid)
			wait(NULL);
		else
		{
			if (execve(av[0], av, NULL) == -1)
			{
				write(STDOUT_FILENO, _nam, _strlen(_nam));
				perror("");
			}
			free(av);
		}
		free(input);
	}
	return (0);
}
