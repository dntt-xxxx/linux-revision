#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* thread_func(void *arg) {
    char *str=(char*) arg;
    printf("in thread func, arg pass: %s , thread_id: %ld pid: %d\n",str,pthread_self(),getpid());
    sleep(3);
    printf("exit thread\n");

    pthread_exit("thread1");
    
}
void * t2_func(void * arg) {
    char *str2=(char*) arg;
    printf("In the thread %s pid: %d\n",str2,getpid());
    sleep(6);
    pthread_exit("thread2");
}
int main(int argc, char* argv[] ) {

    pthread_t  t1;
    pthread_t t2;
    int s;
    void * res;
    void *res2;

    printf("start main thread, pid: %d\n", getpid());
    s = pthread_create(&t1,NULL,thread_func,"HELLO");
    if (s!=0)
    {
        perror("create thread fails");
    }
    s=pthread_create(&t2,NULL,t2_func,"t2");
    if (s!=0)
    {
        perror("create t2 fail");
    }
    
# if 1
    s = pthread_join(t1,&res);
    if (s!=0)
    {
        perror("pthead join error\n");
    }
    printf("Main thread: thread return %s\n", (char*)(res));
    s = pthread_join(t2,&res2);
    if (s!=0)
    {
        perror("pthead join error\n");
    }
     printf("Main thread: thread return %s\n", (char*)(res2));
#endif

    printf("Main thread exit now \n");
    // exit(0);
    pthread_exit(0);
}