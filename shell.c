#include "shell.h"

/**
 * main - shell entry point
 * @argc: number of arguments
 * @argv: list of arguments
 *
 * Return: 0 on success
 */

int main(int argc, char **argv)
{
	int run = 1, nb;
	size_t size = 10;
	char pid, *input, **av, *PROG_NAME = argv[0];

	while(run)
	{
		size = 10;
		input = malloc(size);
		if (isatty(STDIN_FILENO) == 1)
			printf(":) ");
		nb = getline(&input, &size, stdin);
		if (input[nb - 1] != '\n')
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
				printf("%s: ", PROG_NAME);
				perror("");
			}
			free(av);
		}
		free(input);
	}

	printf("Bye\n");
	return (0);
}
