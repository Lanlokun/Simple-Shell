#include <stdlib.h>
#include <stdio.h>

/*
* Function Declarations for builtin shell commands:
* File: shell.c
* Author: Malik K Lanlokun and Okuhle Nsibande
*/

int _getline(char **lineptr, size_t *n, FILE *stream)
{
   
   *lineptr  = malloc(n);
   char *buff;
   int i = 0;

    if (*lineptr == NULL)
    {
        return -1;
    }
    else 
    {
        while(*stream != '\0')
        {
            *lineptr = *stream;
            while (lineptr[i] != '\0')
            {

                buff = lineptr[i];
                i++;
                
            }

            if (strlen(buff) > n)
            {
                    n = strlen(buff);
                    *lineptr = realloc(*lineptr, n);
            }
            *lineptr++;
            *stream++;
        } 

    }

    return (0);



}


int main(void)
{
	

    char *lineptr = NULL;
    size_t n = 0;
    FILE *stream = stdin;
    int i = 0;

    _getline(&lineptr, &n, stream);
    printf("%s", lineptr);
    return (0);
}


