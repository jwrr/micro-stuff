/* 
 * File:   main.c
 * Author: jwrr
 * Part: PIC16F84A
 * Datasheet: https://ww1.microchip.com/downloads/en/devicedoc/35007b.pdf
 * Created on December 10, 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

/*
 * 
 */
int main(int argc, char** argv) {
    int i;
    TRISA = 0;
    for (i=0; i<6; i++)
    {
        PORTA = 0;
        PORTA = 1;
    }

    return 0;
}
