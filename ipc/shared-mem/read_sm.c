#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    char * m_shm_name="/shm_2";
    int m_shm_fd;
    char * addr;

    m_shm_fd = shm_open(m_shm_name,O_RDWR,S_IWUSR | S_IRUSR);
    if (m_shm_fd == -1)
    {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    
    addr = mmap(NULL,100,PROT_READ | PROT_WRITE,MAP_SHARED,m_shm_fd,0);
    if (addr == MAP_FAILED) 
    {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    char mes[100];

    memcpy(mes,addr,50);
    printf("read: %s\n",mes);

    shm_unlink(m_shm_name);
    
    return 0;
}
