#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <errno.h>

// produce 3GB of data
#define SIZE 3*1024*1024*1024
#define i 805306368
int pip[2];

int main(void)
{
    int *l = (int *)malloc(sizeof(int) * i);

    int data = 4 * 4 / 4 * 2;  // the data to be transported

    printf("Total amount is: %ld\n", i);

    struct iovec io[2];

    struct iovec r[2];


    struct iovec iio [2];

    iio[0] = io[0];

    iio[1] = io[1]; 

    pipe(pip);

    int *w;

    int pid = fork();

    memset(l, 5, sizeof(int) * (size_t)i);

    if (pid == 0)
    {
        int c = 0;

        while (1)
        {
            int *data = (int *)malloc(sizeof(int) * (size_t)i);

            write(pip[1], &data, sizeof(int *));


            sleep(10);


            if (c++ == 1)
            {
                exit(0);
                break;
            }
        }
        
        
    }
    else
    {
        // for (int j = 0; j <data -1 ; j++)
        // {
            
            read(pip[0], &w, sizeof(int *));


            ssize_t n;

            for (int j = 0; j < data - 1; j++)
            {
                io[0].iov_base = &l[0];


                io[0].iov_len = 2 * i;

                io[1].iov_base = &l[1/2 * i];

                io[1].iov_len = 2 * i;

                r[0].iov_base = &w[0];


                r[0].iov_len = 2 * i;

                r[1].iov_base = &w[1/2 * i];

                r[1].iov_len = 2 * i;

            }
            
            

            n = process_vm_writev(pid, &io[0], 1, &r[0], 1, 0);


            // printf("n: %ld\n", n);


            n += process_vm_writev(pid, &io[1], 1, &r[1], 1, 0);

            // printf("n: %ld\n", n);

            printf("DATA WAS TRANSFERED! \n");
        // }
        wait(NULL);   
        
        
    }
    
    return 0;
}