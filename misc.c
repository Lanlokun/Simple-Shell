#include "shell.h"

/**
 * _strcat - join cmd prefix to cmd name
 * @prefix: cmd prefix
 * @cmd: command name
 *
 * Return: cmd path on success, else NULL
 */

char *_strcat(char *prefix, char *cmd)
{
	int i = 0, j = 0;
	char *path;

	path = malloc(sizeof(cmd) * (_strlen(cmd) + 15));
	if (!path)
	{
		write(STDOUT_FILENO, fncName, _strlen(fncName));
		perror("");
		return (NULL);
	}

	while (prefix[i])
		path[j++] = prefix[i++];

	i = 0;
	while (cmd[i] && cmd[i] != '\n')
		path[j++] = cmd[i++];
	path[j] = '\0';

	return (&*path);
}

/**
 * is_path - determine if string is valid path
 * @str: string to evaluate
 *
 * Return: str on success, else NULL
 */

char *is_path(char *str)
{
	if (access(str, F_OK))
	{
		write(STDOUT_FILENO, fncName, _strlen(fncName));
		perror("");
		return (NULL);
	}
	return (str);
}

/**
 * params - split string into commands and arguments
 * @input: string input to split
 *
 * Return: command and arguments, else NULL
 */

char **params(char *input)
{
	char *token, **av;
	int i = 0, j = 0;

	if (*input == '\n')
		return (NULL);

	av = malloc(10);
	if (!av)
		return (NULL);

	token = strtok(input, " ");
	while (token)
	{
		av[i] = malloc(_strlen(token) + 5);
		token = strip(token);
		if (i == 0 && !cmd(token))
			return (NULL);
		if (i == 0 && access(token, F_OK))
			token = is_path(_strcat("/bin/", token));

		if (!token)
		{
			free(av);
			return (NULL);
		}
		while (*token)
			av[i][j++] = *token++;
		av[i++][j] = '\0';
		j = 0;
		token = strtok(NULL, " ");
	}
	return (&*av);
}

/**
 * strip - remove spaces from word
 * @str: string to strip
 *
 * Return: stripped string
 */

char *strip(char *str)
{
	char *res = malloc(_strlen(str));
	int i = 0;

	while (str[i] != 9 && str[i] != 32 && str[i] != 10)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

/**
 * _strcmp - Check the equality of two strings
 * @s1: original string
 * @s2: comparison string
 *
 * Return: 0 on success, else distance of uncommon characters
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
