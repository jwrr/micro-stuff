/* 
 * File:   gpio.h
 * Author: jwrr
 *
 */

#ifndef GPIO_H
#define	GPIO_H

////#define GPIO_DAC_CS "E4"
////#define LED1 "G13"
////#define LED2 "E8"
//
//#define getLED2() (LED2_PORT & LED2_BIT)
//#define clrLED2() LED2_PORT &= ~LED2_BIT
//#define setLED2() LED2_PORT |= LED2_BIT
//#define togLED2() LED2_PORT ^= LED2_BIT

#define GPIO_LED1 GPIO_LED1
#define GPIO_LED1_PORT LATG
#define GPIO_LED1_BIT 13


#define GPIO_LED2 GPIO_LED2
#define GPIO_LED2_PORT LATE
#define GPIO_LED2_BIT 8

#define GPIO_DACCS GPIO_DACCS
#define GPIO_DACCS_PORT LATE
#define GPIO_DACCS_BIT 4
#define GPIO_DACSPI SPI2

#define GPIO_concat(A,B) A ## B
#define GPIO_clr(NAME) GPIO_concat(NAME,_PORT) &= ~(1 << GPIO_concat(NAME,_BIT))
#define GPIO_set(NAME) GPIO_concat(NAME,_PORT) |= (1 << GPIO_concat(NAME,_BIT))
#define GPIO_toggle(NAME) GPIO_concat(NAME,_PORT) ^= (1 << GPIO_concat(NAME,_BIT))

#define GPIO_pulseHi(NAME, DURATTION) \
do {\
const uint16_t pulseCnt = 0;\
GPIO_set(NAME);\
for(;pulseCnt<DURATION; pulseCnt++) {}\
GPIO_clr(NAME);\
}while(0)




#endif	/* GPIO_H */

