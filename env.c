#include "shell.h"

/**
 * _env - display environment variables
 *
 * Return: void
 */

void *_env(void)
{
	int nb;

	for (nb = 0; environ[nb]; nb++)
	{
		write(STDOUT_FILENO, environ[nb], _strlen(environ[nb]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (NULL);
}

