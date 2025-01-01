#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

sem_t binary_semaphore;

void* critical_section (void* args) {
    int num =*((int *)args);

    sem_wait(&binary_semaphore);
    printf("Thread %d is running in critical section\n",num);
    
    printf("Thread %d is leaving the critical section\n",num);
    sem_post(&binary_semaphore);
}

int main () {
    pthread_t thread_1, thread_2;
    int thread_id_1 = 1;
    int thread_id_2 = 2;
    sem_init(&binary_semaphore,0,1);

    pthread_create(&thread_1, NULL, critical_section, &thread_id_1);
    pthread_create(&thread_2,NULL,critical_section, &thread_id_2);

    pthread_join(thread_1,NULL);
    pthread_join(thread_2, NULL);

    sem_destroy(&binary_semaphore);
    printf("Execution of Threads Completed\n");
    return 0;
}