#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int sleepDuration = atoi(argv[1]);
    sleep(sleepDuration);
    exit(0);
}
