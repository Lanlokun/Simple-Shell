#include "shell.h"

/**
 * _strlen - count numver of characters in a string
 * @str: string to count
 *
 * Return: length of string
 */

int _strlen(char *str)
{
	int i = 0;

	while (str[i++]);
	return (i);
}
