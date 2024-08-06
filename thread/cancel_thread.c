#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Thread function
void* thread_function(void* arg) {
    
    while (1)
    {
        printf("Thread is running...\n");
        sleep(1);
    }
    
    printf("Thread has finished.\n");
    // pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    int result;

    // Create a new thread
    result = pthread_create(&thread, NULL, thread_function, NULL);
    if (result != 0) {
        printf("Error creating thread: %d\n", result);
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < 10  ; i++)
    {
        printf("Main thead executing %d\n",i);
        sleep(2);
    }

    // Detach the thread
    result = pthread_cancel(thread);
    if (result != 0) {
        printf("Error canceling thread: %d\n", result);
        exit(EXIT_FAILURE);
    }

    printf("Main thread has finished.\n");
    pthread_exit(NULL);
}