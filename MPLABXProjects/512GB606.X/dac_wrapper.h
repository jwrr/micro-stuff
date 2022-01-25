/* 
 * File:   dac_wrapper.h
 *
 */

#ifndef DAC_WRAPPER_H
#define	DAC_WRAPPER_H

//bool DAC_write(bool start, uint16_t value);

void DAC_SPI2_initialize(void);
void DAC_writeSPI(bool start, uint16_t value);

#endif	/* DAC_WRAPPER_H */

