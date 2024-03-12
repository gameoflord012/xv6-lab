#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int mask = atoi(argv[1]);
    trace(mask);

    if(fork() == 0)
    {
        // map exec arg from user input
        char * execArg[argc - 1];
        for(int i = 0; i < argc - 2; i++) execArg[i] = argv[i + 2];
        execArg[argc - 2] = 0;

        exec(execArg[0], execArg);
        printf("exec error");
        exit(-1);
    }
    else
    {
        wait(0);
    }
    
    exit(0);
}
