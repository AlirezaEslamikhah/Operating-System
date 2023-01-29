#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

//bounded buffer problem with semaphores
//producer consumer problem


pthread_mutex_t mutex;
sem_t empty;
sem_t full;
int* buffer = NULL;
int pointer_p = 0;
int pointer_c = 0;
int buffer_size = 0;
int producer_count = 0;




int even_or_odd(int num)
{
	if(num % 2 == 0)
		return 1;
	else
		return 0;
}




void* consumer (void* arg) 
{
	int id = (int*) arg;
	int item;
	// while (1) 
	for(int i = 0;i<producer_count;i++)
	{
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		item = buffer[pointer_c];
		int e = even_or_odd(item);

		bool is_even = e == 1 ? true : false;
		if (is_even)
		{
			printf("Consumer Thread %d: I got number %d, and it is even\n",id,item);
		}
		else
			printf("Consumer Thread %d: I got number %d, and it is odd\n",id,item);
		pointer_c = (pointer_c + 1) % buffer_size; 
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
	}
}
 






void* producer (void* arg)
{
	int id = (int*) arg;

	int item;
	// while (1) 
	for(int i = 0;i<producer_count;i++)
	{

		item = rand(); 
		item = item % 100;
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		buffer[pointer_p] = item;
		pointer_p = (pointer_p+1)%buffer_size;
		printf("Producer Thread %d: Generated number %d \n", id,item);
		pthread_mutex_unlock(&mutex);
		sem_post(&full);

	}
}






int main()
{
	printf("%s","Please enter the buffer size: \n");

	int n ;

	scanf("%d", &n);

	printf("%s","Please enter the number each producer creates: \n");
	
	int m ;
	scanf("%d", &m);
	buffer_size = n;
	producer_count = m;

	buffer = (int*)malloc(sizeof(int)*n);

    pthread_mutex_init(&mutex, NULL);
	sem_init(&empty,0,buffer_size);
	sem_init(&full,0,0);


	pthread_t p1;

	pthread_t p2;

	pthread_t p3;

	pthread_t c1;

	pthread_t c2;

	pthread_t c3;

	pthread_create(&p1, NULL, producer, (void*)1);

	pthread_create(&p2, NULL, producer, (void*)2);

	pthread_create(&p3, NULL, producer, (void*)3);

	pthread_create(&c1, NULL, consumer, (void*)1);

	pthread_create(&c2, NULL, consumer, (void*)2);

	pthread_create(&c3, NULL, consumer, (void*)3);

	pthread_join(p1, NULL);

	pthread_join(p2, NULL);

	pthread_join(p3, NULL);

	pthread_join(c1, NULL);

	pthread_join(c2, NULL);

	pthread_join(c3, NULL);


	sem_destroy(&empty);

	sem_destroy(&full);

	pthread_mutex_destroy(&mutex);

	return 0;
}