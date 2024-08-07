#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


int main(int argc, char const *argv[])
{
    int status;
    int fd[2];
    char write_buf[15]="dongocthanhtu";
    char read_buf[1000];
    int byte_w=0;

    status = pipe(fd);
    printf("open 2 fd: 0:%d 1:%d\n",fd[0],fd[1]);


    byte_w= write(fd[1],write_buf,sizeof(write_buf));

    read(fd[0],read_buf,byte_w);
    printf("read %s\n",read_buf);


    return 0;
}
