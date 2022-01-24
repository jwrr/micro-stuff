/* 
 * File:   adc_wrapper.h
 * 
 */

#ifndef ADC_WRAPPER_H
#define	ADC_WRAPPER_H

bool ADC_readVoltage(bool start, int16_t *v);
void ADC_handleBatteryVoltage(uint16_t pollingLoopCnt);


#endif	/* ADC_WRAPPER_H */

