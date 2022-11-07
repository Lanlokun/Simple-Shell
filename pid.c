#include <unistd.h>
#include <stdio.h>

int main(void)
{
    int a = 4;
    int b = 8;

    int sum  = a + b;

    printf("Sum is %d\n", sum);
    pid_t ppid = getppid();
    pid_t pid = getpid();


    printf("Process ID is %d\n", pid);
    printf("Parent Process ID is %d\n", ppid);
}

