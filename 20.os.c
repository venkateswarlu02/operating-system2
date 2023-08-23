#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

sem_t mutex;
sem_t rwMutex;

int data = 0;
int readersCount = 0;

void *reader(void *arg) {
    while (1) {
        sem_wait(&mutex);
        readersCount++;
        if (readersCount == 1) {
            sem_wait(&rwMutex);
        }
        sem_post(&mutex);

        printf("Reader %ld read data: %d\n", (long)arg, data);

        sem_wait(&mutex);
        readersCount--;
        if (readersCount == 0) {
            sem_post(&rwMutex);
        }
        sem_post(&mutex);

        usleep(100000); // Sleep for a short time to simulate reading
    }
}

void *writer(void *arg) {
    while (1) {
        sem_wait(&rwMutex);

        data++;
        printf("Writer %ld wrote data: %d\n", (long)arg, data);

        sem_post(&rwMutex);

        usleep(200000); 
    }
}

int main() {
    pthread_t readerThreads[NUM_READERS];
    pthread_t writerThreads[NUM_WRITERS];

    sem_init(&mutex, 0, 1);
    sem_init(&rwMutex, 0, 1);

    for (long i = 0; i < NUM_READERS; ++i) {
        pthread_create(&readerThreads[i], NULL, reader, (void *)i);
    }

    for (long i = 0; i < NUM_WRITERS; ++i) {
        pthread_create(&writerThreads[i], NULL, writer, (void *)i);
    }

    for (long i = 0; i < NUM_READERS; ++i) {
        pthread_join(readerThreads[i], NULL);
    }

    for (long i = 0; i < NUM_WRITERS; ++i) {
        pthread_join(writerThreads[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&rwMutex);

    return 0;
}
