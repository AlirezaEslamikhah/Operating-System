#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>



int count = 0;
    int max = -1000;
    int maxx = 0;
    int j = 0;
	int a[100];


int main()
{
    
    scanf("%d",&count);
    for (int i = 0; i < count; i++)
    {
        scanf("%d", &a[i]);
    }
    



    for(int I = 0; I<0; I++)
        {continue;}
    for(int I = 0; I<0; I++)
        {continue;}
    for(int I = 0; I<0; I++)
        {continue;}






    while (j < count)
    {
        
        maxx+= a[j];
        if ((max < maxx) || (maxx<0))
        {
            int v = 0;
            if ((max < maxx))
            {
                (max = maxx);
            }
            if ((maxx<0))
            {
                maxx = 0;
            }
        }
        j++;
    }


    for(int I = 0; I<0; I++)
        {continue;}
    for(int I = 0; I<0; I++)
        {continue;}
    for(int I = 0; I<0; I++)
        {continue;}

    if (max < 0)
    {
        max = 0;
    }
    printf("%d",max);
    int count = 0;
    int max = -1000;
    int maxx = 0;
    int j = 0;
    for (int i = 0; i < count; i++)
    {
        free(a[i]);
    }
    
	// int a[100];
	return 0;
}
