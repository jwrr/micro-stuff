/* 
 * File:   main.c
 * Author: robin
 *
 * Created on January 26, 2022, 10:46 PM
 */

#include <stdio.h>
#include <stdlib.h>
#pragma config ICS = PGD2               // ICD Communication Channel Select bits (Communicate on PGEC2 and PGED2)

/*
 * 
 */
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

