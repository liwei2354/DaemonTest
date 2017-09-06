#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
  pid_t pid;
  int fd;
  int i;
  FILE * fp;

  fprintf(stdout,"begin to fork child process to create a daemon!\n");
  
  pid = fork();
  if(pid < 0)
  {
    perror("fork()");
    exit(1);
  }

  if(pid > 0)
    exit(0);
  
  fd = open("/dev/null",O_RDWR);
  if(fd < 0)    
  {
    perror("open");
    exit(1);
  }
  
  dup2(fd,0);
  dup2(fd,1);
  dup2(fd,2);

  if(fd > 2)
    close(fd);

  umask(0);
  
  setsid();


  fp = fopen("/tmp/out","w+");

  for(i = 0; ; i++)
  {
   
    fprintf(fp,"%d",i);
    fflush(NULL);
    sleep(1);
  }




}











