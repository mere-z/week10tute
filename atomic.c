#include <stdio.h>
#include <pthread.h>

int global_total = 0;
pthread_mutex_t global_total_mutex = PTHREAD_MUTEX_INITIALIZER;

void *add_5000_to_counter(void *data) {
    for (int i = 0; i < 5000; i++) {
        // sleep for 1 nanosecond
        nanosleep (&(struct timespec){.tv_nsec = 1}, NULL);
        
        // increment the global total by 1
        pthread_mutex_lock(&global_total_mutex);
        // this is an atomic operation. global_total = global_total + 1 is not an atomic operation
        global_total++;
        pthread_mutex_unlock(&global_total_mutex);
    }

    return NULL;
}

int main(void) {
    pthread_t thread1;
    pthread_create(&thread1, NULL, add_5000_to_counter, NULL);

    pthread_t thread2;
    pthread_create(&thread2, NULL, add_5000_to_counter, NULL);

    // if threads are not joined, this program will terminate without calling the threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // if program works correctly, should print 10000
    printf("Final total: %d\n", global_total);
}
