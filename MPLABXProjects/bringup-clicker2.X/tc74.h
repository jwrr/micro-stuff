/* 
 * File:   tc74.h
 * Author: jwrr
 *
 * Created on January 14, 2022, 10:41 AM
 */

#ifndef TC74_H
#define	TC74_H

#define I2C_ADDR_TC74  0X4D  // A5 Default

bool TC74_readTemp(bool start, int8_t *t);

#endif	/* TC74_H */

