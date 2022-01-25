/* 
 * File:   adc_wrapper.h
 * 
 */

#ifndef BATT_WRAPPER_H
#define	BATT_WRAPPER_H

bool BATT_readVoltage(bool start, int16_t *v);
void BATT_handleBatteryVoltage(uint16_t pollingLoopCnt);


#endif	/* BATT_WRAPPER_H */

