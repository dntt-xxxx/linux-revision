#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Thread function
void* thread_function(void* arg) {
    printf("Thread is running...\n");
    sleep(12); // Simulate some work
    printf("Thread has finished.\n");
    pthread_exit(NULL);
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

    // Detach the thread
    result = pthread_detach(thread);
    if (result != 0) {
        printf("Error detaching thread: %d\n", result);
        exit(EXIT_FAILURE);
    }

    // Main thread continues to execute
    printf("Main thread is continuing to execute...\n");

    // Sleep for a while to allow the detached thread to run
    sleep(3);

    printf("Main thread has finished.\n");
    pthread_exit(NULL);
}