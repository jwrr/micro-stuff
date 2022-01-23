/* 
 * File:   tc74_wrapper.h
 * 
 */

#ifndef TC74_WRAPPER_H
#define	TC74_WRAPPER_H

#define I2C_ADDR_TC74  0X4D  // A5 Default

bool TC74_readTemp(bool start, int8_t *t);

#endif	/* TC74_WRAPPER_H */

