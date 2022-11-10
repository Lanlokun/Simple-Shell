#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



int main(void)
{
	

				
    if (access("/bin/ls", F_OK))
    {
        perror("Error \n");
    }
    else
    {
        char * const* cmd = "ls";
        execve("/bin/", cmd, NULL);
    }
    
    return (0);


			
}
