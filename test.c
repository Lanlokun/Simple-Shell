#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sighandler(int);

int main () {
	size_t size = 10;
	char *buff = malloc(size);

	signal(SIGINT, sighandler);

	while(1) {
		printf(": ");
		getline(&buff, &size, stdin);
		printf("input: %s\n", buff);
		printf("Going to sleep for a second...\n");
		sleep(1); 
	}
	return(0);
}

void sighandler(int signum) {
	printf("Caught signal %d, coming out...\n", signum);
	exit(1);
}
