/* Program to demonstrate wait and exit*/

#include<stdio.h> 
#include<stdlib.h> 
#include<sys/wait.h> 
#include<unistd.h> 
#include <fcntl.h> 
#include <string.h>

int main() 
{ 
    pid_t cpid; 
    int status = 0;
    int fd;
    int byteread;

    char rbuf[10];
    char mes[]="dotu\n";

    fd = open("test.txt",O_RDWR|O_CREAT);
    if (fd < 0)
    {
        perror("openfile fail\n");
        exit(-1);
    }
    
    cpid = fork();
    if(cpid == -1)
        exit(-1);           /* terminate child */

    if(cpid == 0){
        printf("\nchild executing first its pid = (%d) write:%s\n",getpid(),mes);
        write(fd,mes,strlen(mes));
        sleep(2);
        exit(1);
    }
    else{
        printf("\n Parent executing before wait()\n");
        cpid = wait(&status);
        lseek(fd,SEEK_SET,0);
        byteread=read(fd,rbuf,9);
        rbuf[9]='\0';
        printf("value at file desp fd=%d byteread=%d %s\n",fd,byteread,rbuf);

        printf("\n wait() in parent done\nParent pid = %d\n", getpid()); 
        printf("\n cpid returned is (%d)\n",cpid);
        printf("\n status is (%d)\n",status);
        close(fd);
    }
    
    return 0; 
} 


#if 0
Process termination status (int) 16 bit number
1. status value if  child process has normal exit/termination
   15......8    |     7......0
   XXXXXXXX     |     XXXXXXXX 
   exitStaus    |     0


2. killed by signal
    15......8    |     7   ......0
    unused       |     X   termination signal
                       |
                       |-----> core dump flag


#endif
