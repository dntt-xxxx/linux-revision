#include <string.h>
#include <stdlib.h>
#include <stdio.h> 
#include <fcntl.h> 
#include <malloc.h>
#include <unistd.h>

int main(void) {

    int fd;
    int dup_fd;

    char mess[100];

    fd = open("author.txt",O_WRONLY);
    if (fd < 0)
    {
        perror("Can not openfile\n");
        exit(1);
    }
    printf("fd = %d\n",fd);
    close(1);
    dup_fd = dup2(fd,1);
    sprintf(mess, "dup_fd = %d\n",dup_fd);
    printf("DOTU\n");
    printf("fd=%d\n",fd);
    write(dup_fd,mess,strlen(mess));
    close(fd);
    return 0;
}

