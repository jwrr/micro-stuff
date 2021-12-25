/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  PIC24FJ1024GB610
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB 	          :  MPLAB X v5.45
 */

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
 */

/**
  Section: Included Files
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/usb/usb.h"

static uint8_t readBuffer[CDC_DATA_OUT_EP_SIZE];
static uint8_t writeBuffer[CDC_DATA_IN_EP_SIZE];

static bool G_usbEcho = true;
#define USB_LINELEN 255
#define USB_PASSWORD "abc"

char *G_version = "1.2.3";
double G_voltage = 17.62;
double G_temperature = 25.0;
uint8_t G_mode0 = 0;
uint8_t G_mode1 = 0;
uint8_t G_trig = 0;


char prompt[] = "\n\r> ";
char help[] = "\n\r"
        "Help Menu\n\r"
        "-----------------\n\r"
        "mode0 [a | b | c]\n\r"
        "mode1 [d | e | f]\n\r"
        "trig  [on | off]\n\r"
        "status\n\r"
        "prev\n\r"
        "next\n\r"
        "sel\n\r"
        "load\n\r"
        "erase\n\r"
        "clear\n\r"
        "unlock [password]\n\r"
        "lock\n\r"
        "> "
        ;


#define NUM_WAVEFORMS 16
#define WAVEFORM_SIZE 512
uint16_t G_waveforms[NUM_WAVEFORMS][WAVEFORM_SIZE];


// this isn't used??? FIXME/DELETME

void APP_DeviceCDCBasicDemoInitialize()
{
    line_coding.bCharFormat = 0;
    line_coding.bDataBits = 8;
    line_coding.bParityType = 0;
    line_coding.dwDTERate = 9600;
}

bool usbUp()
{
    /* If the USB device isn't configured yet, we can't really do anything
     * else since we don't have a host to talk to.  So jump back to the
     * top of the while loop. */
    if (USBGetDeviceState() < CONFIGURED_STATE)
    {
        return false;
    }

    /* If we are currently suspended, then we need to see if we need to
     * issue a remote wakeup.  In either case, we shouldn't process any
     * keyboard commands since we aren't currently communicating to the host
     * thus just continue back to the start of the while loop. */
    if (USBIsDeviceSuspended() == true)
    {
        return false;
    }

    CDCTxService();

    /* Make sure that the CDC driver is ready for a transmission.
     * Check to see if there is a transmission in progress, if there isn't, then
     * we can see about performing an echo response to data received.
     */
    //    if (USBUSARTIsTxTrfReady() == false)
    //        return false;

    return true;
} // usbUp

uint8_t usbPutString(uint8_t str[])
{
    if (!usbUp())
    {
        return 0;
    }

    uint8_t len = strlen((char*) str);
    putUSBUSART(str, len);

    return 1;
} // usbPutString

bool usbGetLine(uint8_t line[], uint8_t maxLen)
{
    static uint8_t linepos = 0;
    uint8_t ch;

    if (!usbUp())
    {
        return false;
    }
    uint8_t numBytesRead = getsUSBUSART(readBuffer, 1);
    if (numBytesRead == 0)
    {
        return false;
    }
    if (readBuffer[0] == 0x0D)
    {
        linepos = 0;
        return true;
    }
    if (G_usbEcho)
    {
        putUSBUSART(readBuffer, 1);
    }

    ch = readBuffer[0];
    if (linepos >= maxLen - 1) // overflow error
    {
        line[maxLen - 1] = '\0';
        linepos = 0;
        return true; // end of line
    }
    else if (ch == '\b')
    {
        if (linepos > 0) linepos--;
    }
    else if (ch == 0x0A) // ignore return
    {
        // skip
    }
    else
    {
        line[linepos++] = ch;
        line[linepos] = '\0';
    }
    return false;
} // usbGetLine

char *getArg(char *line)
{
    uint8_t i = 0;
    for (; line[i] != ' ' && line[i] != '\0'; i++);
    if (line[i] == '\0') return NULL;
    i++;
    if (line[i] == '\0') return NULL;
    char *argPtr = &(line[i]);
    return argPtr;
}

uint8_t setVal(char *line, char *name)
{
    char *cmdValStr;
    uint8_t cmdVal = 0;
    cmdValStr = getArg(line);
    if (cmdValStr != NULL)
    {
        cmdVal = atoi(cmdValStr);
    }
    sprintf((char *) writeBuffer, "\n\r%s = %d\n\r> ", name, cmdVal);
    putsUSBUSART((char *) writeBuffer);
    return cmdVal;
}


// ===============================================================
// ===============================================================
// ===============================================================

/*
                         Main application
 */
int main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    uint8_t state = 0;
    uint8_t numBytes = 0;
    bool eoln;
    uint8_t line[USB_LINELEN];
    bool usbLocked = true;
    uint8_t i;

    while (1)
    {
        switch (state)
        {
        case 0:
            numBytes = usbPutString((uint8_t*) "Hello from PIC 555\n\r> ");
            if (numBytes > 0)
            {
                state = 1;
            }
            break;
        case 1:
            eoln = usbGetLine(line, USB_LINELEN);
            if (eoln)
            {
                if (strncmp((char*) line, "unlock", 6) == 0)
                {
                    uint8_t pwLen = strlen(USB_PASSWORD);
                    if (strncmp((char*) &line[7], USB_PASSWORD, pwLen) == 0)
                    {
                        putsUSBUSART("\n\rUnlocked\n\r> ");
                        usbLocked = false;
                    }
                }

                if (usbLocked)
                {
                    putsUSBUSART("\n\rDevice is locked\n\r> ");
                }

                if (strncmp((char*) line, "help", 4) == 0)
                {
                    putsUSBUSART(help);
                }
                else if (strncmp((char*) line, "lock", 4) == 0)
                {
                    usbLocked = true;
                    putsUSBUSART("\n\rDevice is locked\n\r> ");
                }
                else if (strncmp((char*) line, "mode0", 5) == 0)
                {
                    G_mode0 = setVal((char*) line, "Mode0");
                }
                else if (strncmp((char*) line, "mode1", 5) == 0)
                {
                    G_mode1 = setVal((char*) line, "Mode1");
                }
                else if (strncmp((char*) line, "trig", 4) == 0)
                {
                    G_trig = setVal((char*) line, "Trig");
                }
                else if (strncmp((char*) line, "prev", 4) == 0)
                {
                    putsUSBUSART(prompt);
                }
                else if (strncmp((char*) line, "next", 4) == 0)
                {
                    putsUSBUSART(prompt);
                }
                else if (strncmp((char*) line, "sel", 3) == 0)
                {
                    putsUSBUSART(prompt);
                }
                else if (strncmp((char*) line, "status", 6) == 0)
                {
                    sprintf((char*) writeBuffer, "\n\rVersion: %s\n\rVoltage: %2.2fV\n\rTemperature: %2.1fC\n\rMode: %d %d\n\rActive: %d\n\r> ",
                            G_version, G_voltage, G_temperature, G_mode0, G_mode1, G_trig);
                    putsUSBUSART((char*) writeBuffer);
                }
                else if (strncmp((char*) line, "load", 4) == 0)
                {
                    putsUSBUSART(prompt);
                }
                else if (strncmp((char*) line, "erase", 5) == 0)
                {
                    putsUSBUSART(prompt);
                }
                else if (strncmp((char*) line, "clear", 5) == 0)
                {
                    putsUSBUSART(prompt);
                }
                else
                {
                    sprintf((char*) writeBuffer, "\n\rError 1: Invalid command. %s\n\rEnter 'help' for list of commands\n\r> ", line);
                    putUSBUSART(writeBuffer, strlen((char*) writeBuffer));
                }
                for (i = 0; i < USB_LINELEN; i++)
                {
                    line[i] = '\0';
                }
            }
        default:
            break;
        }

    } // while

    return 1;
}
/**
 End of File
 */

