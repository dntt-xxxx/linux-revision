#include <pthread.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int *gval;


static void * thread_f1(void * arg){
    // int *ret=malloc(sizeof(int));
    static int ret1 =1;


    pthread_exit((void*)&ret1);
}

static void * thread_f2(void * arg){
    // int *ret=malloc(sizeof(int));
   static int ret2 =1;


    pthread_exit((void*)&ret2);
}


int main(int argc, char const *argv[])
{
    gval = (int*) malloc(sizeof(int)*10);
    int * t1_ret;
    int * t2_ret;

    pthread_t t1,t2;
    int status;

    status = pthread_create(&t1,NULL, thread_f1,"thread1");
    if (status != 0)     
    {
        perror(" create thread 1 unsuccessfully");
    }
    status = pthread_create(&t2,NULL, thread_f2,"thread2");
    if (status != 0)     
    {
        perror(" create thread 2 unsuccessfully");
    }
    

    pthread_join(t1,(void **) &t1_ret);
    pthread_join(t2,(void **) &t2_ret);

    printf("Main thread: t1_ret:%d t2_ret:%d\n",*t1_ret,*t2_ret);


    /* code */
    pthread_exit(NULL);
}
