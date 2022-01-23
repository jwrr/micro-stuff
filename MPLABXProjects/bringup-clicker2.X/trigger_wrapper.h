/* 
 * File:   trigger_wrapper.h
 * 
 */

#ifndef TRIGGER_WRAPPER_H
#define	TRIGGER_WRAPPER_H

#include <stdbool.h>

void TRIG_handleTrigger(void);
bool TRIG_isSignalOn(void);

bool TRIG_isUSBPressed(void);
void TRIG_setUSBPressed(bool newVal);

#endif	/* TRIGGER_WRAPPER_H */

