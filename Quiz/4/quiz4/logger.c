#include <stdio.h>

#include <stdlib.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <string.h>


#include <unistd.h>

#include <semaphore.h>

#include <sys/mman.h>










#define MAX_BUFFERS 10

#define LOGFILE "/tmp/example.log"

#define SEM_MUTEX_NAME "/sem-mutex"

#define SEM_BUFFER_COUNT_NAME "/sem-buffer-count"

#define SEM_SPOOL_SIGNAL_NAME "/sem-spool-signal"

#define SHARED_MEM_NAME "/posix-shared-mem-example"

struct shared_memory {
    char buf [MAX_BUFFERS] [256];
    int buffer_index;
    int buffer_print_index;
};

void error (char *msg);

int main (int argc, char **argv)
{
    struct shared_memory *shared_mem_ptr;

    sem_t *mutex_sem, *buffer_count_sem, *spool_signal_sem;

    int fd_shm, fd_log;

    char mybuf [256];
    
    




    if ((fd_log = open (LOGFILE, O_CREAT | O_WRONLY | O_APPEND | O_SYNC, 0666)) == -1)
        error ("fopen");





    if ((mutex_sem = sem_open (SEM_MUTEX_NAME, O_CREAT, 0660, 0)) == SEM_FAILED)
        error ("sem_open");




    if ((fd_shm = shm_open (SHARED_MEM_NAME, O_RDWR | O_CREAT | O_EXCL, 0660)) == -1)
        error ("shm_open");

    if (ftruncate (fd_shm, sizeof (struct shared_memory)) == -1)
       error ("ftruncate");
    
    if ((shared_mem_ptr = mmap (NULL, sizeof (struct shared_memory)
    , PROT_READ | PROT_WRITE
    , MAP_SHARED,
            fd_shm
            , 0)
            )             == MAP_FAILED)
       error ("mmap");


    shared_mem_ptr -> buffer_index = shared_mem_ptr -> buffer_print_index = 0;

    if ((buffer_count_sem = sem_open (SEM_BUFFER_COUNT_NAME, O_CREAT | O_EXCL, 0660, MAX_BUFFERS)) == SEM_FAILED)
        error ("sem_open");





    if ((spool_signal_sem = sem_open (SEM_SPOOL_SIGNAL_NAME, O_CREAT | O_EXCL, 0660, 0)) == SEM_FAILED)
        error ("sem_open");





    if (sem_post (mutex_sem) == -1)
        error ("sem_post: mutex_sem");

    while (1) 
    { 

        if (sem_wait (spool_signal_sem) == -1)
            error ("sem_wait: spool_signal_sem");
    
        strcpy (mybuf, shared_mem_ptr -> buf [shared_mem_ptr -> buffer_print_index]);




        (shared_mem_ptr -> buffer_print_index)++;

        if (shared_mem_ptr -> buffer_print_index == 
        MAX_BUFFERS)

           shared_mem_ptr -> buffer_print_index = 0;


        if (sem_post (buffer_count_sem) == -1)
            error ("sem_post: buffer_count_sem");
        


        if (write (fd_log
        , mybuf,
         strlen (mybuf)) 
        != strlen (mybuf))
            error ("write: logfile");
    }
}


void error (char *msg)
{
    perror (msg);
    exit (1);
}