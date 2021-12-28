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
#define VERSION        "123"
#define MENU_SIZE          5
#define MENU_TIME     200000
#define DEBOUNCE_TIME   2000
#define WAVEFORM_SIZE    512

char *G_version = "1.2.3";
double G_voltage = 17.62;
double G_temperature = 25.0;
uint8_t G_mode0 = 0;
uint8_t G_mode1 = 0;
uint8_t G_trig = 0;
uint8_t G_menuSel = 0;
uint16_t G_waveformTable[WAVEFORM_SIZE];

const char *G_menu[][9] = {
    {"M1",  "M2",  "M3",  NULL,  NULL,  NULL,  NULL,  NULL,  NULL},
    {"T11", "T12", "T13", "T14", "T15", "T16", "T17", "T18", NULL},
    {"T21", "T22", "T23", "T24", NULL,  NULL,  NULL,  NULL,  NULL},
    {"T31", "T32", NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL},
    {NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL}
};


enum button_t {NONE=0, NEXT=1, PREV=2, SEL=4, TRIG=8};

char prompt[] = "\n\r> ";
char help[] = "\n\r"
        "Help Menu\n\r"
        "-----------------\n\r"
        "help (h)\n\r"
        "lock (lock)\n\r"
        "unlock [password]\n\r"
        "status (s)\n\r"
        "mode0 [a | b | c]\n\r"
        "mode1 [d | e | f]\n\r"
        "trig  [on | off] (t)\n\r"
        "load (l)\n\r"
        "erase (e)\n\r"
        "clear (c)\n\r"
        "prev (p)\n\r"
        "next (n)\n\r"
        "sel (sel)\n\r"
        "log (log)\n\r"
        "> "
        ;


#define NUM_WAVEFORMS 16
#define WAVEFORM_SIZE 512
uint16_t G_waveforms[NUM_WAVEFORMS][WAVEFORM_SIZE];


// ===============================================================
// ===============================================================
// ===============================================================

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

void spin(uint32_t cnt)
{
    while (cnt--);
}

// ===============================================================
// ===============================================================
// ===============================================================

static uint8_t len(const char *arr[])
{
    uint8_t i = 0;
    for (i=0; arr[i]!=NULL; i++);
    return i;
}

static bool isPressed(uint8_t button)
{
    bool button_prev = (bool)(~PORTD & 0x0040); // RD6
    bool button_sel  = (bool)(~PORTD & 0x0080); // RD7
    bool button_next = (bool)(~PORTA & 0x0080); // RA7
    bool button_trig = (bool)(~PORTD & 0x2000); // RD13
    switch (button)
    {
    case PREV: return button_prev;
    case NEXT: return button_next;
    case SEL:  return button_sel;
    case TRIG: return button_trig;
    default:   return false;
    }
    return false;
}

static uint8_t debounceButtons(void)
{
    uint8_t button = NONE;
    uint32_t cnt = 0;
    while (cnt < DEBOUNCE_TIME)
    {
        cnt++;
        bool button_trig = isPressed(TRIG);
        bool button_next = isPressed(NEXT);
        bool button_prev = isPressed(PREV);
        bool button_sel  = isPressed(SEL);
        button =    button_trig ? TRIG :
                    button_sel  ? SEL  :
                    button_next ? NEXT :
                    button_prev ? PREV : NONE;
        if (button == NONE) {
            return NONE;
        }
    }
    return button;
}

static void waitIdle(void)
{
    bool wait = true;
    while (wait)
    {
        bool button_next = isPressed(NEXT);
        bool button_prev = isPressed(PREV);
        bool button_sel  = isPressed(SEL);
        wait = button_prev | button_sel | button_next;
    }
}

static double checkBattery()
{
    uint16_t adcResult = 555; // FIXME ADC_Read10bit( ADC_CHANNEL_POTENTIOMETER ) + 1;
    double   batteryLevel = (double)adcResult*18.0/1024;
    return batteryLevel;
}

static void updateDisplay(uint8_t fmt, const char *menu[], uint8_t sel, uint8_t cnt)
{
    double   batteryLevel = checkBattery();

    char str[255];
    switch (fmt)
    {
    case 0:
        sprintf(str, "\f %2.2fV %s\n\r Standby\n\r", batteryLevel, menu[sel]);
        break;
    case 1:
        sprintf(str, "\f %2.2fV %s %s\n\r Standby\n\r", batteryLevel, G_menu[0][G_mode0], menu[sel]);
        break;
    case 2:
        sprintf(str, "\f %2.2fV %s %s\r\n ACTIVE\n\r", batteryLevel, G_menu[0][G_mode0], G_menu[G_mode0+1][G_mode1]);
        break;
    default:
        break;
    }

    
//    bool button_trig = isPressed(TRIG);
//    bool isActive = button_trig;
//    if (isActive) {
//        strcat(str, "ACTIVE ");
//        int i;
//        for (i=0; i<cnt; i++)
//        {
//            strcat(str, "*");
//        }
//        strcat(str, "\r\n");
//    } else {
//        strcat(str, "standby\r\n");
//    }
    if (usbUp()) {
        putsUSBUSART(str);
    }
    printf(str);
}

static uint8_t navMenu(const char *menu[], uint8_t sel, uint8_t displayFormat)
{
    uint8_t menuLen = len(menu);
    if (sel > menuLen-1) {
        sel = 0;
    }

    updateDisplay(displayFormat, menu, sel, 0);
    bool button_trig = isPressed(TRIG);
    bool done = button_trig;

    while (!done)
    {
        waitIdle();
        uint8_t button = NONE;
        while (button == NONE)
        {
            spin(MENU_TIME);
            updateDisplay(displayFormat, menu, sel, 0);
            button = debounceButtons();
        }
        switch (button)
        {
        case NEXT:
            sel = (sel >= menuLen-1) ? 0 : sel + 1;
            break;
        case PREV:
            sel = (sel == 0) ? menuLen - 1 : sel - 1;
            break;
        default:
            break;
        }

        updateDisplay(displayFormat, menu, sel, 0);
        done = (button == SEL) || (button == TRIG);    
    } // while
    return sel;
} // navMenu


static void loadWaveform(uint8_t mode0, uint8_t mode1, uint16_t table[])
{
    static uint8_t mode0_prev = 255;
    static uint8_t mode1_prev = 255;
    
    bool waveformChanged = (mode0 != mode0_prev) || (mode1 != mode1_prev);
    
    if (waveformChanged)
    {
        mode0_prev = mode0;
        mode1_prev = mode1;
        // Copy FLASH to MEM
    }
}

static void xmitWaveform(uint16_t table[])
{
    static uint8_t cnt = 0;
    cnt++;
    cnt = cnt & 0x07;
    spin(200000);
    uint8_t displayFormat = 2;
    updateDisplay(displayFormat, NULL, 0, cnt);
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
    char logStr[USB_LINELEN];
    bool usbLocked = true;
    uint32_t i;
    bool s3;
    bool s4;
    bool s5;
    bool s6;
    uint8_t sall;
    uint8_t sallPrev = 0;
    bool logEnabled = false;

    LATA = 0x0000;
    while (1)
    {
        
        spin(10000);
        s3 = (bool)(~PORTD & 0x0040);
        s4 = (bool)(~PORTD & 0x0080);
        s5 = (bool)(~PORTA & 0x0080);
        s6 = (bool)(~PORTD & 0x2000);
        sall = 8*s6 + 4*s5 + 2*s4 + s3;
                    
        if (s3) {
            LATA = (LATA + 1) & 0x007F;
        } else if (s4) {
            LATA = (LATA + 1) & 0x0003;
        } else if (s5) {
            LATA = (LATA + 1) & 0x000F;
        } else if (s6) {
            LATA = (LATA + 1) & 0x003F;
        }
        
        if (logEnabled && (sall != sallPrev)) {
            sprintf(logStr, "0x%x\n\r", (unsigned int)sall);
            putsUSBUSART(logStr);
            sallPrev = sall;
        }
        
        bool button_trig = isPressed(TRIG);
        if (button_trig)
        {
            loadWaveform(G_mode0, G_mode1, G_waveformTable);
            xmitWaveform(G_waveformTable);
        }
        else
        {
            G_mode1 = navMenu(G_menu[G_mode0+1], G_mode1, 1);
            G_mode0 = navMenu(G_menu[0], G_mode0, 0);
        }

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

                if (strncmp((char*) line, "help", 1) == 0)
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
                else if (strncmp((char*) line, "trig", 1) == 0)
                {
                    G_trig = setVal((char*) line, "Trig");
                }

                else if (strncmp((char*) line, "status", 1) == 0)
                {
                    sprintf((char*) writeBuffer, "\n\rVersion: %s\n\rVoltage: %2.2fV\n\rTemperature: %2.1fC\n\rMode: %d %d\n\rActive: %d\n\r> ",
                            G_version, G_voltage, G_temperature, G_mode0, G_mode1, G_trig);
                    putsUSBUSART((char*) writeBuffer);
                }
                else if (strncmp((char*) line, "log", 1) == 0)
                {
                    logEnabled = !logEnabled;
                    sprintf((char*) writeBuffer, "\n\rLog %s\n\r> ",
                            (logEnabled) ? "ON" : "OFF");
                    putsUSBUSART((char*) writeBuffer);
                }
                else if (strncmp((char*) line, "load", 1) == 0)
                {
                    putsUSBUSART(prompt);
                }
                else if (strncmp((char*) line, "erase", 1) == 0)
                {
                    putsUSBUSART(prompt);
                }
                else if (strncmp((char*) line, "clear", 1) == 0)
                {
                    putsUSBUSART(prompt);
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
                else
                {
                    sprintf((char*) writeBuffer, "\n\r0x%x 0x%x 0x%x Error 1: Invalid command. %s\n\rEnter 'help' for list of commands\n\r> ", 
                            ANSELD, TRISD, s3, line);
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

