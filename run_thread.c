#include <stdio.h>
#include <pthread.h>

void *thread_run(void *data) {

    char *string = data;
    printf("%s", string);
    return NULL;
}

int main(void) {
    pthread_t thread;

    char *string = "Hello there\n";
    pthread_create(
        &thread,    // the pthread_t handle that will represent this thread
        NULL,       // thread-attributes -- we usually just leave this NULL
        thread_run, // the function that the thread should start executing
        string      // data we want to pass to the thread
    );

    pthread_join(thread, NULL);

    return 0;
}
