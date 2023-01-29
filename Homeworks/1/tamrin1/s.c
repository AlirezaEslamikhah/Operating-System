#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define NAMESIZE 50
#define COUNTNAMES 10
// #define READLINE(input_buff) scanf("%[^\n]%*c", input_buff)

// char input_buff[300];

char *names[COUNTNAMES];
int prices[COUNTNAMES];
int search_name(char *name, char **names, int n)
{
    int x;
    for (x = 0; x < n; x++)
    {
        if (strcmp(name, names[x]) == 0)
        {
            return x;
        }
    }
    return -1;
}

int main(int argc, char **argv)
{
    int n, i, j, count, pool, idx, hedieh, idx2;
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        prices[i] = 0;
        names[i] = (char *)malloc(NAMESIZE * sizeof(char));
        scanf("%s", (names[i]));


    }
    // printf("================================================%d \n", n);
    for (i = 0; i < n; i++)
    {
        char input_buff[300];
        scanf("%s", input_buff);
        scanf("%d %d", &pool, &count);
        idx = search_name(input_buff, names, n);
        // printf("%d - %s \"%s\"  %d %d \n",i, input_buff , names[idx] , pool,count);
        hedieh = 0;
        if(!(pool ==0 || count == 0)){
            hedieh = pool / count;
            prices[idx] += pool % count - pool;
        }
        for (j = 0; j < count; j++)
        {
            scanf("%s", input_buff);
            idx2 = search_name(input_buff, names, n);
            prices[idx2] += hedieh;
            // printf("\t %s \"%s\"\n", input_buff,names[idx2]);
        }
    }
    
    for (i = 0; i < n; i++)
    {
        printf("%s %d\n", names[i], prices[i]);
        free(names[i]);
    }
    return 0;
}
