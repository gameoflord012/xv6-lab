#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int p[2];
    pipe(p);

    if(fork() == 0)
    {
        int pid = getpid();

        char byte;
        read(p[0], &byte, 1);
        printf("%d: received ping\n", &pid);
        
        char sendByte = 'a';
        write(p[1], &sendByte, 1);

        close(p[0]);
        close(p[1]);
        exit(0);
    }
    else
    {
        int pid = getpid();

        char sendByte = 'a';
        write(p[1], &sendByte, 1);

        char byte;
        read(p[0], &byte, 1);
        printf("%d: received pong\n", &pid);

        close(p[0]);
        close(p[1]);
    }

    wait(0);
    exit(0);
}
