#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

sem_t m_sem;
int g_val =0;

void* thread_func(void *arg) {
    char *str=(char*) arg;
    int loc=0;

    printf("This is thread: %s\n",str);
    sem_wait(&m_sem);
    for (size_t i = 0; i < 10000; i++)
    {
        loc = g_val;
        loc++;
        g_val = loc;
        /* code */
    }
    
    sem_post(&m_sem);
    sleep(5);
    printf("exit thread:%s \n",str);
    pthread_exit(0);
    
}

int main(int argc, char* argv[] ) {

    pthread_t  t1;
    pthread_t t2;
    int s;
    
    if (sem_init(&m_sem,0,1) == -1)  
    {
        perror("sem_init");
        exit(EXIT_FAILURE);
    }
    

    printf("start main thread, pid: %d\n", getpid());
    s = pthread_create(&t1,NULL,thread_func,"t1");
    if (s!=0)
    {
        perror("create thread fails");
    }
    s = pthread_create(&t2,NULL,thread_func,"t2");
    if (s!=0)
    {
        perror("create thread fails");
    }

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    
    sem_destroy(&m_sem);

    printf("Main thread exit now gva:%d \n",g_val);

    // exit(0);
    pthread_exit(0);
}