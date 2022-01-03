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

#define USB_PASSWORD "abc"
#define NUM_WAVEFORMS 24
#define WAVEFORM_SIZE 256
#define USB_LINELEN 255

static uint8_t G_readBuffer[CDC_DATA_OUT_EP_SIZE];
static uint8_t G_writeBuffer[CDC_DATA_IN_EP_SIZE];
static uint8_t line[USB_LINELEN] = "";

char     G_version[20]  = "1.2.3";
double   G_voltage      = 17.62;
double   G_temperature  = 25.0;
uint8_t  G_mode[2]      = {0, 0};
uint8_t  G_modeSel      = 0;
uint8_t  G_config       = 0;
uint8_t  G_usb          = 0;
uint8_t  G_trig_usb     = 0;
uint8_t  G_left_usb     = 0;
uint8_t  G_right_usb    = 0;
uint8_t  G_sel_usb      = 0;
uint8_t  G_state        = 0;
bool     G_watchDisplay = false;
bool     G_getStatus    = false;
bool     G_showPixels   = false;
bool     G_usbLocked    = true;
bool     G_usbEcho      = true;
bool     G_selfTestResult   = true; // true = pass; false = fail
uint8_t  G_triggerCountDown = 0;
uint8_t  G_triggerCountDownMax = 5; 
    
uint16_t G_waveformTable[WAVEFORM_SIZE];

char G_screen[13][22] = {
    "CHARGE:       100%\n\r", // 0
    "SELF TEST:    PASS\n\r", // 1
    "                  \n\r", // 2
    "    SIGNAL OFF    \n\r", // 3
    "/-< >             \n\r", // 4
    "<      AAAA      >\n\r", // 5
    "ABCDEFGHIJKLMNOPQR\n\r", // 6
    "<     EEEEEEE    >\n\r", // 7
    "STUVWXYZ0123456789\n\r", // 8
    "  P/N: PN123-01   \n\r", // 9
    "  F/W: FW123-01   \n\r", // 10
    "      USB ON      \n\r", // 11
    "> "
};
//  "123456789012345678", // -

char *G_screenBatteryLevel = &(G_screen[0][14]);
char *G_screenPassFail     = &(G_screen[1][14]);
char *G_screenSignal       = &(G_screen[3][11]);
char *G_screenMode0        = &(G_screen[5][7]);
char *G_screenMode1        = &(G_screen[7][5]);
char *G_screenUSB          = &(G_screen[11][6]);

char prompt[] = "\n\r> ";
char help[] = "\n\r"
        "Help Menu\n\r"
        "-----------------\n\r"
        "help (h)\n\r"
        "lock (lock)\n\r"
        "unlock [password](u)\n\r"
        "load (l)\n\r"
        "erase (e)\n\r"
        "clear (c)\n\r"
        "status (s)\n\r"
        "run (r) - control with asdf. a=left, s=sel, d=right, f=fire trig q=quit\n\r"
        "pixels (p)\n\r"
        "> ";

const char G_modes0[][6+1] = {" AAAA ", "BBBBB ", " CCC ", "DDDDDD"};
const char G_modes1[][8+1] = {" EEEEEE ", " FFFFFFF", "   GGG  "};

enum button_t {NONE=0, RIGHTARROW=1, LEFTARROW=2, SELECT=4, TRIGGER=8};

const uint8_t G_font[][8+1] = {
    {'A',  0x08, 0x14, 0x14, 0x22, 0x3e, 0x41, 0x41, 0x00} /* 0 */,
    {'B',  0x3e, 0x21, 0x21, 0x3e, 0x21, 0x21, 0x3e, 0x00} /* 1 */,
    {'C',  0x1e, 0x21, 0x20, 0x20, 0x20, 0x21, 0x1e, 0x00} /* 2 */,
    {'D',  0x3c, 0x22, 0x22, 0x22, 0x22, 0x22, 0x3c, 0x00} /* 3 */,
    {'E',  0x3f, 0x20, 0x20, 0x38, 0x20, 0x20, 0x3f, 0x00} /* 4 */,
    {'F',  0x3f, 0x20, 0x20, 0x3c, 0x20, 0x20, 0x20, 0x00} /* 5 */,
    {'G',  0x1e, 0x20, 0x20, 0x20, 0x27, 0x21, 0x1e, 0x00} /* 6 */,
    {'H',  0x22, 0x22, 0x22, 0x3e, 0x22, 0x22, 0x22, 0x00} /* 7 */,
    {'I',  0x3e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x3e, 0x00} /* 8 */,
    {'J',  0x0f, 0x02, 0x02, 0x02, 0x22, 0x22, 0x1c, 0x00} /* 9 */,
    {'K',  0x36, 0x24, 0x28, 0x38, 0x24, 0x22, 0x33, 0x00} /* 10 */,
    {'L',  0x38, 0x10, 0x10, 0x10, 0x10, 0x11, 0x3f, 0x00} /* 11 */,
    {'M',  0x41, 0x63, 0x55, 0x49, 0x41, 0x41, 0x41, 0x00} /* 12 */,
    {'N',  0x41, 0x61, 0x51, 0x49, 0x45, 0x43, 0x41, 0x00} /* 13 */,
    {'O',  0x1c, 0x22, 0x41, 0x41, 0x41, 0x22, 0x1c, 0x00} /* 14 */,
    {'P',  0x3c, 0x22, 0x22, 0x22, 0x3c, 0x20, 0x20, 0x00} /* 15 */,
    {'Q',  0x1c, 0x22, 0x41, 0x41, 0x41, 0x22, 0x1c, 0x06} /* 16 */,
    {'R',  0x3c, 0x22, 0x22, 0x3c, 0x24, 0x22, 0x21, 0x00} /* 17 */,
    {'S',  0x1c, 0x22, 0x20, 0x1c, 0x02, 0x22, 0x1c, 0x00} /* 18 */,
    {'T',  0x7f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00} /* 19 */,
    {'U',  0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1c, 0x00} /* 20 */,
    {'V',  0x63, 0x22, 0x22, 0x14, 0x14, 0x1c, 0x08, 0x00} /* 21 */,
    {'W',  0x41, 0x49, 0x49, 0x49, 0x49, 0x55, 0x22, 0x00} /* 22 */,
    {'X',  0x63, 0x22, 0x14, 0x08, 0x14, 0x22, 0x63, 0x00} /* 23 */,
    {'Y',  0x63, 0x22, 0x14, 0x08, 0x08, 0x08, 0x1c, 0x00} /* 24 */,
    {'Z',  0x7f, 0x02, 0x04, 0x08, 0x10, 0x20, 0x7f, 0x00} /* 25 */,
    {'0',  0x1c, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1c, 0x00} /* 26 */,
    {'1',  0x18, 0x18, 0x08, 0x08, 0x08, 0x08, 0x1e, 0x00} /* 27 */,
    {'2',  0x1c, 0x22, 0x02, 0x04, 0x08, 0x10, 0x3e, 0x00} /* 28 */,
    {'3',  0x1c, 0x02, 0x02, 0x0c, 0x02, 0x02, 0x1c, 0x00} /* 29 */,
    {'4',  0x04, 0x0c, 0x14, 0x24, 0x7e, 0x04, 0x06, 0x00} /* 30 */,
    {'5',  0x3c, 0x20, 0x20, 0x3c, 0x02, 0x22, 0x1c, 0x00} /* 31 */,
    {'6',  0x38, 0x40, 0x40, 0x78, 0x44, 0x44, 0x38, 0x00} /* 32 */,
    {'7',  0x3e, 0x02, 0x04, 0x04, 0x08, 0x10, 0x20, 0x00} /* 33 */,
    {'8',  0x1c, 0x22, 0x22, 0x1c, 0x22, 0x22, 0x1c, 0x00} /* 34 */,
    {'9',  0x1c, 0x22, 0x22, 0x1e, 0x02, 0x02, 0x1c, 0x00} /* 35 */,
    {' ',  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} /* 36 */,
    {'<',  0x01, 0x06, 0x1c, 0x70, 0x1c, 0x06, 0x01, 0x00} /* 37 */,
    {'>',  0x40, 0x30, 0x1c, 0x07, 0x1c, 0x30, 0x40, 0x00} /* 38 */,
    {'%',  0x31, 0x52, 0x64, 0x08, 0x13, 0x25, 0x46, 0x00} /* 39 */,
    {':',  0x00, 0x0c, 0x0c, 0x00, 0x0c, 0x0c, 0x00, 0x00} /* 40 */,
    {'/',  0x02, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x00} /* 41 */,
    {'-',  0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00} /* 42 */
};

enum {LETTER_A=0, DIGIT_0=26, SPACE=36, LT=37, GT=38, PERCENT=39, COLON=40,
      SLASH=41, DASH=42};

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

uint8_t usbWrite(char *str)
{
    if (!usbUp())
    {
        return 0; // fail
    }

    while (!USBUSARTIsTxTrfReady()) CDCTxService();
    putsUSBUSART(str);
    while (!USBUSARTIsTxTrfReady()) CDCTxService();

    return 1; // success
} // usbPutString

static bool usbGetLine(uint8_t line[], uint8_t maxLen)
{
    static uint8_t linepos = 0;
    uint8_t ch;

    if (!usbUp())
    {
        return false;
    }
    uint8_t numBytesRead = getsUSBUSART(G_readBuffer, 1);
    if (numBytesRead == 0)
    {
        return false;
    }
    if (G_readBuffer[0] == 0x0D)
    {
        linepos = 0;
        return true;
    }
    if (G_usbEcho)
    {
        putUSBUSART(G_readBuffer, 1);
    }

    ch = G_readBuffer[0];
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


static char usbGetChar()
{
    uint8_t ch;
    if (!usbUp())
    {
        return '\0';
    }
    uint8_t numBytesRead = getsUSBUSART(G_readBuffer, 1);
    if (numBytesRead == 0)
    {
        return false;
    }
    ch = G_readBuffer[0];
    return ch;
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

void spin(uint32_t cnt)
{
    while (cnt--);
}

// ===============================================================
// ===============================================================
// ===============================================================

static bool isPressed(uint8_t button)
{
    bool button_prev = (bool)(~PORTD & 0x0040); // RD6
    bool button_sel  = (bool)(~PORTD & 0x0080); // RD7
    bool button_next = (bool)(~PORTA & 0x0080); // RA7
    bool button_trig = (bool)(~PORTD & 0x2000); // RD13
    switch (button)
    {
    case LEFTARROW: return button_prev;
    case RIGHTARROW: return button_next;
    case SELECT:  return button_sel;
    case TRIGGER: return button_trig;
    default:   return false;
    }
    return false;
}

static uint16_t checkBattery()
{
    double    maxVoltage = 18.0;
    double    minVoltage = 12.0;
    uint16_t  maxADC     = 1023;
    uint16_t  minADC     = (uint16_t)(maxADC * (minVoltage / maxVoltage));
    uint16_t  rangeADC   = maxADC - minADC;
    static uint16_t  actualADC  = 1040; // FIXME ADC_Read10bit( ADC_CHANNEL_POTENTIOMETER ) + 1;
    uint16_t  percent;
    
    
    actualADC = (actualADC <= minADC) ? 1040 : 
                (actualADC > 1023)    ? 1023 : actualADC - 1;
    if (actualADC < minADC)
    {
        percent = 1;
    }
    else if (actualADC > maxADC)
    {
        percent = 100;
    }
    else
    {
        percent = (uint16_t)(100 * (actualADC - minADC) / rangeADC);
    }
    
    return percent;
}

static void changeText(char *str, char *newstr)
{
    int i = 0;
    for (; newstr[i]; i++)
    {
        str[i] = newstr[i];
    }
}


static bool triggerPressed()
{
    static bool trigPrev = false;
    bool trig = isPressed(TRIGGER) || G_trig_usb;
    bool retVal = false;
    if (G_triggerCountDown == 0) {
        retVal = trig && !trigPrev;
    }
    else
    {
        retVal = trig;
    }
    trigPrev = trig;
    return retVal;
}

static void handleTrigger()
{
    static uint8_t trigCnt = 0;
    if (triggerPressed())
    {
        trigCnt = (trigCnt >= 10) ? 0 : trigCnt + 1;
        
        if (G_triggerCountDown == 0)
        {
            G_triggerCountDown = G_triggerCountDownMax;
        }
        else if (trigCnt==0)
        {
            G_triggerCountDown--;
            if (G_triggerCountDown == 0)
            {
                G_trig_usb = false;
            }
        }
    }
    else
    {
        trigCnt = 0;
        G_triggerCountDown = 0;
    }
}

static bool leftPressed()
{
    static bool leftPrev = false;
    bool left = isPressed(LEFTARROW) || G_left_usb;
    G_left_usb = false;
    bool retVal = left && !leftPrev;
    leftPrev = left;
    return retVal;
}

static bool rightPressed()
{
    static bool rightPrev = false;
    bool right = isPressed(RIGHTARROW) || G_right_usb;
    G_right_usb = false;
    bool retVal = right && !rightPrev;
    rightPrev = right;
    return retVal;
}

static bool selPressed()
{
    static bool selPrev = false;
    bool sel = isPressed(SELECT) || G_sel_usb;
    G_sel_usb = false;
    bool retVal = sel && !selPrev;
    selPrev = sel;
    return retVal;
}

static void handleButtons()
{        
    if (leftPressed())
    {
        G_mode[G_modeSel] = (G_mode[G_modeSel]==0) ? 2 : G_mode[G_modeSel] - 1;
    }

    if (rightPressed())
    {
        G_mode[G_modeSel] = (G_mode[G_modeSel]==2) ? 0 : G_mode[G_modeSel] + 1;
    }
        
    if (selPressed())
    {
        G_modeSel = (G_modeSel + 1) % 2;
    }
}

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
}

static void pixelizeLine(char *message)
{
    uint8_t  lineIndex; // Work through each of the 8 font lines
    const uint16_t outstrLen = 14*(18*8+2);
    char     outstr[outstrLen+1];
    uint16_t outstrIndex = 0;
    
    for (outstrIndex = 0; outstrIndex < outstrLen; outstrIndex++)
    {
        outstr[outstrIndex] = '\0';
    }
    
    outstrIndex = 0;
    if (outstrIndex < outstrLen)
    {
        outstr[outstrIndex++] = '\r';
    }
    if (outstrIndex < outstrLen)
    {
        outstr[outstrIndex++] = '\n';
    }
    
    for (lineIndex=1; lineIndex<9; lineIndex++) 
    {
        uint16_t messageIndex = 0;
        for (messageIndex = 0; message[messageIndex] != '\0'; messageIndex++)
        {
            char ch = message[messageIndex];
            if (ch == '\r' || ch == '\n')
            {
                break;
            }
            if (islower(ch))
            {
                ch = toupper(ch);
            }
            uint8_t fontIndex;
            fontIndex = (isupper(ch)) ? (uint8_t)ch - (uint8_t)'A' + LETTER_A :
                        (isdigit(ch)) ? (uint8_t)ch - (uint8_t)'0' + DIGIT_0  :
                        (ch == ' ')   ? SPACE   :
                        (ch == '<')   ? LT      :
                        (ch == '>')   ? GT      :
                        (ch == '%')   ? PERCENT :
                        (ch == ':')   ? COLON   : 
                        (ch == '/')   ? SLASH   :
                        (ch == '-')   ? DASH    : 'X';
            
            uint8_t fontPixelsForThisLineByte = G_font[fontIndex][lineIndex];
            uint8_t pixelBitIndex;
            for (pixelBitIndex=0; pixelBitIndex<8; pixelBitIndex++)
            {
                char pix = (fontPixelsForThisLineByte & (1<<(7-pixelBitIndex))) ? (char)219 : ' ';
                if (outstrIndex < outstrLen)
                {
                    outstr[outstrIndex++] = pix;
                }
            }
        }
        if (outstrIndex < outstrLen)
        {
            outstr[outstrIndex++] = '\r';
        }
        if (outstrIndex < outstrLen)
        {
            outstr[outstrIndex++] = '\n';
        }
        
        usbWrite(outstr);
        for (outstrIndex = 0; outstrIndex < outstrLen; outstrIndex++)
        {
            outstr[outstrIndex] = '\0';
        }
        outstrIndex = 0;
    }
}

static void pixelizeScreen()
{
    uint8_t screenIndex;
    for (screenIndex = 0; screenIndex < 12; screenIndex++)
    {
        pixelizeLine(G_screen[screenIndex]);
    }
}

static void updateDisplay()
{
    uint16_t batteryLevel = checkBattery();
    char batteryLevelStr[4];
    sprintf(batteryLevelStr, "%3d", batteryLevel);
    changeText(G_screenBatteryLevel, batteryLevelStr);

    char selfTestStr[5];
    G_selfTestResult = !G_selfTestResult;
    sprintf(selfTestStr, "%s", (G_selfTestResult ? "PASS" : "FAIL"));
    changeText(G_screenPassFail, selfTestStr);
    
    char signalStr[10];
    if (G_triggerCountDown == 0)
    {
        sprintf(signalStr, "OFF    ");
    }
    else if (G_triggerCountDown < 10)
    {
        sprintf(signalStr, "ON (%d) ", G_triggerCountDown);
    }
    else
    {
        sprintf(signalStr, "ON (%d)", G_triggerCountDown);
    }
    changeText(G_screenSignal, signalStr);
    
    char mode0Str[10];
    sprintf(mode0Str, "%s", G_modes0[G_mode[0]]);
    changeText(G_screenMode0, mode0Str);
    
    char mode1Str[10];
    sprintf(mode1Str, "%s", G_modes1[G_mode[1]]);
    changeText(G_screenMode1, mode1Str);
    
    
    if (G_modeSel == 0)
    {
        G_screen[5][0]  = '<';
        G_screen[5][17] = '>';
        G_screen[7][0]  = ' ';
        G_screen[7][17] = ' ';        
    }
    else
    {
        G_screen[5][0]  = ' ';
        G_screen[5][17] = ' ';
        G_screen[7][0]  = '<';
        G_screen[7][17] = '>';
    }
    
    
    char usbStr[10];
    sprintf(usbStr, "%s", usbUp() ? " USB ON "  :
                                    "        ");
    changeText(G_screenUSB, usbStr);

    if (G_watchDisplay || G_getStatus)
    {
        G_getStatus = false;
        if (usbUp()) {
            if (G_showPixels) {
                usbWrite("\r\n");
                pixelizeScreen();
                G_showPixels = false;
            }
            else
            {
                int i;
                char str[13*22] = "\f";
                for (i=0; i<13; i++) {
                    strcat(str, G_screen[i]);
                 }
                usbWrite(str);
            }
            CDCTxService();
        }
    }
}


static void charMode()
{
    char ch = usbGetChar();
    if (ch)
    {
        if (ch == 'a')
        { // left
            G_left_usb = true;
        }
        else if (ch == 's')
        {
            G_sel_usb = true;
        }
        else if (ch == 'd')
        { // right
            G_right_usb = true;
        }
        else if (ch == 'f')
        {
            G_trig_usb = !G_trig_usb;
        }
        else
        {
            G_state = 1;
            G_watchDisplay = false;
            usbWrite(prompt);                   
        }
    }
}

static void lineMode()
{
    bool eoln = usbGetLine(line, USB_LINELEN);
    if (eoln)
    {
        if (strncmp((char*) line, "unlock", 1) == 0)
        {
            char *pw;
            pw = getArg((char*)line);
            uint8_t pwLen = strlen(USB_PASSWORD);
            if (strncmp(pw, USB_PASSWORD, pwLen) == 0)
            {
                usbWrite("\n\rUnlocked\n\r> ");
                G_usbLocked = false;
            }
            return;
        }

        if (G_usbLocked)
        {
            usbWrite("\n\rDevice is locked\n\r> ");
            return;
        }

        if (strncmp((char*) line, "lock", 4) == 0)
        {
            G_usbLocked = true;
            usbWrite("\n\rDevice is locked\n\r> ");
        }
        else if (strncmp((char*) line, "help", 1) == 0)
        {
            usbWrite(help);
        }
        else if (strncmp((char*) line, "status", 1) == 0)
        {
            G_getStatus = true;
        }
        else if (strncmp((char*) line, "pixels", 1) == 0)
        {
            G_showPixels = true;
            G_getStatus = true;
        }
        else if (strncmp((char*) line, "run", 1) == 0)
        {
            G_watchDisplay = true;
            G_state = 2;
            usbWrite(prompt);
        }
        else if (strncmp((char*) line, "load", 1) == 0)
        {
            usbWrite(prompt);
        }
        else if (strncmp((char*) line, "erase", 1) == 0)
        {
            usbWrite(prompt);
        }
        else if (strncmp((char*) line, "clear", 1) == 0)
        {
            usbWrite(prompt);
        }
        else
        {
            sprintf((char*) G_writeBuffer, "\n\rError 1: Invalid command. %s\n\r> ",line);
            usbWrite((char*)G_writeBuffer);
        }
        uint16_t i;
        for (i = 0; i < USB_LINELEN; i++)
        {
            line[i] = '\0';
        }
    }
}

static void handleUSB()
{
    uint8_t success;
    switch (G_state)
    {
    case 0:
        success = usbWrite("Hello from PIC 'u abc' to unlock. 'h' for help.\n\r> ");
        if (success)
        {
            G_state = 1;
        }
        break;
    case 1:
        lineMode();
        break;
    case 2: // display
        charMode();
        break;
    default:
        break;
    }
}

// ===============================================================
// ===============================================================
// ===============================================================

/*
                         Main application
 */
int main(void)
{
    SYSTEM_Initialize(); // Generated by MCC
    LATA = 0x0000;
    while (1)
    {
        spin(100000);
        handleUSB();
        handleTrigger();
        handleButtons();
        updateDisplay();
    }
    return 1;
}


