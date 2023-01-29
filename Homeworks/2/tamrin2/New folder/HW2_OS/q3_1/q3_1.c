#include<stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    int fork_id = fork();
    if (fork_id == 0)
    {
        FILE* fptr;
        fptr = fopen(argv[1],"r");
        if (!fptr || argc != 2)
        {
            printf("Error opening file");
        }
        char ch;
        while ((ch = fgetc(fptr)) != EOF )
        {
         printf("%c",ch);
        }
        fclose(fptr);

        // for executing the program in terminal use ./a.out filename and press enter
    }
    else 
    {
        wait (NULL);
    }
    
    return 0;
}
