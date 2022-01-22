/* 
 * File:   usbprint.h
 * Author: robin
 *
 * Created on January 20, 2022, 8:36 AM
 */

#ifndef USBPRINT_H
#define	USBPRINT_H

#include <stdio.h>

uint8_t USB_print(char *str);
#define USB_LINELEN 255
#define USB_WRITE_BUFFER_SIZE 2048
#define USB_WRITE_MAX_TX 200
#define USB_EOL "\n\r"
#define USB_PROMPT G_prompt
#define USB_printEOL() USB_print(USB_EOL)
#define USB_printLine(S) USB_print(S); USB_printEOL()
#define USB_printf(...) sprintf(USB_tmpStr, __VA_ARGS__); USB_print(USB_tmpStr)
#define USB_printfLine(...) USB_printf(__VA_ARGS__); USB_printEOL()
#define USB_printPrompt() if (G_enablePrompt) USB_print(USB_PROMPT)
#define USB_printfLinePrompt(...) USB_printf(__VA_ARGS__); USB_printEOL(); USB_printPrompt()
#define USB_printLinePrompt(S) USB_printLine(S); USB_printPrompt()

#define USB_printLines(L) do {\
        uint8_t i;\
        for (i=0; L[i][0] != '\0'; i++) {\
            USB_printLine(L[i]);\
        }\
    } while(0)

#define centerf(W,S,...) do {\
        sprintf(USB_tmpStr,__VA_ARGS__);\
        center(W, S, USB_tmpStr);\
    } while(0)


#endif	/* USBPRINT_H */

