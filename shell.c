#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


char *strconcat(char *argv1, char *argv2)
{
	int i = 0, j = 0;
	char *result = malloc(sizeof(argv1) * 7);

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
	int run = 1, i = 0, j = 0;
	size_t size = 10;
	char *buff = malloc(size);
	char *command, *token;
	char *av[5];

	while (run)
	{
		printf(": ");
		getline(&buff, &size, stdin);


		token = strtok(buff, " ");
		while (*token)
		{
			if (i == 0)
			{
				if (access(token, F_OK))
				{
					command = strconcat("/bin/", token);
					if (access(command, F_OK))
					{
						perror("Error");
						printf("%s, Error\n", command);
						/* clear memory & restart */
						break;
					}

					else
						command = token;
				}
			}


			av[i] = malloc(strlen(token));
			while (*token)
				av[i][j++] = *token++;
			av[i][j] = '\0';
			i++;
			j = 0;
			token = strtok(NULL, " ");
		}


		if (execve(command, av, NULL) == -1)
		{
			perror("exec, Error");
			/* clear memory & restart */
			continue;
		}
	}
}
