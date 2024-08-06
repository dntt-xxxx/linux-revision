#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* thread_func(void *arg) {
    char *str=(char*) arg;
    printf("in thread func, arg pass: %s , thread_id: %ld pid: %d\n",str,pthread_self(),getpid());
    sleep(15);
    printf("exit thread\n");
    pthread_exit(0);
    
}

int main(int argc, char* argv[] ) {

    pthread_t  t1;
    int s;
    printf("start main thread, pid: %d\n", getpid());
    s = pthread_create(&t1,NULL,thread_func,"HELLO");
    if (s!=0)
    {
        perror("create thread fails");
    }
    sleep(8);
    printf("Main thread exit now \n");

    // exit(0);
    pthread_exit(0);
}