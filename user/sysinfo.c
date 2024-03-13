// #include "kernel/types.h"
// #include "kernel/stat.h"
// #include "kernel/sysinfo.h"
// #include "user/user.h"

// uint64
// atoui64(const char *s)
// {
//   uint64 n;

//   n = 0;
//   while('0' <= *s && *s <= '9')
//     n = n*10 + *s++ - '0';
//   return n;
// }

// int
// main(int argc, char *argv[])
// {
//     uint64 addr = atoui64(argv[1]);
//     struct sysinfo * info = (struct sysinfo *)addr;
//     exit(sysinfo(info));

//     // struct sysinfo info;
//     // sysinfo(&info);
//     // printf("Free %d Proc %d\n", info.freemem, info.nproc);
//     // exit(0);
// }
