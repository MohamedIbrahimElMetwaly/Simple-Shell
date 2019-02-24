#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

#include "interface.h"
#define size 50
#define delimiter " \n"
int wa= 0;
char* readInput()
{
    char* input = NULL;
    size_t inputSize = 0;

    getline(&input, &inputSize, stdin);
    

return input;

}


char** splitInput(char* input)
{   int i=0; int count = 0;

    

    char** ptr = malloc(size * sizeof(char*));
    if(!ptr)
    {
        printf("ERROR: allocation\n");
    }
    ptr[i] = strtok(input, delimiter);

    while(ptr[i] != NULL)
    {
        i++;
        ptr[i] = strtok(NULL, delimiter);
    }
    
    
    return ptr;
}


void executeCommand(char** ptr)
{   int i = 0;
    int status;
    pid_t pid;
    int flag=0;
    
    

    if(strcmp(ptr[0],"exit()")==0)
    {
        exit(0);
    }
    else if(strcmp(ptr[0],"cd")==0)
    {
        chdir(ptr[1]);   
    }
    else
    {
        while(ptr[i+1] != NULL)  //loop to get last index before NULL
        {i++;}                   //to check if it is & or not

        if(strcmp(ptr[i],"&") ==0)
        {
            flag = 1;
            ptr[i] = NULL;    //remove & before passing ptr to execvp
        }
        
        
        pid = fork();
        if(pid >= 0)    //fork succeded
        {
            if(pid == 0) //child code
            {
                execvp(ptr[0],ptr);
            }   
            else  //parent
            {
                if(flag != 1)   //if there is no & then wait
                    {
                        wait(0);
                    }
                
                signal(SIGCHLD,signalHandler);
            }
        }
        else //fork failed
        {
            printf("fork failed");
        }
    }
}

void signalHandler()
{
    FILE *fptr;
    if(!fptr)
    {
        printf("Error: in FILE");
    }
    if( wa == 0)
    {
    fptr = fopen("log.txt","w");
    fprintf(fptr,"%s","Child is terminated\n");
    fclose(fptr);
    wa = 1;
    }
    else
    {
        fptr = fopen("log.txt","a");
    fprintf(fptr,"%s","Child is terminated\n");
    fclose(fptr);
    }
    
}