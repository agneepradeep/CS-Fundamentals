#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* my_thread_function(void *args) {
    int* num = (int *)args;
    printf("Thread is running, Received Argument %d\n",*(num));
    pthread_exit(NULL);
}

int main () {
    pthread_t thread;
    int argument = 5;

    /**pthread_create() returns 0 if thread didn't successfully created */

    if (pthread_create(&thread,NULL,my_thread_function,(void *)&argument)) {
        fprintf(stderr, "Thread Creation Failed");
    } else {
        pthread_join(thread,NULL);
        printf("Thread has finished its execution\n");
    }
    return 0;
}