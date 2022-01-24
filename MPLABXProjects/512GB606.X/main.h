/* 
 * File:   main.h
 *
 * Created on January 3, 2022, 9:34 AM
 */

#ifndef MAIN_H
#define	MAIN_H

#define USB_LINELEN 255

char     G_outStr[2048];
char     G_mostRecentCommand[22] = "";

char     G_version[20]  = "1.2.3";
double   G_voltage      = 17.62;
double   G_temperature  = 25.0;

uint8_t  G_config           = 0;
uint8_t  G_usb              = 0;
uint8_t  G_usbTrig          = 0;
uint8_t  G_usbLeft          = 0;
uint8_t  G_usbRight         = 0;
uint8_t  G_usbSel           = 0;
uint8_t  G_state            = 0;
bool     G_run_usb          = false;
bool     G_refreshScreen    = false;
bool     G_usbLocked        = false;
bool     G_usbEcho          = true;
bool     G_selfTestResult   = true; // true = pass; false = fail
bool     G_engineeringMode  = false;
uint8_t  G_customLoadIndex  = 0;
bool     G_waveLoadInProgress = false;
bool     G_customLoaded     = false;
bool     G_forceDisplayUpdate = false;
uint32_t G_spinTime         = 10000;

#endif	/* MAIN_H */

