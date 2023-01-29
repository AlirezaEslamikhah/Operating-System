#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
double main_result = 0;
pthread_mutex_t lock;




typedef struct 
{
    double* start;
    double* end;
}thread_data;




void* solve(void* args)
{
    pthread_mutex_lock (&lock);
    double start = *((thread_data*)args)->start;
    double end = *((thread_data*)args)->end;
    // printf("in solve start %d , end %d \n", start, end);
    for (double n = start; n < end; n++)
    {
        double temp = 0;
        if (((int)n % 2 == 0) || (int)n == 0)
        {
            temp = 1 / ((2 * n) + 1);
            main_result += temp;
            printf("%f \n", temp);
        }
        else
        {
            temp =  (1 / ((2 * n) + 1));
            main_result -= temp;
            printf("%f \n", -temp);
        }
        // main_result += pow((-1),n) / ((2 * n) + 1);
        // printf("%f \n", main_result);
    }

    pthread_mutex_unlock(&lock);
}


int main(int argc, char *argv[]) 
{
    int main_number;
    int thread_number;
    printf("%s", "Enter the main number: ");
    scanf("%d", &main_number);
    printf("%s", "Enter the thread number: ");
    scanf("%d", &thread_number);
    for (int i = 0; i < thread_number; i++)
    {
        pthread_t thread;
        double start = (main_number / thread_number) * i;
        double end = (main_number / thread_number) * (i + 1);
        if (i == thread_number - 1)
        {
            end = main_number;
        }
        // printf("%s" , "start: ", start, "end: ", end);
        printf("start %f , end %f \n", start, end);
        thread_data *data = (thread_data*)malloc(sizeof(thread_data));
        data->start = &start;
        data->end = &end;
        pthread_create(&thread, NULL, solve, data);
        pthread_join(thread, NULL);
    }
    printf("%s %f \n", "Final Result IS: ", main_result);
    return 0;
}
