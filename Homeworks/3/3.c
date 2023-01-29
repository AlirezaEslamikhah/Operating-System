#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

pthread_mutex_t lock; 
sem_t sem[5];
char state[5];

int num[5] = { 0, 1, 2, 3, 5 };

void test (int i)
{
    if (state[(i+5) %5] != 'E' && state[i] == 'H' && state[(i+1) %5] != 'E')
    {
        sleep(2);
        printf("Philosopher %d is eating\n", i);
        state[i] = 'E';
        sem_post(&sem[i]);
    }
    
}

void pickup (int i)
{
    pthread_mutex_lock(&lock);
    state[i] = 'H';
    printf("Philosopher %d is hungry \n", i);
    test(i);
    pthread_mutex_unlock(&lock);
    if (state[i] != 'E')
    {
        sem_wait(&sem[i]);
    }
    sleep(1);
}

void putdown (int i)
{
    pthread_mutex_lock(&lock);
    state[i] = 'T';
    printf("Philosopher %d is finished eating  and is thinking \n", i);
    test((i+5) %5);
    test((i+1) %5);
    pthread_mutex_unlock(&lock);
}

void* philosopher(void* args)
{
    while (1)
    {
        int* id = (int*)args;
        printf("Philosopher %d is thinking and wants to eat \n", *id);
        sleep(1);
        pickup(*id);
        sleep(1);
        putdown(*id);
    }

}

int main(int argc, char *argv[])
{
    pthread_t philosepheres[5];
    for ( int i = 0; i < 5; i++)
    {
        sem_init(&sem[i], 0, 0);
        state[i] = 'T';
    }
    
    for (int i = 0; i < 5; i++)
    {
        // printf("%d \n", i);
        pthread_create(&philosepheres[i], NULL, philosopher, &num[i]);
        printf("philosopher %d created \n", i);
        // pthread_join(philosepheres[i], NULL);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(philosepheres[i], NULL);
    }
    return 0;
}


