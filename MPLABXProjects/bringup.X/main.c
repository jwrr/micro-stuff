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



// CLICKER2 ADC_CHANNEL channel_AN5
#define ADC_CHANNEL channel_AN3
#define LEFT_BUTTON    "RD9"
#define RIGHT_BUTTON   "RD11"
#define CENTER_BUTTON  "RF4"
#define TRIGGER_BUTTON "RD10"

//#ifdef EXP1632
//#define BUTTON1 'D',6
//#define BUTTON2 'D',7
//#define BUTTON3 'A',7
//#define BUTTON4 'D',13
//#endif
//
//#ifdef CLICKER2
//#define LED1 'G',13
//#define LED2 'E',8
//#define BUTTON1 "RA0"
//#define BUTTON2 "RE2"
//
//#define LEFT_BUTTON    "RG0"
//#define RIGHT_BUTTON   "RF2"
//#define CENTER_BUTTON  "RD6"
//#define TRIGGER_BUTTON "RA0"
//
//
////#define LED1 'G',13
////#define LED2 'E',8
////#define BUTTON1 'A',0
////#define BUTTON2 'E',2
////
////#define LEFT_BUTTON    'G',0
////#define RIGHT_BUTTON   'F',2
////#define CENTER_BUTTON  'D',6
////#define TRIGGER_BUTTON 'A',0
//#endif
    
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
#include "mcc_generated_files/spi2.h"

#include "tc74.h"


#define LINELEN 255
char G_rxLine[LINELEN-10];
char G_txLine[LINELEN];
char G_tmpStr[LINELEN+1];
uint8_t G_pixLine[G_txtScreenWidth];
uint8_t G_pixLine2[G_txtScreenWidth];

uint8_t USB_Append(char *str);
void FONT_GetPixLine(uint8_t pixLineIndex, uint8_t *pixLine);


// ===============================================================
// ===============================================================
// ===============================================================

// 18Wx12H
//char G_screen[13][22] = {
//    "BATTERY:      100%\n\r", // 0
//    "SELF TEST:    PASS\n\r", // 1
//    "                  \n\r", // 2
//    "    SIGNAL OFF    \n\r", // 3
//    "                  \n\r", // 4
//    "<      AAAA      >\n\r", // 5
//    "                  \n\r", // 6
//    "<     EEEEEEE    >\n\r", // 7
//    "                  \n\r", // 8
//    "  P/N: PN123-01   \n\r", // 9
//    "  F/W: FW123-01   \n\r", // 10
//    "      USB ON      \n\r", // 11
//    "> "
//};

// 8Wx10H
//char G_screen[13][22] = {
//    "12345678\n\r", // 0
//    "BAT 100%\n\r", // 0
//    "TST PASS\n\r", // 1
//    "        \n\r", // 2
//    " SIG OFF\n\r", // 3
//    "        \n\r", // 4
//    "< AAAA >\n\r", // 5
//    "< EEEE >\n\r", // 6
//    "PN123-01\n\r", // 7
//    "V123-01 \n\r", // 8
//    "USB ON  \n\r", // 9
//    "> "
//};

// 4Wx5H
//char G_screen[13][22] = {
//    "1234\n\r", // 0
//    "100%\n\r", // 0
//    "PASS\n\r", // 1
//    " OFF\n\r", // 2
//    "<AA>\n\r", // 3
//    "<EE>\n\r", // 4
//    "> "
//};


// ===============================================================
// USB

bool USB_isUp()
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


#define USB_WRITE_BUFFER_SIZE 2048
#define USB_WRITE_MAX_TX 200
char USB_writeBuffer[USB_WRITE_BUFFER_SIZE];
char *USB_writeBufferHead = USB_writeBuffer;
char *USB_writeBufferTail = USB_writeBuffer;
char *USB_writeBufferMax = USB_writeBuffer + sizeof(USB_writeBuffer);

uint8_t USB_Append(char *str)
{
    uint16_t len = strlen(str);
    char *newTail = USB_writeBufferTail + len;
    if (newTail < USB_writeBufferMax)
    {
        strcat(USB_writeBuffer, str);
        USB_writeBufferTail = newTail;
    }
    return 0;
}

uint8_t USB_AppendChar(char c)
{
    char str[2] = "";
    uint8_t i = 0;
    str[i++] = c;
    str[i] = '\0';
    uint8_t success = USB_Append(str);
    return success;
}

uint8_t USB_Send()
{
    if (USB_isUp()) {
        CDCTxService();
        if (USBUSARTIsTxTrfReady())
        {
            G_tmpStr[200] = '\0';
            strncpy(G_tmpStr, USB_writeBufferHead, 200);
            uint16_t txLen = strlen(G_tmpStr);
            if (txLen == 0)
            {
                USB_writeBufferHead = USB_writeBuffer;
                USB_writeBufferTail = USB_writeBuffer;
                USB_writeBuffer[0] = '\0';
            }
            else
            {
                USB_writeBufferHead += txLen;
                putsUSBUSART(G_tmpStr);        
            }
        }
    }
    return 1; // success
}

static bool USB_ReadLine(char line[], uint16_t maxLen, bool echo)
{
    static uint8_t readBufferPos = 0;
    static uint8_t readBufferLen = 0;
    static uint8_t linepos = 0;
    uint8_t lineposPrev = linepos;
    uint8_t ch;
    bool    eoln = false;
    
    if (!USB_isUp())
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
        USB_Append(&(line[lineposPrev]));
    }
    
    return eoln;
}

void USB_WriteFontBits(char pixForOneLineOfChar)
{
    // The pixBitIndex loop is only for output to USB
    uint8_t pixBitIndex;
    char pixChar[2];
    pixChar[1] = '\0';
    for (pixBitIndex=0; pixBitIndex<8; pixBitIndex++)
    {
        uint8_t mask = 1 << (7 - pixBitIndex);
        bool bitIsOn = (pixForOneLineOfChar & mask) > 0;
        char asciiSquare = (char)219;
        pixChar[0] = bitIsOn ? asciiSquare : ' ';
        USB_Append(pixChar);
    }
}

void USB_StartGraphicsLine(bool showGraphics)
{
    if (showGraphics)
    {
        USB_Append("\n\r");
    }
}

void USB_AppendGraphicsLine(bool showGraphics, uint8_t pixVal)
{
    if (showGraphics)
    {
        USB_WriteFontBits(pixVal);
    }
}

void USB_EndGraphicsLine(bool showGraphics)
{
    if (showGraphics)
    {
        USB_Append("\n\r");
    }
}


// ===============================================================
// GPIO

void GPIO_Set(char port, uint8_t pos, bool value)
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

void GPIO_Toggle(char port, uint8_t pos)
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

// bool GPIO_Get(char port, uint8_t pos)
bool GPIO_Get(char *pin)
{
    uint8_t pinLen = strlen(pin);
    if (pinLen < 3) return false;
    
    char port = pin[1];
    uint8_t pos = (uint8_t)strtol(&(pin[2]), NULL, 10);
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

// l GPIO_EdgeDetect(char port, uint8_t pos, bool *val, uint8_t whichEdge)
bool GPIO_EdgeDetect(char *pin, bool *val, uint8_t whichEdge)
{
    bool prevVal = *val;
    bool newVal = GPIO_Get(pin);
    *val = newVal;
    bool falling = whichEdge == 0;
    bool rising  = whichEdge == 1;
    bool both    = !falling && !rising;
    bool edgeDetected = (rising  && !prevVal && newVal) ||
                        (falling && prevVal && !newVal) ||
                        (both && (prevVal != newVal));
    return edgeDetected;
}


// ===============================================================
// DAC

#define DAC_CS 'E',4

bool DAC_Write(bool start, uint16_t value)
{
    uint16_t rdata;
    uint16_t i = 0;
//    toggleOutputBit(DAC_CS);
    if (start)
    {
        while (SPI2STATLbits.SPITBF == true);
        GPIO_Set(DAC_CS, 1);
        for (i = 0; i < 10; i++);
        GPIO_Set(DAC_CS, 0);
        for (i = 0; i < 10; i++);
        SPI2BUFL = value;
        while (SPI2STATLbits.SPIRBE == true);
        rdata = SPI2BUFL; // sets SPIRBE
    }
    return false;
}


// ==========================================================
// DISP
// SHARP 144x168 DISPLAY (LS013B7DH05)

#define DISP_CS 'G',8

uint8_t DISP_cmd  = 0x80;
bool    DISP_vcom = true;
uint8_t DISP_pixelWidth = 144;
uint8_t DISP_byteWidth = 18;
uint8_t DISP_timeout = 255;
uint8_t DISP_pixLineIndex = 0;
uint8_t DISP_frameCount = 0;

uint8_t DISP_SendByteSPI(uint8_t val)
{
    uint8_t cnt;
    for (cnt = 0; cnt < DISP_timeout; cnt++)
    {
        if (SPI2STATLbits.SPITBF == false) break;
    }
    if (SPI2STATLbits.SPITBF == true) return 0;
    SPI2BUFL = val;
    
     for (cnt = 0; cnt < DISP_timeout; cnt++)
    {
        if (SPI2STATLbits.SPIRBE == false) break;
    }   
    
    if (SPI2STATLbits.SPIRBE == true) return 0;
    uint8_t rdata = SPI2BUFL; // sets SPIRBE
    return rdata;
}
 
void DISP_DrawPixLine(uint8_t addr, uint8_t pixels[])
{
    uint8_t i = 0;
    DISP_SendByteSPI(addr);
    for (i = 0; i < DISP_byteWidth; i++)
    {
        DISP_SendByteSPI(pixels[i]);
    }
    DISP_SendByteSPI(0x00);
}


uint8_t DISP_ReverseBits(uint8_t val)
{
    uint8_t reverseVal = 0;
    uint8_t i;
    uint8_t mask = 1;
    for (i = 0; i < 8; i++)
    {
        if (val & mask)
        {
            reverseVal += (1 << (7-i));
        }
        mask <<= 1;
    }
    return reverseVal;
}

// SHARP 144x168 DISPLAY (LS013B7DH05)
void DISP_WriteFrame(bool start)
{
    if (start && (DISP_pixLineIndex == 0))
    {
        DISP_pixLineIndex = 1;
        GPIO_Set(DISP_CS, 1);
        DISP_vcom = !DISP_vcom;
        DISP_cmd = DISP_vcom ? 0xc0 : 0x80;
        DISP_SendByteSPI(DISP_cmd);
    }
    
    if (DISP_pixLineIndex > 0 && DISP_pixLineIndex <= 168)
    {
        FONT_GetPixLine(DISP_pixLineIndex-1, G_pixLine);
        uint8_t reverseAddr = DISP_ReverseBits(DISP_pixLineIndex);
        DISP_DrawPixLine(reverseAddr, G_pixLine);
        DISP_pixLineIndex++;
    }
    else if (DISP_pixLineIndex > 168)
    {
        DISP_SendByteSPI(0x00);
        GPIO_Set(DISP_CS, 0);
        DISP_pixLineIndex = 0;
        DISP_frameCount++;
    }
}

void DISP_Append8BitsToPixLine(uint8_t pixVal, uint8_t *pixLine, uint8_t index)
{
    if (index < G_txtScreenWidth)
    {
        pixLine[index] = pixVal;
        USB_AppendGraphicsLine(G_showGraphics, pixVal);
    }
}


// ==========================================================
// FONT

uint8_t FONT_CharToIndex(char ch)
{
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
                (ch == '-')   ? DASH    : (uint8_t)'X';
    return fontIndex;
}

void FONT_GetPixLine(uint8_t pixLineIndex, uint8_t *pixLine)
{
    uint8_t txtIndex = pixLineIndex / G_fontHeight;
    uint8_t fontLineIndex = pixLineIndex % G_fontHeight;
    char *txtLine = G_txtScreen[txtIndex];
    USB_StartGraphicsLine(G_showGraphics);
    uint16_t txtLineIndex = 0;
    for (txtLineIndex = 0; txtLine[txtLineIndex] != '\0'; txtLineIndex++)
    {
        char ch = txtLine[txtLineIndex];
        uint8_t fontIndex = FONT_CharToIndex(ch);
        uint8_t pixForOneLineOfChar = G_font[fontIndex][fontLineIndex];
        uint8_t pixInverted = ~pixForOneLineOfChar;
        uint8_t pixLineByteIndex = txtLineIndex;
        DISP_Append8BitsToPixLine(pixInverted, pixLine, pixLineByteIndex);
    }
    USB_EndGraphicsLine(G_showGraphics);
}


// ==========================================================
// TC74

uint8_t TC74_state = 0;
uint8_t TC74_temp = 0;
uint8_t TC74_cmd = 0; // read temperature. 1 = standby
I2C3_MESSAGE_STATUS TC74_status;

bool TC74_ReadTemp(bool start, int8_t *t)
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

void Spin(uint32_t cnt)
{
    while (cnt--);
}

// ===============================================================
// ===============================================================
// ===============================================================

//uint16_t ADC_Read()
//{
//    int conversion,i=0;
//    ADC1_Initialize();
//
//    ADC1_Enable();
//    ADC1_ChannelSelect(channel_AN5);
//    ADC1_SoftwareTriggerEnable();
//    //Provide Delay
//    for(i=0;i <1000;i++)
//    {
//    }
//    ADC1_SoftwareTriggerDisable();
//    while(!ADC1_IsConversionComplete(channel_AN5));
//    conversion = ADC1_ConversionResultGet(channel_AN5);
//    ADC1_Disable(); 
//    
//    return (uint16_t)conversion;
//}


uint16_t ADC_conversionCnt = 0;
bool ADC_ReadVoltage(bool start, int16_t *v)
{
    bool done = false;
    
    if (start)
    {
        ADC1_Initialize();
        ADC1_Enable();
// clicker2        ADC1_ChannelSelect(channel_AN5);
        ADC1_ChannelSelect(ADC_CHANNEL);
        ADC1_SoftwareTriggerEnable();
        ADC_conversionCnt = 1;
    }
    
    if (ADC_conversionCnt >= 1000)
    {
        ADC1_SoftwareTriggerDisable();
        while(!ADC1_IsConversionComplete(ADC_CHANNEL));
        *v = ADC1_ConversionResultGet(ADC_CHANNEL);
        ADC1_Disable(); 
        ADC_conversionCnt = 0;
        done = true;  
    }
    else if (ADC_conversionCnt > 0)
    {
        ADC_conversionCnt++;
    }
    return done;
}


// ==========================================================================
// ==========================================================================
// ==========================================================================


int main(void)
{
    SYSTEM_Initialize(); // Generated by MCC

    
    bool leftButton = true;
    bool rightButton = true;
    bool centerButton = true;
    bool triggerButton = true;
    uint8_t fallingEdge = 0;
//    uint8_t bothEdges   = 2;
//    uint8_t risingEdge  = 1;


    bool echo = true;
    int8_t temperature = 0;
    bool tempStart  = false;
    bool tempDone   = false;

    int16_t voltage = 0;
    bool adcStart  = false;
    bool adcDone   = false;
            
//    bool dacStart  = false;
//    uint16_t dacValue = 0;
    
    bool displayStart = false;
    
    sprintf(G_tmpStr, "HELLO. Start typing222\n\r> ");
    USB_Append(G_tmpStr);
    uint32_t cnt = 0;
    while (1)
    {
        cnt = (cnt + 1) % 100000;
        
        if (GPIO_EdgeDetect(LEFT_BUTTON, &leftButton, fallingEdge))
        {
            USB_Append("Left\n\r");
            adcStart = true;
        }

        if (GPIO_EdgeDetect(RIGHT_BUTTON, &rightButton, fallingEdge))
        {
            USB_Append("Right\n\r");
        }

        if (GPIO_EdgeDetect(CENTER_BUTTON, &centerButton, fallingEdge))
        {
            USB_Append("Center\n\r");
            tempStart = true;
        }

        if (GPIO_EdgeDetect(TRIGGER_BUTTON, &triggerButton, fallingEdge))
        {
            USB_Append("Trigger\n\r");
        }

        bool eoln = USB_ReadLine(G_rxLine, (uint16_t)sizeof(G_rxLine), echo);
        if (eoln) {
            // Process command line
            sprintf(G_tmpStr, "\n\rcmd=%s\n\r> ", G_rxLine);
            USB_Append(G_tmpStr);
            G_rxLine[0] = '\0';
        }

        if (tempStart)
//        {
//            GPIO_Toggle(LED1);
//        }
        tempDone = TC74_ReadTemp(tempStart, &temperature);
        tempStart = false;
        if (tempDone) {
//            GPIO_Set(LED2, 1);
            sprintf(G_tmpStr, "Temperature = %d\n\r", temperature);
            USB_Append(G_tmpStr);
        }

        adcDone = ADC_ReadVoltage(adcStart, &voltage);
        if (adcDone)
        {
            sprintf(G_tmpStr, "Voltage (max=1023) = %d\n\r", voltage);
            USB_Append(G_tmpStr);
        }

        displayStart = (cnt == 10);
//        GPIO_Set(LED2, DISP_vcom);
        DISP_WriteFrame(displayStart);        

//        dacStart = (cnt == 10);
//        if (dacStart)
//        {            
//            dacValue += 512;
//            dacValue &= 0x0FFF;
//        }
//        DAC121S101_writeDAC(dacStart, dacValue); 
        
//        displayStart = (cnt == 10);
//        DISP_WriteFrame(displayStart);


        
        USB_Send();
    } // while (1)
    return 1;
}


