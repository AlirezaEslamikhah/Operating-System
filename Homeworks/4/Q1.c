#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

struct prime
{
    int value;
    int counter;
} typedef prime;

struct passed_number
{
    int value;
    int pu_number;
} typedef passed_number;


int current_pipe = 0;
int counter = 0;
int number = 100;
int prime_counter = 0;
prime primes[101];


void generate_100_primes()
{
    // generating first 100 prime numbers
    int i = 2;
    int j = 0;
    while (prime_counter < 100)
    {
        bool is_prime = true;
        for (int k = 2; k < i; k++)
        {
            if (i % k == 0)
            {
                is_prime = false;
                break;
            }
        }
        if (is_prime)
        {
            primes[j].value = i;
            primes[j].counter = i;
            prime_counter ++;
            j ++;
        }
        i ++;
    }

}



int pipes [9][2]= {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
// prime pipes[9][2];
// pipes[0] = {prime(0,0),prime(0,0)};

void solve(int read_pipe)
{
    while (1)
    {
        int value[3];
        read(read_pipe,&value,sizeof(value));
        // printf("%d is solving \n",value[1]);
        // printf("current pipe is %d \n",value[0]);
        // printf("The counter is %d \n",value[2]);
        value[1] = value[1] + value[0];
        current_pipe = value[0];
        value[2] --;
        if(value[2] == 0)
        {
            write(pipes[8][1],&value,sizeof(value));
        }
        else
        {
            // sleep(1);
            // int v = value[1];
            // printf("v is %d \n",v);
                value[0] ++; 

            if (value[0] == 0 || value[0] == 8)
            {
                value[0] = 0;
                write(pipes[0][1],&value,sizeof(value));
                // printf("%s","entered next pu \n");
            }
            else
            {
                write(pipes[current_pipe + 1][1],&value,sizeof(value));
                // printf("%s","entered next pu \n");
            }
        }
        // printf("process %d is finished \n",read_pipe);
    }
}

void solve_main(int read_pipe)
{
    while (1)
    {
        int value[3];
        read(read_pipe,&value,sizeof(value));
        printf("ENTERED FINAL PU AND THE VALUE IS %d \n",value[1]);
        if (value[1] == 2436)
        {
            break;
        }
    }
    
    

}






int main(int argc, char const *argv[])
{
    for (int i = 0; i < 9; i++)
    {
        pipe(pipes[i]);
    }
    generate_100_primes();
    // primes[0].value = 4;
    // primes[0].counter = 4;
    int pidd = getpid();
    printf("job started from process %d \n",pidd);
    for (int i = 0; i < 8; i++)
    {
        if (fork() == 0)
        {
            printf("process %d is created \n",i);
            // printf("pipes is %d \n",pipes[i][0]);
            solve(pipes[i][0]);
            // solve(pipes[i][0]);
            // exit(0);
        }
    }
    sleep(1);
    printf("%d \n",primes[2].value);
    for (int i = 0; i < 100; i++)
    {
        int v = primes[i].value;
        int vv = v % 8;
        int counter = primes[i].value;
        int a[3] = {vv,v,counter};
        // v = v + vv; 
        printf("the value is %d and the process pid is %d\n",v,getpid());
        // current_pipe = vv;
        write(pipes[vv][1],&a,sizeof(a));
        // wait(NULL);
    }
    solve_main(pipes[8][0]);
    return 0;
}

