#include <string.h>
#include <stdlib.h>
#include <stdio.h> 
#include <fcntl.h> 
#include <malloc.h>
#include <unistd.h>

int main(void) {

    int fd;
    char mess[]=" Dotu\n";
    fd = open("author.txt",O_WRONLY);
    if (fd < 0)
    {
        perror("Can not openfile\n");
        exit(1);
    }
    lseek(fd,-1, SEEK_END);

    write(fd,mess,strlen(mess));

    lseek(fd,0, SEEK_SET);
    close(fd);
    return 0;
}