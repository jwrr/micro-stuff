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


#define CLICKER2


#ifdef EXP1632
#define BUT1 'D', 6
#define BUT2 'D', 7
#define BUT3 'A', 7
#define BUT4 'D', 13
#endif

#ifdef CLICKER2
#define LED1 'G', 13
#define LED2 'E',  8
#define BUT1 'A',  0
#define BUT2 'E',  2
#endif
    
#define isPressed(PB) (!getInputBit(PB))

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

bool usbWrite200(char *str)
{
    char tmpStr[201];
    tmpStr[200] =  '\0';
    if (!usbUp())
    {
        return false; // fail
    }

    // while (!USBUSARTIsTxTrfReady()) CDCTxService();
    strncpy(tmpStr, str, 200);
    putsUSBUSART(tmpStr);

    // while (!USBUSARTIsTxTrfReady()) CDCTxService();

    return true; // success
} // usbWrite256




#define USB_WRITE_BUFFER_SIZE 2048
#define USB_WRITE_MAX_TX 200
char usbWriteBuffer[USB_WRITE_BUFFER_SIZE];
char *usbWriteBufferHead = usbWriteBuffer;
char *usbWriteBufferTail = usbWriteBuffer;
char *usbWriteBufferMax = usbWriteBuffer + sizeof(usbWriteBuffer);
char txStr[USB_WRITE_MAX_TX+1];

uint8_t usbWriteBufferAppend(char *str)
{
    uint16_t len = strlen(str);
    char *newTail = usbWriteBufferTail + len;
    if (newTail < usbWriteBufferMax)
    {
        strcat(usbWriteBuffer, str);
        usbWriteBufferTail = newTail;
    }
    return 0;
}

uint8_t usbWriteBufferTx()
{
    if (usbUp()) {
        CDCTxService();
        if (USBUSARTIsTxTrfReady())
        {
            txStr[200] = '\0';
            strncpy(txStr, usbWriteBufferHead, 200);
            uint16_t txLen = strlen(txStr);
            if (txLen == 0)
            {
                usbWriteBufferHead = usbWriteBuffer;
                usbWriteBufferTail = usbWriteBuffer;
                usbWriteBuffer[0] = '\0';
            }
            else
            {
                usbWriteBufferHead += txLen;
                putsUSBUSART(txStr);        
            }
        }
    }
    return 1; // success
}

uint8_t usbWrite(char *str)
{
    static char usbWriteBuffer[2048] = "";
    static char *bufferHead = usbWriteBuffer;
    static char *bufferTail = usbWriteBuffer;

    if (!usbUp())
    {
        return 0; // fail
    }

    uint16_t len = strlen(str);
    
    if (len == 0)
    {
        return 0;
    }
    
    
    if (bufferTail + len > &(usbWriteBuffer[2048]))
    { // overflow
        return 0;
    }
    
    strcat(usbWriteBuffer, str);
    bufferTail += len;
    
    if (!USBUSARTIsTxTrfReady())
    {
        return 0;
    }
    
    char txStr[201];
    txStr[200] = '\0';
    strncpy(txStr, bufferHead, 200);
    uint16_t txLen = strlen(txStr);
    bufferHead += txLen;
    if (bufferHead == bufferTail) {
        bufferHead = usbWriteBuffer;
        bufferTail = usbWriteBuffer;
    }
    
    putsUSBUSART(txStr);  

    return 1; // success
} // usbWrite

static bool usbGetLine(char line[], uint16_t maxLen, bool echo)
{
    static uint8_t readBufferPos = 0;
    static uint8_t readBufferLen = 0;
    static uint8_t linepos = 0;
    uint8_t lineposPrev = linepos;
    uint8_t ch;
    bool    eoln = false;
    
    if (!usbUp())
    {
        return false;
    }
    
    if (readBufferPos == readBufferLen) {
        readBufferLen = getsUSBUSART(G_readBuffer, sizeof(G_readBuffer));
        readBufferPos = 0;
        if (readBufferLen == 0)
        {
            return false;
        }
    }
    
    while (readBufferPos < readBufferLen) {
        ch = G_readBuffer[readBufferPos++];
        if (ch == 0x0D)
        {
            linepos = 0;
            eoln = true;
            break;
        }

        if (linepos >= maxLen - 1) // overflow error
        {
            line[maxLen - 1] = '\0';
            linepos = 0;
            eoln = true;
            break;
        }
        else if (ch == '\b')
        {
            if (linepos > 0) linepos--;
            line[linepos] = '\0';
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
    }
    
    if (echo)
    {
        usbWriteBufferAppend(&(line[lineposPrev]));
    }
    
    return eoln;
}


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
}


void spin(uint32_t cnt)
{
    while (cnt--);
}

// ===============================================================
// ===============================================================
// ===============================================================

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

void setOutputBit(char port, uint8_t pos, bool value)
{
    uint16_t mask1 = 1 << pos;
    uint16_t mask0 = ~mask1;
    switch (port)
    {
    case 'A': LATA = value ? (LATA | mask1) : (LATA & mask0); break;
    case 'B': LATB = value ? (LATB | mask1) : (LATB & mask0); break;
    case 'C': LATC = value ? (LATC | mask1) : (LATC & mask0); break;
    case 'D': LATD = value ? (LATD | mask1) : (LATD & mask0); break;
    case 'E': LATE = value ? (LATE | mask1) : (LATE & mask0); break;
    case 'F': LATF = value ? (LATF | mask1) : (LATF & mask0); break;
    case 'G': LATG = value ? (LATG | mask1) : (LATG & mask0); break;
    default: break;
    }
}

bool getInputBit(char port, uint8_t pos)
{
    uint16_t mask0 = 1 << pos;
    switch (port)
    {
    case 'A': return (bool)(PORTA & mask0);
    case 'B': return (bool)(PORTB & mask0);
    case 'C': return (bool)(PORTC & mask0);
    case 'D': return (bool)(PORTD & mask0);
    case 'E': return (bool)(PORTE & mask0);
    case 'F': return (bool)(PORTF & mask0);
    case 'G': return (bool)(PORTG & mask0);
    default: return false;
    }
    return false;
}

// ===============================================================
// ===============================================================
// ===============================================================

#define LINELEN 255

int main(void)
{
    SYSTEM_Initialize(); // Generated by MCC
    
    char *prompt = "\n\r> ";
    char rxLine[LINELEN-10];
    char txLine[LINELEN];
    bool echo = true;

    sprintf(txLine, "HELLO. Start typing%s", prompt);
    usbWriteBufferAppend(txLine);    
    while (1)
    {
        setOutputBit(LED1, isPressed(BUT1));
        setOutputBit(LED2, isPressed(BUT2));
        
//        spin(100000);
        if (isPressed(BUT1))
            usbWriteBufferAppend("1");
        else if (isPressed(BUT2))
            usbWriteBufferAppend("2");
#ifdef EXP1632
        else if (isPressed(BUT3))
            usbWriteBufferAppend("3");
        else if (isPressed(BUT4))
            usbWriteBufferAppend("4");
#endif
        bool eoln = usbGetLine(rxLine, (uint16_t)sizeof(rxLine), echo);
        if (eoln) {
            // Process command line
            sprintf(txLine, "\n\rcmd=%s%s", rxLine, prompt);
            usbWriteBufferAppend(txLine);
            rxLine[0] = '\0';
        }

        usbWriteBufferTx();
    } // while (1)
    return 1;
}


