
/**
 * Copyright 2022 jwrr.com
 * The MIT License
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *      The above copyright notice and this permission notice shall be included
 *      in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
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
#include "mcc_generated_files/interrupt_manager.h"
#include "mcc_generated_files/i2c3.h"

uint8_t usbWriteBufferAppend(char *str);
#define LINELEN 255
char rxLine[LINELEN-10];
char txLine[LINELEN];

// ===============================================================
// ===============================================================
// ===============================================================

#define I2C_ADDR_TC74  0X4D  // A5 Default

uint8_t TC74_state = 0;
uint8_t TC74_temp = 0;
uint8_t TC74_cmd = 0; // read temperature. 1 = standby
I2C3_MESSAGE_STATUS TC74_status;

bool TC74_readTemp(bool start, int8_t *t)
{
    const uint8_t len = 1;
    bool done = false;
    *t = TC74_temp;
    
    switch (TC74_state)
    {
    case 0:
        if (start)
        {
            I2C3_MasterWrite( &TC74_cmd, len, I2C_ADDR_TC74, &TC74_status);
            TC74_state = 1;
        }
        break;
    case 1:
        if (TC74_status != I2C3_MESSAGE_PENDING) {
            TC74_state++;
        }
        break;
    case 2:
        I2C3_MasterRead( &TC74_temp, len, I2C_ADDR_TC74, &TC74_status);
        TC74_state++;
        break;
    case 3:
        if (TC74_status != I2C3_MESSAGE_PENDING) {
            TC74_state++;
        }
        break;
    case 4:
        TC74_state = 0;
        *t = (int8_t)(TC74_temp);
        done = true;
        break;
    default:
        TC74_state = 0;
        break;
    }
    return done;
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
        readBufferPos = 0;
        readBufferLen = getsUSBUSART(G_readBuffer, sizeof(G_readBuffer));
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

void toggleOutputBit(char port, uint8_t pos)
{
    uint16_t massk = 1 << pos;
    switch (port)
    {
    case 'A': LATA ^= massk;
    case 'B': LATB ^= massk;
    case 'C': LATC ^= massk;
    case 'D': LATD ^= massk;
    case 'E': LATE ^= massk;
    case 'F': LATF ^= massk;
    case 'G': LATG ^= massk;
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

int main(void)
{
    SYSTEM_Initialize(); // Generated by MCC
    
    char *prompt = "\n\r> ";

    bool echo = true;
    int8_t temperature = 0;
    bool tempStart  = false;
    bool tempDone   = false;

    sprintf(txLine, "HELLO. Start typing%s", prompt);
    usbWriteBufferAppend(txLine);
    uint32_t cnt = 0;
    while (1)
    {
        cnt = (cnt + 1) % 30000;

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

        
        tempStart = (cnt == 10);
        if (tempStart)
        {
            toggleOutputBit(LED1);
            sprintf(txLine, "Temperature start\n\r");
            usbWriteBufferAppend(txLine);
        }
        tempDone = TC74_readTemp(tempStart, &temperature);
        
        if (tempDone) {
            setOutputBit(LED2, 1);
            sprintf(txLine, "Temperature done = %d\n\r", temperature);
            usbWriteBufferAppend(txLine);
        }
        
        usbWriteBufferTx();
    } // while (1)
    return 1;
}


