#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// defining M N

// void *producer(void *);
// void *consumer(void *);
int N;
int M;
int producingIndex = 0;
int consumingIndex = 0;
sem_t FullSemaphore;
sem_t EmptySemaphore;
sem_t mutex;
int *buffer;
void *consumer()
{
    int m = M;
    while (m > 0)
    {
        sem_wait(&FullSemaphore);
        sem_wait(&mutex);
        int consumedNumber = buffer[consumingIndex];
        consumingIndex = (consumingIndex + 1) % N;
        char *evenOrOdd = "odd";
        if (consumedNumber % 2 == 0)
        {
            evenOrOdd = "even";
        }
        printf("Consumer Thread %d: I got number %d, and its %s\n", pthread_self(), consumedNumber, evenOrOdd);
        sem_post(&mutex);
        sem_post(&EmptySemaphore);
        m--;
    }
}
void *producer()
{
    int m = M;
    while (m > 0)
    {
        int randomNumber = rand();
        sem_wait(&EmptySemaphore);
        sem_wait(&mutex);
        buffer[producingIndex] = randomNumber % 100;
        producingIndex = (producingIndex + 1) % N;
        printf("Producer Thread %d: Generated number %d\n", pthread_self(), randomNumber);
        sem_post(&mutex);
        sem_post(&FullSemaphore);
        m--;
    }
}



int main()
{
    // gettin m n
    printf("N:\n");
    scanf("%d", &N);
    printf("M:\n");
    scanf("%d", &M);
    buffer = (int *)malloc(sizeof(int) * N);

    // creating threads and semaphores

    sem_init(&FullSemaphore, 0, 0);
    sem_init(&EmptySemaphore, 0, N);
    sem_init(&mutex, 0, 1);

    pthread_t threadIDs[6];
    pthread_create(&threadIDs[3], NULL, producer, NULL);
    pthread_create(&threadIDs[4], NULL, producer, NULL);
    pthread_create(&threadIDs[5], NULL, producer, NULL);
    pthread_create(&threadIDs[0], NULL, consumer, NULL);
    pthread_create(&threadIDs[1], NULL, consumer, NULL);
    pthread_create(&threadIDs[2], NULL, consumer, NULL);
   

    sem_destroy(&FullSemaphore);
    sem_destroy(&EmptySemaphore);
    sem_destroy(&mutex);

    return 0;
}

// producer function



// consumer function

