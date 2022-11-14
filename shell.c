#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char *strconcat(char *prefix, char *cmd)
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
		av[i] = malloc(strlen(token) + 5);
		if (i == 0 && (!strcmp(token, "cd")))
				printf("");
		else if (i == 0 && access(token, F_OK))
			token = strconcat("/bin/", token);
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


int main(int argc, char **argv)
{
	int run = 1, nb;
	size_t size = 10;
	char pid, *buff, **av, *PROG_NAME = argv[0];

    
	while(run)
	{
		size = 10;
		buff = malloc(size);
		if (isatty(STDIN_FILENO) == 1)
			printf(":) ");
		nb = getline(&buff, &size, stdin);
	
		if (!strcmp(buff, "exit\n") || nb == -1)
			break;

		if (!strcmp(buff, "clear\n"))
		{
			system("clear");
			continue;
		}
	
		if (buff[nb - 1] != '\n')
			break;
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
			if (!strcmp(*av, "cd"))
			{
				if (chdir(av[1]))
					perror("Error");
				write(1, "passed through", 10);
				return (0);
			}
			else if (execve(av[0], av, NULL) == -1)
			{
				printf("%s: ", PROG_NAME);
				perror("");
				while (av)
					printf("%s ", *av++);
				return (1);
			}
			free(av);
		}
		free(buff);
	}

	printf("Bye\n");
	return (0);
}
