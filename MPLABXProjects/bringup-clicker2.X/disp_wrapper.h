/* 
 * File:   mode.h
 *
 */

#ifndef DISP_WRAPPER_H
#define	DISP_WRAPPER_H

#include <stdbool.h>

#define G_pixPerLine 144
#define G_pixLinesPerScreen 168
#define G_fontWidth  8
#define G_fontHeight 14
#define G_pixBlankLinesBetweenChar 4
#define G_charHeight (G_fontHeight + G_pixBlankLinesBetweenChar)
#define G_txtCharPerLine (G_pixPerLine / G_fontWidth)
#define G_txtLinesPerScreen (G_pixLinesPerScreen / G_fontHeight)


bool DISP_isBusy(void);
void DISP_printScreen(void);
char *DISP_getLinePtr(int lineNumber);
#define DISP_getBatteryLinePtr() DISP_getLinePtr(0)
#define DISP_getTemperatureLinePtr() DISP_getLinePtr(1)
#define DISP_getSignalLinePtr() DISP_getLinePtr(4)

bool DISP_getShowGraphics(void);
void DISP_setShowGraphics(bool newVal);

uint8_t DISP_getScreenWidthInChar(void);
void DISP_setScreenWidthInChar(uint8_t newWidth);


void DISP_append8BitsToPixLine(uint8_t pixVal, uint8_t *pixLine, uint8_t index);

char *DISP_center(uint8_t width, char centered[], const char uncentered[]);
void DISP_handleRightButton(void);
void DISP_handleLeftButton(void);
void DISP_updateMode(void);
const char **DISP_getModeNames(uint8_t m);
void DISP_handleCenterButton();

uint8_t DISP_getModeIndex(void);
uint8_t DISP_getModeSize(uint8_t mode);
uint8_t DISP_getModeSel(void);
void DISP_setModeSel(uint8_t newVal);
const char *DISP_getModeName(uint8_t m);
void DISP_setMode(uint8_t mode, uint8_t val);

uint8_t DISP_sendByteSPI(uint8_t val);
void DISP_drawPixLine(uint8_t addr, uint8_t pixels[]);
uint8_t DISP_reverseBits(uint8_t val);
void DISP_writeFrame(bool start);

bool DISP_getVcom(void);
void DISP_setVcom(bool newVcom);

bool DISP_getStart(void);
void DISP_enableDisplayThisCycle();
void DISP_preventDispThisCycle();

#endif	/* DISP_WRAPPER_H */

