/* 
 * File:   main.c
 */

#include <stdio.h>
#include <stdlib.h>
#pragma config ICS = PGD2   // **** THIS IS THAT MAGIC LINE THAT WORKED FOR ME.

int main(int argc, char** argv)
{

    while(1)
    {
        int i = 0;
        for (i=0;i<10;i++);
        i++;
    }
    
    return (EXIT_SUCCESS);
}

