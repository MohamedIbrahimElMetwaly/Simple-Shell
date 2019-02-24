#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define size 50
#include "interface.h"

int main()
{
    char **ptr = malloc(size * sizeof(char*));
    char *input;
    
    printf("\t\t\tSimple Shell\n");
    while(1)
    {   printf(">");
        input =readInput();
        ptr = splitInput(input);
        executeCommand(ptr);
        signalHandler();
    }
}