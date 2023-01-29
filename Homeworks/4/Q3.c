// implement a simple logger with pipe and fork
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
bool r_is_empty = true;
bool w_is_empty = true;



void write_log(int pid,int write_pipe)
{
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    // char* massage = ("hello from process %d the massage is delivered at %s \n",pid,asctime(timeinfo));
    // while (1)
    // {
        char* massage;
        sprintf(massage,"hello from process %d the massage is delivered at %s \n",pid,asctime(timeinfo));
        write(write_pipe,massage,strlen(massage));
        sleep(1);
    // }
    
    
}

void read_log(int read_pipe)
{
    // while (1)
    // {
        char massage[200];
        read(read_pipe,massage,100);
        // printf("%s",massage);
        //log into a txt file
        FILE *fptr;
        fptr = fopen("log.txt", "a");
        fprintf(fptr, "%s \n", massage);
        fclose(fptr);
    // }
    
    
}

int main()
{
    int pipe1[2];
    int pipe2[2];
    int pipe3[2];
    int pipe4[2];
    pipe(pipe1);
    pipe(pipe2);
    pipe(pipe3);
    pipe(pipe4);

    int pid = fork();
    if (pid == 0)
    {
        sleep(3);
        read_log(pipe1[0]);
        read_log(pipe2[0]);
        read_log(pipe3[0]);
        read_log(pipe4[0]);
        
    }
    else
    {
        int pid2 = fork();
        if (pid2 == 0)
        {
            int pid3 = fork();
            if(pid3 == 0)
            {
                // write_log(pid3,pipe1[1]);
                write_log(getpid(),pipe1[1]);
                exit(0);
            }
            else if(pid3>0)
            {
                // write_log(pid3,pipe2[1]);
                write_log(getpid(),pipe2[1]);
                exit(0);

            }
        }
        else if (pid2 > 0)
        {
             int pid4 = fork();
            if(pid4 == 0)
            {
                // write_log(pid4,pipe3[1]);
                write_log(getpid(),pipe3[1]);
                exit(0);

            }
            else if(pid4>0)
            {
                // write_log(pid4,pipe4[1]);
                write_log(getpid(),pipe4[1]);
                exit(0);

            }
        }
    }
    
}