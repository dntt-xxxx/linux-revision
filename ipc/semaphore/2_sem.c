#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    sem_t *m_sem;
    char *sem_name="/mysemaphore";
    int sval;

    m_sem = sem_open(sem_name,O_RDWR);
    if (m_sem == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    
    if (sem_getvalue(m_sem,&sval) == -1)
    {
        perror("sem_getvalue");
        exit(EXIT_FAILURE);
    }
     printf("SEM VALUE 1st: %d\n",sval);
    if (sem_wait(m_sem) == -1 )
    {
        perror("sem_wait");
        exit(EXIT_FAILURE);
    }
    sem_getvalue(m_sem,&sval);
    printf("SEM VALUE after wait: %d\n",sval);
    printf("P1 executes critical section \n");
    sleep(5);

    sem_post(m_sem);
    sem_getvalue(m_sem,&sval);
    printf("SEM VALUE after sem_post: %d\n",sval);
    // sem_unlink(sem_name);
    return 0;
}
