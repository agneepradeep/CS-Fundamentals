#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFERSIZE 5

int buffer[BUFFERSIZE];
int producer_index = 0;
int consumer_index = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex_lock;

void* producer_function(void* args) {
    int item;
    for (int i = 0; i<10;i++) {
        item = random()%100;

        sem_wait(&empty);
        pthread_mutex_lock(&mutex_lock);
        buffer[producer_index] = item;

        printf("Producer produces a item %d\n",item);
        producer_index = (producer_index+1)%BUFFERSIZE;

        sem_post(&full);
        pthread_mutex_unlock(&mutex_lock);
        sleep(1);
    }
    return NULL;
}

void* consumer_function(void *args) {
    int item;

    for (int i = 0; i<10; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex_lock);

        item = buffer[consumer_index];
        printf("Consumer Consumed Item %d\n",item);
        consumer_index = (consumer_index+1)%BUFFERSIZE;

        sem_post(&empty);
        pthread_mutex_unlock(&mutex_lock);
        sleep(2);
    }
    return NULL;
}

int main () {
    pthread_t producer_thread, consumer_thread;

    sem_init(&empty,0,BUFFERSIZE);
    sem_init(&full,0,0);
    pthread_mutex_init(&mutex_lock,NULL);

    pthread_create(&producer_thread,NULL,producer_function,NULL);
    pthread_create(&consumer_thread,NULL,consumer_function,NULL);

    pthread_join(producer_thread,NULL);
    pthread_join(consumer_thread,NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex_lock);

    return 0;
}