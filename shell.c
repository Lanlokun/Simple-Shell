#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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

char *cmd_path(char *token)
{
	int i = 0, j = 0;
	char *prefix = "/bin/", *cmd, *path;

	cmd = strip_cmd(token);
	if (!cmd)
		return (NULL);
	if (!access(cmd, F_OK))
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
		if (i == 0)
		{
			token = cmd_path(token);
			if (!token)
			{
				free(av);
				return (NULL);
			}
			command = token;
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


int main(void)
{
	int run = 1;
	size_t size = 10;
	char pid, *buff, **av;

	while (run)
	{
		printf(": ");
		buff = malloc(size);
		getline(&buff, &size, stdin);
		av = params(buff);
		if (!av)
		{
			free(buff);
			continue;
		}

		pid = fork();
		if (pid)
			wait(NULL);
		else
		{
			if (execve(av[0], av, NULL) == -1)
			{
				perror("exec, Error");
			}
			free(av);
			free(buff);
		}
	}
}
