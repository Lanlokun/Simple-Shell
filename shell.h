#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

char *strconcat(char *prefix, char *cmd);
char **params(char *buff);
int _strcmp(char *s1, char *s2);
void *_env(void);
char *strip(char *str);
int _strlen(char *str);
int cmd(char *str);

#endif
