/* 
 * File:   gpio_wrapper.h
 * 
 */

#ifndef GPIO_WRAPPER_H
#define	GPIO_WRAPPER_H

// #define CLICKER2

#ifdef EXP1632
#define BUTTON1 'D',6
#define BUTTON2 'D',7
#define BUTTON3 'A',7
#define BUTTON4 'D',13
#endif

#ifdef CLICKER2
#define LED1 'G',13
#define LED2 'E',8
#define BUTTON1 "RA0"
#define BUTTON2 "RE2"

#define GPIO_TRIGGER_BUTTON "RA0"
#define GPIO_LEFT_BUTTON    "RG0"
#define GPIO_CENTER_BUTTON  "RD6"
#define GPIO_RIGHT_BUTTON   "RF2"

#else

#define GPIO_TRIGGER_BUTTON "RD10"
#define GPIO_LEFT_BUTTON    "RD9"
#define GPIO_CENTER_BUTTON  "RF4"
#define GPIO_RIGHT_BUTTON   "RD11"
#endif
    
#define GPIO_isPressed(BUTTON) (!GPIO_get(BUTTON))


#include <stdint.h>
#include <stdbool.h>

#define GPIO_DAC_CS 'E',4
#define GPIO_DISP_CS 'G',8


void GPIO_set(char port, uint8_t pos, bool value);
void GPIO_toggle(char port, uint8_t pos);
void GPIO_toggle(char port, uint8_t pos);
bool GPIO_get(char *pin);
bool GPIO_edgeDetect(char *pin, bool *val, uint8_t whichEdge);
void GPIO_handleButtons();

#endif	/* GPIO_WRAPPER_H */

