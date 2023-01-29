#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int* input;






void selection_sort(int start, int end)
{
    for (int i = start; i < end; i++)
    {


        int min = i;
        for (int j = i + 1; j < end; j++)
        {
            if (input[j] < input[min])
            {
                min = j;
            }
        }

        int temp = input[i];

        input[i] = input[min];

        input[min] = temp;
    }
    printf("Sorted %d to %d \n", start, end);

    for (int i = start; i < end; i++)
    {
        printf("%d ", input[i]);
    }
    
    printf("\n");
}







void bubble_sort(int start, int end)
{



    for (int i = start; i < end; i++)
    {
        for (int j = start; j < end - i; j++)
        {
            if (input[j] > input[j + 1])
            {
                int temp = input[j];
                input[j] = input[j + 1];
                input[j + 1] = temp;
            }
        }
    }
    // printf("Sorted %d to %d \n", start, end);
    // for (int i = start; i < end; i++)
    // {
    //     printf("%d ", input[i]);
    // }
    // printf("\n");
    
    
}

void merge(int start, int middle, int end)
{


    int i, j, k;

    int n1 = middle - start + 1;

    int n2 = end - middle;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = input[start + i];
    for (j = 0; j < n2; j++)
        R[j] = input[middle + 1 + j];
    i = 0;
    j = 0;
    k = start;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            input[k] = L[i];
            i++;
        }
        else
        {
            input[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        input[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        input[k] = R[j];
        j++;
        k++;
    }

    bubble_sort(start, end);
}


int main()
{
    struct shmid_ds buf;

    int shk;

    shk = shmget(IPC_PRIVATE, 1024, IPC_CREAT | 0666);
    
    input = shmat(shk,(void*) 0, SHM_RND);

    printf("Enter the number of elements: ");

    int n;

    scanf("%d", &n);

    printf("Enter the elements: ");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &input[i]);
    }
    int middle = n / 2;

    int start = 0;

    int end = n - 1;

    int pid = fork();
    
    if (pid == 0)
    {
        printf("entered child 1 and the start is %d and the middle is %d \n", start, middle);
        input = shmat(shk,(void*) 0, SHM_RND);
        selection_sort(start, middle);
        exit(0);
    }
    else
    {
        int pid2 = fork();
        if (pid2 == 0)
        {
            sleep(1);
            printf("entered child 2 and the middle is %d and the end is %d \n", middle + 1, end);
            input = shmat(shk,(void*) 0, SHM_RND);
            selection_sort(middle , end);
            exit(0);
        }
        else
        {
            sleep(3);
            printf("entered parent and the start is %d and the middle is %d and the end is %d \n", start, middle, end);
            merge(start, middle, end+1);
            shmctl(shk, IPC_RMID, &buf);
        }
    }


    for (int i = 1; i < n+1; i++)
    {
        printf("%d ", input[i]);
    }
    
    printf("\n");

    return 0;
}
