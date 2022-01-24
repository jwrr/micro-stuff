/* 
 * File:   timer_wrapper.h
 * 
 */

#ifndef TIMER_WRAPPER_H
#define	TIMER_WRAPPER_H

void TMR3_callBack(void);

bool TIME_isTimeMonitorEnabled(void);
void TIME_enableTimeMonitor(bool newVal);

void TIME_clearCount();

#endif	/* TIMER_WRAPPER_H */

