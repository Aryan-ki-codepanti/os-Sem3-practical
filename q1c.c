#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t id;
    id = fork();

    if (id == 0) //child
        printf("Inside Child Process: %d\n", id);
     

    else if (id > 0) //parent
    {
        printf("Waiting for child\n");
        wait(NULL);
        printf("Inside Parent Process: %d\n", id);
    }

    else
    {
        printf("Error Occured! %d\n", id);
        return 1;
    }

    return 0;
}