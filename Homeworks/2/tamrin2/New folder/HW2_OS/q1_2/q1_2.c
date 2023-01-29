#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "string.h"
#include "pthread.h"
typedef struct {int a; int b;} myarg_t;
int num[100];

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l; 
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}


void merge_(int arr[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_(arr, l, m);
        merge_(arr, m + 1, r);
 
        merge(arr, l, m, r);
    }
}
void merge_sort(void * arg)
{
    myarg_t *args = (myarg_t *) arg;
    int l = args->a;
    int r = args->b;
    if (l < r) {
        int m = l + (r - l) / 2;
        myarg_t arg1 = {l, m};
        myarg_t arg2 = {m + 1, r};
        merge_sort(&arg1);
        merge_sort(&arg2);
        merge(num, l, m, r);
    }
}


void solve(int n,int m)
{
    int s = n/m;
    for(int i = 0; i < m; i++)
    {
        pthread_t thread_id;
        int ss = i * s;
        int e = ss +s;
        myarg_t args = {ss,e};
        pthread_create(&thread_id, NULL,merge_sort, &args);
        pthread_join(thread_id, NULL);
        // pthread_exit(0);
    }
}


int main()
{
    int n ,m;
    printf("%s","Enter the number of elements:");
    scanf("%d",&n);
    printf("%s","Enter the number of segments:");
    scanf("%d",&m);
    if (n % m != 0)
    {
        printf("%s","Mesl adam adad bede \n");
        return 0;
    }
    printf("%s","Enter the elements of array: \n");
    for(int i = 0; i < n; i++)
    {
        scanf("%d",&num[i]);
    }
    solve(n,m);
    merge_(num,0,n-1);
    for (int t = 1; t < n+1; t++)
    {
        printf("%d ",num[t]);
    }
    return 0;

}