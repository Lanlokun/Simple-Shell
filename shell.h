#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;
extern char *fncName;
char **params(char *buff);
char *is_path(char *str);
int _strcmp(char *s1, char *s2);
void *_env(void);
char *strip(char *str);
int _strlen(char *str);
int cmd(char *str);
char *_strcat(char *prefix, char *cmd);

/*void args(char *str){
	char *fncName = str;
}*/

#endif
