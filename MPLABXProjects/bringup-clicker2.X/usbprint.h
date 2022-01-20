/* 
 * File:   usbprint.h
 * Author: robin
 *
 * Created on January 20, 2022, 8:36 AM
 */

#ifndef USBPRINT_H
#define	USBPRINT_H

#include <stdio.h>

uint8_t USB_Print(char *str);
#define USB_LINELEN 255
#define USB_WRITE_BUFFER_SIZE 2048
#define USB_WRITE_MAX_TX 200
#define USB_EOL "\n\r"
#define USB_PROMPT G_prompt
#define USB_PrintEOL() USB_Print(USB_EOL)
#define USB_PrintLine(S) USB_Print(S); USB_PrintEOL()
#define USB_Printf(...) sprintf(USB_tmpStr, __VA_ARGS__); USB_Print(USB_tmpStr)
#define USB_PrintfLine(...) USB_Printf(__VA_ARGS__); USB_PrintEOL()
#define USB_PrintPrompt() if (G_enablePrompt) USB_Print(USB_PROMPT)
#define USB_PrintfLinePrompt(...) USB_Printf(__VA_ARGS__); USB_PrintEOL(); USB_PrintPrompt()
#define USB_PrintLinePrompt(S) USB_PrintLine(S); USB_PrintPrompt()

#define USB_PrintLines(L) do {\
        uint8_t i;\
        for (i=0; L[i][0] != '\0'; i++) {\
            USB_PrintLine(L[i]);\
        }\
    } while(0)

#define centerf(W,S,...) do {\
        sprintf(USB_tmpStr,__VA_ARGS__);\
        center(W, S, USB_tmpStr);\
    } while(0)


#endif	/* USBPRINT_H */

