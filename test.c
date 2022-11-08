#include <unistd.h>
#include <stdio.h>

int main() {
	char c[10];
	int pid;

	while (1)
	{
		read(STDIN_FILENO, c, strlen(STDIN_FILENO));

		printf("%s", c);
	}
	return 0;
}
