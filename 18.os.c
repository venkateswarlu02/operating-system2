#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

sem_t empty, full, mutex;
int buffer[BUFFER_SIZE];
int counter = 0;

void *producer(void *arg) {
    int item;
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        item = i + 1;

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[counter] = item;
        printf("Produced: %d\n", item);
        counter++;

        sem_post(&mutex);
        sem_post(&full);
    }

    return NULL;
}

void *consumer(void *arg) {
    int item;
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        sem_wait(&full);
        sem_wait(&mutex);

        item = buffer[counter - 1];
        counter--;
        printf("Consumed: %d\n", item);

        sem_post(&mutex);
        sem_post(&empty);
    }

    return NULL;
}

int main() {
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        pthread_create(&producers[i], NULL, producer, NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        pthread_create(&consumers[i], NULL, consumer, NULL);
    }

    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        pthread_join(consumers[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
