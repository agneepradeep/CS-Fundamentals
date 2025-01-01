#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t rw_mutex;
sem_t mutex;
int read_count = 0;
int shared_data = 0;

void *reader(void *arg) {
    int reader_id = *((int *)arg);
    sem_wait(&mutex);
    read_count++;
    if (read_count == 1)
        sem_wait(&rw_mutex);
    sem_post(&mutex);

    printf("Reader %d read data: %d\n", reader_id, shared_data);

    sem_wait(&mutex);
    read_count--;
    if (read_count == 0)
        sem_post(&rw_mutex);
    sem_post(&mutex);

    return NULL;
}

void *writer(void *arg) {
    int writer_id = *((int *)arg);
    sem_wait(&rw_mutex);

    shared_data++;
    printf("Writer %d wrote data: %d\n", writer_id, shared_data);

    sem_post(&rw_mutex);
    return NULL;
}

int main() {
    pthread_t readers[5], writers[3];
    int reader_ids[5] = {1, 2, 3, 4, 5};
    int writer_ids[3] = {1, 2, 3};

    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < 5; i++)
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    for (int i = 0; i < 3; i++)
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);

    for (int i = 0; i < 5; i++)
        pthread_join(readers[i], NULL);
    for (int i = 0; i < 3; i++)
        pthread_join(writers[i], NULL);

    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    return 0;
}
