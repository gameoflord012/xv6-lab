#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int p[2];
    pipe(p);

    for(int i = 2; i <= 35; i++)
    {
        write(p[1], &i, sizeof(int));
    }

    int EOF = -1;
    write(p[1], &EOF, sizeof(EOF));

    while(1)
    {
        if(fork() == 0)
        {
            // printf("===============NEW_PROCESS================");
            int i;
            int pr = -1;
            int remain = 0;

            while (read(p[0], &i, sizeof(i)))
            {
                if(i == EOF) break;

                if(pr == -1)
                {
                    pr = i;
                    printf("prime %d\n", pr);
                    continue;
                }

                if(i % pr != 0)
                {
                    write(p[1], &i, sizeof(i));
                    // printf("drop %d\n", i);
                    remain = 1;
                }
            }

            write(p[1], &EOF, sizeof(EOF));

            if(!remain) 
            {
                // printf("=====NO_MORE_PRIMES====");
                exit(0);
            }
        }
        else
        {
            wait(0);
            exit(0);
        }
    }
}
