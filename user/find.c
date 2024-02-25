#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "user/user.h"

void
ls(char *path, const char * file)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, O_RDONLY)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_DEVICE:
  case T_FILE:
    for(p = path + strlen(path); p >= path && *p != '/'; p--);
    p++;
    
    if(strcmp(p, file) == 0)
      printf("%s\n", path);

    close(fd);
    return;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }
    
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';

    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;

      memmove(p, de.name, sizeof de.name);
      // printf("%s\n", buf);

      if(strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
        continue;

      ls(buf, file);
    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
    ls(argv[1], argv[2]);
    exit(0);
}