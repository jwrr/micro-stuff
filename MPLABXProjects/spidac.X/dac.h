/* 
 * File:   dac_wrapper.h
 *
 */

#ifndef DAC_H
#define	DAC_H

#include <stdbool.h>
#include <stdint.h>

#define Nop2() Nop(); Nop()
#define Nop3() Nop2(); Nop()
#define Nop4() Nop2(); Nop2()
#define Nop8() Nop4(); Nop4()
#define Nop11() Nop8(); Nop3()
#define Nop13() Nop11(); Nop2()
#define Nop15() Nop13(); Nop2()
#define Nop16() Nop8(); Nop8()
#define Nop17() Nop15(); Nop2()
#define Nop19() Nop17(); Nop2()
#define Nop21() Nop19(); Nop2()
#define Nop23() Nop21(); Nop2()


#define Nop470p5KHz() Nop11()
#define Nop444p4KHz() Nop13()
#define Nop421p0KHz() Nop15()
#define Nop400p0KHz() Nop17()
#define Nop380p9KHz() Nop19()
#define Nop364p3KHz() Nop21()
#define Nop347p8KHz() Nop23()

void DAC_setCS(uint16_t hi, uint16_t lo);

void DAC_writeSPI(uint16_t value);
void DAC_writeSPI1(uint16_t dacVal);
void DAC_writeSPI2(uint16_t dacVal);

#endif	/* DAC_H */

