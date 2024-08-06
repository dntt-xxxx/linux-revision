#include <pthread.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int gval=0;
int condition=0;

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static void * thread_f1(void * arg){
    // int *ret=malloc(sizeof(int));
    static int ret1 =1;
    int loc;
    int ret;
    printf("thread 1 run first\n");
    ret = pthread_mutex_lock(&mtx);
    if (ret!=0)
    {
        perror("mutex lock fails\n");
        pthread_exit(NULL);
    }
    gval=111;
    sleep(3);
    condition =1;
    pthread_cond_signal(&cond);
    ret = pthread_mutex_unlock(&mtx);
    if (ret!=0)
    {
        perror("mutex lock fails\n");
        pthread_exit(NULL);
    }
    printf("thread 1 exit\n");
    pthread_exit(NULL);
}

static void * thread_f2(void * arg){
    int ret;
    printf("thread 2 run first\n");
    ret = pthread_mutex_lock(&mtx);
    if (ret!=0)
    {
        perror("mutex lock fails\n");
        pthread_exit(NULL);
    }
    
    while (condition == 0)
    {
        pthread_cond_wait(&cond,&mtx);
    }
    
    printf("Recieve signal from thread_1 this is always run after thread A critical section%d\n",condition);
    printf("value gvar:%d\n",gval);
    ret = pthread_mutex_unlock(&mtx);
    if (ret!=0)
    {
        perror("mutex lock fails\n");
        pthread_exit(NULL);
    }
    printf("thread 2 exit\n");
    pthread_exit(NULL);
}


int main(int argc, char const *argv[])
{
    // gval = (int*) malloc(sizeof(int)*10);
    int * t1_ret;
    int * t2_ret;

    pthread_t t1,t2;
    int status;

    status = pthread_create(&t1,NULL, thread_f1,NULL);
    if (status != 0)     
    {
        perror(" create thread 1 unsuccessfully");
    }
    status = pthread_create(&t2,NULL, thread_f2,NULL);
    if (status != 0)     
    {
        perror(" create thread 2 unsuccessfully");
    }
    
   

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
     printf("Main thread: gval: %d\n",gval);
    /* code */
    return EXIT_SUCCESS;
}
