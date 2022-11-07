#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    size_t n = 10;

    char *buff = malloc(sizeof(char) * n);

    printf("Enter your name: ");
    getline(&buff, &n, stdin);
    printf("Hello %s", buff);

    free(buff);
    return (0);
}