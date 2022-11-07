#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

		token = strtok(&buff, ' ');
		while (*token)
		{
			av[i] = malloc(strlen(token));
			while (*token)
				av[i][j++] = *token++;
			av[i][j] = '\0';
			i++;
			token = strtok(NULL, ' ');
		}

		if (access(av[1], F_OK))
		{
			command = strconcat("/bin/", av[1]);
			if (access(command, F_OK))
			{
				perror("Error");
				/* clear memory & restart */
				continue;
			}

			else
				command = av[1];
		}

		if (execve(command, av++, NULL) == -1)
		{
			perror("Error");
			/* clear memory & restart */
			continue;
		}
	}
}
