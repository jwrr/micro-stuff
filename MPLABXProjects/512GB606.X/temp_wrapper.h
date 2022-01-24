/* 
 * File:   tc74_wrapper.h
 * 
 */

#ifndef TEMP_WRAPPER_H
#define	TEMP_WRAPPER_H

#define I2C_ADDR_TC74  0X4D  // A5 Default

bool TEMP_readTemperature(bool start, int8_t *t);
void TEMP_handleTemperature(uint16_t pollingLoopCnt);
uint16_t TEMP_getTemperature(void);

#endif	/* TEMP_WRAPPER_H */

