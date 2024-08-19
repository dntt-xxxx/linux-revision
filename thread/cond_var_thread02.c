
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Not used properly in this example

int condition = 0;  // Shared condition variable
//ERROR:
// void *thread_a(void *arg) {
//     // Thread A checks the condition without locking the mutex
//     if (condition == 0) {
//         printf("Thread A: Condition is false, waiting...\n");
//         // Here, Thread A plans to wait, but without locking the mutex

//         // Simulate some delay before actually calling pthread_cond_wait
//         sleep(1);

//         // Thread A now waits on the condition variable without holding a mutex
//         pthread_cond_wait(&cond, &mutex);  // Improper usage; the mutex should be locked here
//         printf("Thread A: Woke up, condition is now true.\n");
//     } else {
//         printf("Thread A: Condition is already true.\n");
//     }

//     return NULL;
// }

// void *thread_b(void *arg) {
//     // Thread B sets the condition and signals the condition variable
//     sleep(1);  // Let Thread A start first
//     printf("Thread B: Setting condition to true and signaling...\n");
//     condition = 1;
//     pthread_cond_signal(&cond);  // Signal the condition variable
//     return NULL;
// }

//FIX:
 void *thread_a(void *arg) {
    pthread_mutex_lock(&mutex);  // Lock the mutex

    while (condition == 0) {
        printf("Thread A: Condition is false, waiting...\n");
        pthread_cond_wait(&cond, &mutex);  // Now this is correct: mutex is locked
    }

    printf("Thread A: Woke up, condition is now true.\n");
    pthread_mutex_unlock(&mutex);  // Unlock the mutex

    return NULL;
}

void *thread_b(void *arg) {
    sleep(1);  // Let Thread A start first

    pthread_mutex_lock(&mutex);  // Lock the mutex
    printf("Thread B: Setting condition to true and signaling...\n");
    condition = 1;
    pthread_cond_signal(&cond);  // Signal the condition variable
    pthread_mutex_unlock(&mutex);  // Unlock the mutex

    return NULL;
}

int main() {
    pthread_t a, b;

    // Create Thread A and Thread B
    pthread_create(&a, NULL, thread_a, NULL);
    pthread_create(&b, NULL, thread_b, NULL);

    // Wait for both threads to finish
    pthread_join(a, NULL);
    pthread_join(b, NULL);

    return 0;
}