/* mycomp.c */
#include <stdio.h>
#include <string.h>
#include "complex.h"
#include "commands.h"

/* define the maximum length for input string */
#define MAX_INPUT 100

int main(void)
{
    char input[MAX_INPUT]; /* buffer to store user input */
    Complex vars[6];       /* array to store 6 complex variables */
    int i;               
    
    /* initialize all complex variables */
    for (i = 0; i < 6; i++)
    {
        init_comp(&vars[i]); 
    }

    printf("\nWelcome to the Complex Number Calculator!\n");
    printf("Enter commands (type 'stop' to exit):\n");

    while (1) /* infinite loop to keep reading user input */
    {
        printf(">> "); 

        /* read user input and check if EOF occurred */
        if (fgets(input, MAX_INPUT, stdin) == NULL)
        {
            /* if fgets fails, input ended unexpectedly */
            printf("\nError: Input ended unexpectedly\n");
            break;
        }

        /* echo the input back to the user */
        printf("%s", input);

        /* check if input ends with a newline and remove it */
        if (input[strlen(input) - 1] == '\n')
        {
            input[strlen(input) - 1] = '\0'; /* replace newline with null terminator */
        }

        /* process the command entered by the user */
        if (process_command(input, vars) == -1)
        {
            /* stop command was entered, so exit the loop */
            break;
        }
    }

    return 0; /* return 0 to indicate successful program execution */
}
