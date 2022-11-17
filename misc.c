#include "shell.h"

/**
 * _strcat: join cmd prefix to cmd name
 * @prefix: cmd prefix
 * @cmd: command name
 *
 * Return: cmd path on success, else NULL
 */

char *_strcat(char *prefix, char *cmd)
{
	int i = 0, j = 0;
	char *path;

	path = malloc(sizeof(cmd) * (strlen(cmd) + 5));
	if (!path)
	{
		perror("Error");
		return(NULL);
	}

	while (prefix[i])
		path[j++] = prefix[i++];

	i = 0;
	while (cmd[i] && cmd[i] != '\n')
		path[j++] = cmd[i++];
	path[j] = '\0';

	if (access(path, F_OK))
	{
		perror("Error");
		free(path);
		return (NULL);
	}
	return (&*path);
}

/**
 * params - split string into commands and arguments
 * @input: string input to split
 *
 * Return: command and arguments, else NULL
 */

char **params(char *input)
{
	char *command, *token, **av;
	int i = 0, j = 0;

	if (*input == '\n')
		return (NULL);

	/*if (!strcmp(input, "exit\n") || nb == -1)
		break;
	if (!strcmp(*av, "cd"))
	{
		if (chdir(av[1]))
			perror("Error");
		write(1, "passed through", 10);
		return (0);
	}*/

	if (!strcmp(input, "clear\n"))
	{
		system("clear");
		return (NULL);
	}

	av = malloc(10);
	if (!av)
		return (NULL);

	token = strtok(input, " ");
	while (token)
	{
		av[i] = malloc(strlen(token) + 5);
		if (i == 0 && (!strcmp(token, "cd")))
			printf("");
		else if (i == 0 && access(token, F_OK))
			token = _strcat("/bin/", token);
		if (!token)
		{
			free(av);
			return (NULL);
		}
		while(*token && (*token != '\n'))
			av[i][j++] = *token++;
		av[i++][j] = '\0';
		j = 0;
		token = strtok(NULL, " ");
	}
	return (&*av);
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
