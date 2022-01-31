/* 
 * File:   usblib.h
 */

#ifndef USBLIB_H
#define	USBLIB_H

#include <stdbool.h>
#include "ring.h"

bool USB_isUp();
uint16_t USB_read(uint8_t *data, uint16_t maxReadLen);
uint16_t USB_readString(char *str, uint16_t maxStrLen);
int16_t USB_readLine(char *str, uint16_t maxReadLen);
bool USB_maintenance();

extern uint8_t *USB_tmpBuffer;

bool USB_write(uint8_t *data, uint16_t len);
bool USB_writeString(char *str, uint16_t maxStrLen);
bool USB_writeLine(char *str);
#define USB_printLine USB_writeLine
#define USB_printf(...) sprintf(USB_tmpStr, __VA_ARGS__); USB_writeString(USB_tmpStr)
#define USB_printfLine(...) sprintf(USB_tmpStr, __VA_ARGS__); USB_writeLine(USB_tmpStr)

#endif	/* USBLIB_H */

