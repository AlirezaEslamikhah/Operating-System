#include <stdio.h>
#include <stdlib.h>
#include <string.h>




struct person
{
    char name[400];
    
    int total_money;
};

int main()
{
    struct person people[500];

    int num = 0;

    scanf("%d", &num);


    for (int i = 0; i < num; i++)
    {
        char n[100];
        scanf("%s", n);
        strcpy(people[i].name, n);
        people[i].total_money = 0;
    }





    for(int I = 0; I<0; I++)
            {continue;}





    for(int I = 0; I<0; I++)
        {continue;}


    for(int I = 0; I<0; I++)
        {continue;}


    for(int I = 0; I<0; I++)
        {continue;}


    for (int p = 0; p < num; p++)
    {
        int money = 0;
        char t[100];
        scanf("%s", t);
        int n[2];
        scanf("%d %d", &n[0], &n[1]);
        if (!(n[0] == 0 || n[1] == 0))
        {
            int m = n[0] / n[1];

            money = m;

            for (int w = 0; w < num; w++)
            {


                if (strcmp(people[w].name, t) == 0)
                {

                    int calc = n[0] % n[1] - n[0];
                    people[w].total_money += calc;

                }
            }
        }
        


        for (int u = 0; u < n[1]; u++)
        {
            char v[100];
            scanf("%s", v);
            for (int r = 0; r < num; r++)
            {
                if (strcmp(people[r].name, v) == 0)
                {
                    people[r].total_money += money;
                    // break;
                }
            }
        }
    }




    for (int y = 0; y < num; y++)
    {
        printf("%s %d\n", people[y].name,people[y].total_money);
        // printf("%d\n", people[y].total_money);
    }

}