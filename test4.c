#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


char *strconcat(char *argv1, char *argv2)
{
	int i = 0, j = 0;
	char *result = malloc(sizeof(argv1) * 100);

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


int main(int ac, char **av)
{
		char *command = strconcat("/bin/", av[1]);
		char *params[] = {command, av[2], NULL};

		if (execve(params[0], params, NULL) == -1)
		{
			perror("Error");
			return (-1);
		}

		free(command);

		return (0);
}
