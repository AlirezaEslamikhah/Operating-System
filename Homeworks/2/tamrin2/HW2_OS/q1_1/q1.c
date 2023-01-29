#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>



int num[100];
int tmp[100];
int tmp_flag = 0;

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void merge_(int arr[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
 
        merge(arr, l, m, r);
    }
}
void bubble_sort (int begin,int end,int n)
{
    int i, j;
    for (i = begin; i < end-1; i++)
        for (j = begin; j < end-i-1; j++)
            if (num[j] > num[j+1])
                swap(&num[j], &num[j+1]);
}

void quick_sort(int begin,int end)
{
    if(begin < end)
    {
        int i = begin;
        int j = end;
        int key = num[begin];
        while(i < j)
        {
            while(i < j && num[j] >= key)
            {
                j--;
            }
            num[i] = num[j];
            while(i < j && num[i] <= key)
            {
                i++;
            }
            num[j] = num[i];
        }
        num[i] = key;
        quick_sort(begin,i-1);
        quick_sort(i+1,end);
    }
}

void merge_sort(int arr[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
 
        merge(arr, l, m, r);
    }
}



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
void solve(int n,int m)
{
    int s = n/m;
    // s--;
    for(int i = 0; i < m; i++)
    {
        if (vfork() == 0)
        {
            int ss = i * s;
            int e = ss +s;
            // bubble_sort(s,e,n);
            merge_sort(num,ss,e);
            // quick_sort(ss,e);
            // sort(num,ss,e);
            exit(0);
        }
    }
    for(int j = 0; j < m; j++)
    {
        wait(NULL);
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
    // scanf("%d",&num);
    int s = m /n;
    merge_(num,0,n-1);
    for (int t = 1; t < n+1; t++)
    {
        printf("%d ",num[t]);
    }
    return 0;
}