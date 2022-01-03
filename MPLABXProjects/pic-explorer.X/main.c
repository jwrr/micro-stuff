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
#include "mcc_generated_files/adc1.h"
#include "main.h"


// ===============================================================
// ===============================================================
// ===============================================================


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

uint16_t readADC1()
{
    int conversion,i=0;
    ADC1_Initialize();

    ADC1_Enable();
    ADC1_ChannelSelect(channel_AN5);
    ADC1_SoftwareTriggerEnable();
    //Provide Delay
    for(i=0;i <1000;i++)
    {
    }
    ADC1_SoftwareTriggerDisable();
    while(!ADC1_IsConversionComplete(channel_AN5));
    conversion = ADC1_ConversionResultGet(channel_AN5);
    ADC1_Disable(); 
    
    return (uint16_t)conversion;
}

static uint16_t checkBattery()
{
    double    maxVoltage = 18.0;
    double    minVoltage = 12.0;
    uint16_t  maxADC     = 1023;
    uint16_t  minADC     = (uint16_t)(maxADC * (minVoltage / maxVoltage));
    uint16_t  rangeADC   = maxADC - minADC;
    uint16_t  actualADC;
    uint16_t  percent;

    actualADC = readADC1();
    if (actualADC < minADC)
    {
        percent = 0;
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
    G_selfTestResult = true; // !G_selfTestResult;
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

    int ii;
    bool screenChange = false;
    for (ii=0; ii<13; ii++) {
        if (strcmp(G_screenPrev[ii], G_screen[ii]) != 0)
        {
            screenChange = true;
            break;
        }
    }
    
    if (G_run_usb && !screenChange)
    {
        return;
    }
    
    for (ii=0; ii<13; ii++) {
        strcpy(G_screenPrev[ii], G_screen[ii]);
    }
    
    if (G_run_usb || G_getStatus)
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
            G_run_usb = false;
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
            G_run_usb = true;
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
        success = usbWrite(WELCOME_PROMPT);
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


