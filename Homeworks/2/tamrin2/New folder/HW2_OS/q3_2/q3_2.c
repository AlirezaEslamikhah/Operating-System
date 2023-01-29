#include<stdio.h>
#include <string.h>
#include <stdlib.h>

//Using system(), we can execute any command that can run on terminal if operating system allows. 
//For example, we can call system(“dir”) on Windows and system(“ls”) to list contents of a directory.
//We can also use system(“gcc -o hello hello.c”) to compile a C program and system(“./hello”) to run it.
//We can also use system(“rm hello”) to delete the executable file.
//Some common uses of system() in Windows OS are, system(“pause”) which is used to execute pause command and make the screen/terminal wait for a key press,
// and system(“cls”) which is used to make the screen/terminal clear.
//However, making a call to system command should be avoided due to the following reasons:
//It’s a very expensive and resource heavy function call
// It’s not portable: Using system() makes the program very non-portable i.e. 
// this works only on systems that have the pause command at the system level, like DOS or Windows. 
// But not Linux, MAC OSX and most others.

int main(int argc, char const *argv[])
{
    int fork_id = fork();
    if (fork_id == 0)
    {
        //the result is system(cat filename)
        char command[100] = "cat";
        char file[100] ;
        strcpy(file,argv[1]);
        strcat(command, " ");
        strcat(command, file);
        system(command);
    }
    
    
    
    return 0;
}