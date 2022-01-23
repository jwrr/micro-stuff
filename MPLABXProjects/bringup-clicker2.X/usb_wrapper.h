/* 
 * File:   usb_wrapper.h
 * 
 */

#ifndef USB_WRAPPER_H
#define	USB_WRAPPER_H

#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

bool USB_isUp();

uint8_t USB_print(const char *str);
uint8_t USB_printChar(char c);
bool USB_readLine(char line[], uint16_t maxLen, bool echo);
uint8_t USB_flushPrintBuffer(void);
void USB_printFontBits(char pixForOneLineOfChar);
void USB_printGraphicsLineTrailer(bool showGraphics);
void USB_printGraphicsLineHeader(bool showGraphics);
void USB_printGraphicsLinePixels(bool showGraphics, uint8_t pixVal);
void USB_printWave(void);

void USB_setPrompt(char *newPrompt);
const char *USB_getPrompt(void);
void USB_setEnablePrompt(bool newVal);
bool USB_getEnablePrompt();
void USB_setEchoCommand(bool newVal);
bool USB_getEchoCommand(void);
void USB_setEchoChar(bool newVal);
bool USB_getEchoChar(void);
char *USB_getTmpStr(void);

#define USB_LINELEN 255
#define USB_WRITE_BUFFER_SIZE 2048
#define USB_WRITE_MAX_TX 200
#define USB_EOL "\n\r"
#define USB_PROMPT USB_getPrompt()
#define USB_printEOL() USB_print(USB_EOL)
#define USB_printLine(S) USB_print(S); USB_printEOL()
#define USB_printf(...) sprintf(USB_getTmpStr(), __VA_ARGS__); USB_print(USB_getTmpStr())
#define USB_printfLine(...) USB_printf(__VA_ARGS__); USB_printEOL()
#define USB_printPrompt() if (USB_getEnablePrompt()) USB_print(USB_PROMPT)
#define USB_printfLinePrompt(...) USB_printf(__VA_ARGS__); USB_printEOL(); USB_printPrompt()
#define USB_printLinePrompt(S) USB_printLine(S); USB_printPrompt()

#define USB_printLines(L) do {\
        uint8_t i;\
        for (i=0; L[i][0] != '\0'; i++) {\
            USB_printLine(L[i]);\
        }\
    } while(0)

#define centerf(W,S,...) do {\
        sprintf(USB_getTmpStr(),__VA_ARGS__);\
        DISP_center(W, S, USB_getTmpStr());\
    } while(0)


#endif	/* USB_WRAPPER_H */

