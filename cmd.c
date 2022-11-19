#include "shell.h"

/**
 * cmd - handle built-in commands
 * @str: command to evaluate
 *
 * Return: 0 on success
 */

int cmd(char *str)
{
	if (!_strcmp(str, "exit"))
		exit(0);
	else if (!_strcmp(str, "env"))
	{
		_env();
		return (0);
	}
	else if (!_strcmp(str, "clear"))
	{
		system("clear");
		return (0);
	}
	return (1);
}

