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

#define BATT_CHANNEL channel_AN3

#ifdef EXP1632
#define BUTTON1 'D',6
#define BUTTON2 'D',7
#define BUTTON3 'A',7
#define BUTTON4 'D',13
#endif

#ifdef CLICKER2
#define LED1 'G',13
#define LED2 'E',8
#define BUTTON1 "RA0"
#define BUTTON2 "RE2"

#define LEFT_BUTTON    "RG0"
#define RIGHT_BUTTON   "RF2"
#define CENTER_BUTTON  "RD6"
#define TRIGGER_BUTTON "RA0"


//#define LED1 'G',13
//#define LED2 'E',8
//#define BUTTON1 'A',0
//#define BUTTON2 'E',2
//
//#define LEFT_BUTTON    'G',0
//#define RIGHT_BUTTON   'F',2
//#define CENTER_BUTTON  'D',6
//#define TRIGGER_BUTTON 'A',0
#endif
    
#define GPIO_isPressed(BUTTON) (!GPIO_get(BUTTON))

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
#include "mcc_generated_files/tmr3.h"
#include "tc74.h"
#include "flash_wrapper.h"

#define LINELEN 255
char G_rxLine[LINELEN-10];
char G_txLine[LINELEN];
uint8_t DISP_pixLine[G_txtCharPerLine];

uint8_t USB_print(char *str);
void FONT_getPixLine(uint8_t pixLineIndex, uint8_t *pixLine);


// ===============================================================
// ===============================================================
// ===============================================================

//===============================================================
// MODE

uint8_t getModeIndex();
uint8_t getModeSize(uint8_t mode);
const char *getModeName(uint8_t m);
void setMode(uint8_t mode, uint8_t val);

uint8_t getModeIndex()
{
    uint8_t tableIndex = G_mode[0] * G_modeSize[1] + G_mode[1];
    return tableIndex;
}

uint8_t getModeSize(uint8_t mode)
{
    if (mode >= 2) return 0;
    return G_modeSize[mode];
}

const char *getModeName(uint8_t m)
{
    if (m >= 2) return NULL;
    if (m == 0) return G_modeNames0[G_mode[m]];
    if (m == 1) return G_modeNames1[G_mode[m]];
    return NULL;
}

void setMode(uint8_t mode, uint8_t val)
{
    if (mode >= 2) return;
    G_mode[mode] = val;
}


// ===============================================================
// USB

bool G_enablePrompt = true;
bool G_echoCommand = false;
bool G_echoChar = false;

#include "usbprint.h"

static char USB_tmpStr[USB_LINELEN+1];
char USB_writeBuffer[USB_WRITE_BUFFER_SIZE];
char *USB_writeBufferHead = USB_writeBuffer;
char *USB_writeBufferTail = USB_writeBuffer;
char *USB_writeBufferMax = USB_writeBuffer + sizeof(USB_writeBuffer);

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

uint8_t USB_print(char *str)
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

uint8_t USB_printChar(char c)
{
    char str[2] = "";
    uint8_t i = 0;
    str[i++] = c;
    str[i] = '\0';
    uint8_t success = USB_print(str);
    return success;
}

void USB_printFontBits(char pixForOneLineOfChar)
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
        USB_print(pixChar);
    }
}

void USB_printGraphicsLineHeader(bool showGraphics)
{
    if (showGraphics)
    {
        USB_printLine("");
    }
}

void USB_printGraphicsLinePixels(bool showGraphics, uint8_t pixVal)
{
    if (showGraphics)
    {
        USB_printFontBits(pixVal);
    }
}

void USB_printGraphicsLineTrailer(bool showGraphics)
{
    if (showGraphics)
    {
        USB_printLine("");
    }
}

uint8_t USB_flushPrintBuffer()
{
    if (USB_isUp()) {
        CDCTxService();
        if (USBUSARTIsTxTrfReady())
        {
            USB_tmpStr[200] = '\0';
            strncpy(USB_tmpStr, USB_writeBufferHead, 200);
            uint16_t txLen = strlen(USB_tmpStr);
            if (txLen == 0)
            {
                USB_writeBufferHead = USB_writeBuffer;
                USB_writeBufferTail = USB_writeBuffer;
                USB_writeBuffer[0] = '\0';
            }
            else
            {
                USB_writeBufferHead += txLen;
                putsUSBUSART(USB_tmpStr);        
            }
        }
    }
    return 1; // success
}

static bool USB_readLine(char line[], uint16_t maxLen, bool echo)
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
        USB_print(&(line[lineposPrev]));
    }
    
    return eoln;
}


void USB_printWave()
{
    uint8_t tableIndex = getModeIndex();
    USB_printfLine("Waveform[%d] = ", tableIndex);
    uint16_t i;
    bool done = false;
    for (i=0; i<257; i+=2)
    {
        int32_t value32 = FLASH_readFromPage(tableIndex, i);
        // flash is initially 0
        // after page is written and erased it's 0x00FFFFFF
        // table writer sets bit 16 "valid" bit, so all values should  be in
        // the range of 0x10000 to 0x1ffff
        bool outOfRange = (value32 < 0x10000) || (value32 > 0x1ffff);
        int32_t value16 = value32 & 0xffff; // trim valid bit
        bool isNegative = (value16 > 0x7fff);
        done = outOfRange || isNegative;
        if (done) break;
        USB_printf("%d, ", (int)value16);
//        int32_t upper = value32 >> 16;
//        int32_t lower = value32 & 0xFFFF;
//        USB_printfLine("%04x%04x %d %d %d %d, ", (int)upper, (int)lower, (int)value16,  outOfRange, isNegative, done);
    }
    USB_printLine("-1");
}

// ===============================================================
// GPIO

void GPIO_set(char port, uint8_t pos, bool value)
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

void GPIO_toggle(char port, uint8_t pos)
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
bool GPIO_get(char *pin)
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
bool GPIO_edgeDetect(char *pin, bool *val, uint8_t whichEdge)
{
    bool prevVal = *val;
    bool newVal = GPIO_get(pin);
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

bool DAC_write(bool start, uint16_t value)
{
    uint16_t rdata;
    uint16_t i = 0;
//    toggleOutputBit(DAC_CS);
    if (start)
    {
        while (SPI2STATLbits.SPITBF == true);
        GPIO_set(DAC_CS, 1);
        for (i = 0; i < 10; i++);
        GPIO_set(DAC_CS, 0);
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
uint8_t DISP_ScreenWidthInPixels = 144;
uint8_t DISP_screenWidthInBytes = 18;
uint8_t DISP_screenWidthInChar  = 18;
uint8_t DISP_timeout = 255;
uint8_t DISP_pixLineIndex = 0;
uint8_t FONT_pixLineIndex = 0;
uint8_t DISP_frameCount = 0;
bool    DISP_busy = false;

uint8_t DISP_sendByteSPI(uint8_t val)
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
 
void DISP_drawPixLine(uint8_t addr, uint8_t pixels[])
{
    uint8_t i = 0;
    DISP_sendByteSPI(addr);
    for (i = 0; i < DISP_screenWidthInBytes; i++)
    {
        DISP_sendByteSPI(pixels[i]);
    }
    DISP_sendByteSPI(0x00);
}


uint8_t DISP_reverseBits(uint8_t val)
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
void DISP_writeFrame(bool start)
{
    if (start && (DISP_pixLineIndex == 0))
    {
        DISP_busy = true;
        DISP_pixLineIndex = 1;
        FONT_pixLineIndex = 0;
        GPIO_set(DISP_CS, 1);
        DISP_vcom = !DISP_vcom;
        DISP_cmd = DISP_vcom ? 0xc0 : 0x80;
        DISP_sendByteSPI(DISP_cmd);
    }
    
    if (DISP_pixLineIndex > 0 && DISP_pixLineIndex <= 168)
    {
//            FONT_isAllSpaces
        FONT_getPixLine(FONT_pixLineIndex, DISP_pixLine);
        if (FONT_isStartingBlankLine(FONT_pixLineIndex))
        {
            FONT_pixLineIndex += 11; // Reduce height of blank lines
        }
        FONT_pixLineIndex++;
        uint8_t reverseAddr = DISP_reverseBits(DISP_pixLineIndex);
        DISP_drawPixLine(reverseAddr, DISP_pixLine);
        DISP_pixLineIndex++;
    }
    else if (DISP_pixLineIndex > 168)
    {
        DISP_busy = false;
        DISP_sendByteSPI(0x00);
        GPIO_set(DISP_CS, 0);
        DISP_pixLineIndex = 0;
        FONT_pixLineIndex = 0;
        DISP_frameCount++;
    }
}

void DISP_append8BitsToPixLine(uint8_t pixVal, uint8_t *pixLine, uint8_t index)
{
    if (index < G_txtCharPerLine)
    {
        pixLine[index] = pixVal;
        USB_printGraphicsLinePixels(G_showGraphics, pixVal);
    }
}


// ==========================================================
// FONT

uint8_t FONT_charToIndex(char ch)
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

uint8_t FONT_getTxtLineNumber(uint8_t pixLineNumber)
{
    return pixLineNumber / G_charHeight;
}

void FONT_getPixLine(uint8_t pixLineNumber, uint8_t *pixLine)
{
    uint8_t txtLineNumber = FONT_getTxtLineNumber(pixLineNumber);
    uint8_t fontLineIndex = (pixLineNumber % G_charHeight) + 1;
    bool isSpaceBetweenLines = (fontLineIndex >= G_fontHeight);
    char *txtLine = G_txtScreen[txtLineNumber];
    USB_printGraphicsLineHeader(G_showGraphics);
    uint16_t txtLineIndex = 0;
    for (txtLineIndex = 0; txtLine[txtLineIndex] != '\0'; txtLineIndex++)
    {
        char ch = txtLine[txtLineIndex];
        uint8_t fontIndex = FONT_charToIndex(ch);
        uint8_t pixForOneLineOfChar = 0;
        if (!isSpaceBetweenLines)
        {
            pixForOneLineOfChar = G_font[fontIndex][fontLineIndex];
        }
        if (FONT_BlackOnWhite) {
            pixForOneLineOfChar = ~pixForOneLineOfChar;
        }
        uint8_t pixLineByteIndex = txtLineIndex;
        DISP_append8BitsToPixLine(pixForOneLineOfChar, pixLine, pixLineByteIndex);
    }
    USB_printGraphicsLineTrailer(G_showGraphics);
}

bool FONT_isTxtLineAllSpaces(uint8_t pixLineNumber)
{
    uint8_t txtLineNumber = FONT_getTxtLineNumber(pixLineNumber);
    char *txtLine = G_txtScreen[txtLineNumber];
    uint8_t ii;
    for (ii=0; ii < G_txtCharPerLine; ii++)
    {
        if (!isspace(txtLine[ii])) return false;
    }
    return true;
}

bool FONT_isStartingBlankLine(uint8_t pixLineNumber)
{
    bool isStartingBlankLine = false;
    if (FONT_isTxtLineAllSpaces(pixLineNumber))
    {
        uint8_t fontLineIndex = (pixLineNumber % G_charHeight) + 1;
        if (fontLineIndex == 1)
        {
            isStartingBlankLine = true;
        }
    }
    return isStartingBlankLine;
}

// ==========================================================
// TC74

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

void spin(uint32_t cnt)
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
bool ADC_readVoltage(bool start, int16_t *v)
{
    bool done = false;
    
    if (start)
    {
        ADC1_Initialize();
        ADC1_Enable();
        ADC1_ChannelSelect(BATT_CHANNEL);
        ADC1_SoftwareTriggerEnable();
        ADC_conversionCnt = 1;
    }
    
    if (ADC_conversionCnt >= 1000)
    {
        ADC1_SoftwareTriggerDisable();
        while(!ADC1_IsConversionComplete(BATT_CHANNEL));
        *v = ADC1_ConversionResultGet(BATT_CHANNEL);
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


char *center(uint8_t width, char centered[], const char uncentered[])
{
    uint8_t uncenteredLen = strlen(uncentered);
    if (uncenteredLen > width)
    {
        strncpy(centered, uncentered, width);
        centered[width] = '\0';
        return centered;
    }
    
    uint8_t lenDelta = width - uncenteredLen;
    uint8_t startPos = lenDelta / 2;
    uint8_t i;
    for (i=0; i<width; i++)
    {
        centered[i] = ' ';
    }
 
    for (i=0; i<uncenteredLen; i++)
    {
        centered[i+startPos] = uncentered[i];
    }
    // centered[width] = '\0';
    return centered;
}   

void handleCenterButton()
{
    G_modeSel = (G_modeSel + 1) % 2;
    if (G_modeSel == 0) {
        G_txtScreen[G_screenLineMode0][0] = '<';
        G_txtScreen[G_screenLineMode1][0] = ' ';
        G_txtScreen[G_screenLineMode0][G_txtCharPerLine - 1] = '>';
        G_txtScreen[G_screenLineMode1][G_txtCharPerLine - 1] = ' ';        
    }
    else
    {
        G_txtScreen[G_screenLineMode0][0] = ' ';
        G_txtScreen[G_screenLineMode1][0] = '<';
        G_txtScreen[G_screenLineMode0][G_txtCharPerLine - 1] = ' ';
        G_txtScreen[G_screenLineMode1][G_txtCharPerLine - 1] = '>';          
    }
}

void updateMode(uint8_t mode)
{
    uint8_t wid = DISP_screenWidthInChar-2;
    center(wid, &(G_txtScreen[G_screenLineMode0][1]), G_modeNames0[G_mode[0]]);
    center(wid, &(G_txtScreen[G_screenLineMode1][1]), G_modeNames1[G_mode[1]]);
    if (G_modeSel == 0) {
        G_txtScreen[G_screenLineMode0][0] = '<';
        G_txtScreen[G_screenLineMode1][0] = ' ';
        G_txtScreen[G_screenLineMode0][G_txtCharPerLine - 1] = '>';
        G_txtScreen[G_screenLineMode1][G_txtCharPerLine - 1] = ' ';        
    }
    else
    {
        G_txtScreen[G_screenLineMode0][0] = ' ';
        G_txtScreen[G_screenLineMode1][0] = '<';
        G_txtScreen[G_screenLineMode0][G_txtCharPerLine - 1] = ' ';
        G_txtScreen[G_screenLineMode1][G_txtCharPerLine - 1] = '>';          
    }
}

void handleLeftButton()
{
    if (G_mode[G_modeSel] == 0)
    {
        G_mode[G_modeSel] = G_modeSize[G_modeSel];
    }
    G_mode[G_modeSel]--;
    updateMode(G_mode[G_modeSel]);
}

void handleRightButton()
{
    G_mode[G_modeSel]++;
    if (G_mode[G_modeSel] >= G_modeSize[G_modeSel])
    {
        G_mode[G_modeSel] = 0;
    }
    updateMode(G_mode[G_modeSel]);
}

bool G_triggerPressedPrev   = false;
bool G_triggerFiring        = false;
bool G_displayStart         = true;
bool USB_triggerPressed     = false;
bool USB_triggerPressedPrev = false;

//G_screenLineTrig
//    uint8_t wid = DISP_screenWidthInChar-2;
//    if (G_modeSel == 0) {
//        center(&(G_txtScreen[G_screenLineMode0][1]), G_modeNames0[mode], wid);

void handleTrigger(void)
{
    bool triggerVal      = GPIO_get(TRIGGER_BUTTON);
    bool triggerPressed  = !triggerVal;
    bool triggerEdge     = !G_triggerPressedPrev && triggerPressed;
    G_triggerPressedPrev = triggerPressed;
    bool USB_triggerEdge = !USB_triggerPressedPrev && USB_triggerPressed;
    USB_triggerPressedPrev = USB_triggerPressed;

    if (G_triggerCountDown == 0){
        if (triggerEdge || USB_triggerEdge)
        {
            G_triggerFiring = false;
            G_triggerCountDown = G_triggerCountDownMax + 1;
            center(DISP_screenWidthInChar, G_txtScreen[G_screenLineSignal], ">>> SIGNAL ON <<<");
            G_displayStart = true;
//            USB_PrintLinePrompt("Trigger pressed");
        }
        else if (triggerPressed || USB_triggerPressed)
        {
            center(DISP_screenWidthInChar, G_txtScreen[G_screenLineSignal], "RELEASE / RE-PRESS");
            G_displayStart = true;
//            USB_PrintLinePrompt("Trigger over-ride. Release, pause and press again");
        }
        else
        {
            center(DISP_screenWidthInChar, G_txtScreen[G_screenLineSignal], "SIGNAL OFF");
            G_displayStart = true;
        }
    }
    else if ((triggerPressed || USB_triggerPressed) && (G_triggerCountDown > 1))
    {
        G_triggerCountDown--;
        G_triggerFiring = true;
        center(DISP_screenWidthInChar, G_txtScreen[G_screenLineSignal], ">>> SIGNAL ON <<<");
        G_displayStart = false;
//        USB_PrintfLinePrompt("Signal On (%d)", G_triggerCountDown);
    }
    else
    {
        G_triggerFiring = false;
        G_triggerCountDown = 0;
        center(DISP_screenWidthInChar, G_txtScreen[G_screenLineSignal], "SIGNAL OFF");
        G_displayStart = true;
//        USB_PrintLinePrompt("Signal off");
    }
}



void DAC_SPI2_initialize(void)
{
    // AUDEN disabled; FRMEN disabled; AUDMOD I2S; FRMSYPW One clock wide; AUDMONO stereo; FRMCNT 0; MSSEN disabled; FRMPOL disabled; IGNROV disabled; SPISGNEXT not sign-extended; FRMSYNC disabled; URDTEN disabled; IGNTUR disabled; 
    SPI2CON1H = 0x00;
    // WLENGTH 0; 
    SPI2CON2L = 0x00;
    // SPIROV disabled; FRMERR disabled; 
    SPI2STATL = 0x00;
    // SPI2BRGL 0; 
    SPI2BRGL = 0x07; // Baud Rate Generator. MCC set this to 0x00; Changed it to 7 to match display
    // SPITBFEN disabled; SPITUREN disabled; FRMERREN disabled; SRMTEN disabled; SPIRBEN disabled; BUSYEN disabled; SPITBEN disabled; SPIROVEN disabled; SPIRBFEN disabled; 
    SPI2IMSKL = 0x00;
    // RXMSK 0; TXWIEN disabled; TXMSK 0; RXWIEN disabled; 
    SPI2IMSKH = 0x00;
    // SPI2URDTL 0; 
    SPI2URDTL = 0x00;
    // SPI2URDTH 0; 
    SPI2URDTH = 0x00;
    // SPIEN enabled; DISSDO disabled; MCLKEN FOSC/2; CKP Idle:Low, Active:High; SSEN disabled; MSTEN Master; MODE16 enabled; SMP Middle; DISSCK disabled; SPIFE Frame Sync pulse precedes; CKE Idle to Active; MODE32 disabled; SPISIDL disabled; ENHBUF enabled; DISSDI disabled; 
    SPI2CON1L = 0x8421;  
    
//    // SPI2BRGL 7; 
//    SPI2BRGL = 0x07;
//    // SPIEN enabled; DISSDO disabled; MCLKEN FOSC/2; CKP Idle:Low, Active:High; SSEN disabled; MSTEN Master; MODE16 disabled; SMP Middle; DISSCK disabled; SPIFE Frame Sync pulse precedes; CKE Active to Idle; MODE32 disabled; SPISIDL disabled; ENHBUF enabled; DISSDI disabled; 
//    SPI2CON1L = 0x8121;
}

// DAC121S101
void DAC_writeSPI(bool start, uint16_t value)
{
    uint16_t rdata;
    uint16_t i = 0;
    if (start)
    {
        while (SPI2STATLbits.SPITBF == true);
        DAC_SPI2_initialize(); // Mode 0, 16-Bit

        GPIO_set(DAC_CS, 1);
        for (i = 0; i < 10; i++);
        GPIO_set(DAC_CS, 0);
        for (i = 0; i < 10; i++);

        SPI2BUFL = value;
        uint16_t cnt = 0;
        while (SPI2STATLbits.SPIRBE == true) cnt++;
        rdata = SPI2BUFL;     // sets SPIRBE
        SPI2_Initialize(); // Mode 1, 8-bit
    }
}

int16_t *p_waveformSample;
int16_t *p_waveformSampleBase;
int16_t G_sample = 0; // *p_waveformSample;
int16_t G_samplePrev = 0; // FIXME use this in polling loop for interpolation

bool timeMonitor = false;
uint16_t cnt500usec = 0;
uint16_t cntSeconds = 0;

void TMR3_callBack(void)
{
    if (G_triggerFiring)
    {
        G_samplePrev = G_sample;
        G_sample = *p_waveformSample++;
        if (G_sample == -1)
        {
            p_waveformSample = p_waveformSampleBase;
            G_sample = *p_waveformSample++;
        }
        DAC_writeSPI(true, (uint16_t)G_sample);
    }
    cnt500usec++;
    
    if (cnt500usec >= 2000)
    {
        uint8_t tableIndex = getModeIndex();
        p_waveformSampleBase = G_waveformTable[tableIndex];
        p_waveformSample = p_waveformSampleBase;
        handleTrigger();
        cnt500usec = 0;
        cntSeconds++;
        uint16_t tm3TimerCount = TMR3_Counter16BitGet();
        
        if (timeMonitor)
        {
            USB_printfLinePrompt("TMR3 callback = %d seconds %d", cntSeconds, tm3TimerCount);
        }
    }
}

uint16_t getTableLen16(int16_t *table)
{
    uint16_t maxLen = 256;
    uint16_t len = 0;
    for (; len < maxLen; len++)
    {
        if (table[len] == -1)
        {
            return len+1;
        }
    }
    return maxLen;
}

bool isUint(char *s)
{
    uint16_t i = 0;
    if (s[0] == '\0') return false;
    for (i=0; s[i] != '\0'; i++)
    {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

    
int stringInArray(char *str, const char *strArray[], int len)
{
    int i = 0;
    for (; i < len; i++)
    {
        if (strcmp(str, strArray[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

char MAIN_cmd[USB_LINELEN] = "";

int main(void)
{
    SYSTEM_Initialize(); // Generated by MCC
    
    bool leftButton = true;
    bool rightButton = true;
    bool centerButton = true;
    uint8_t fallingEdge = 0;
//    uint8_t bothEdges   = 2;
//    uint8_t risingEdge  = 1;

    int8_t temperature = 0;
    int8_t temperaturePrev = 25;
    bool tempMonitor = false;
    bool tempStart  = false;
    bool tempDone   = false;

    int16_t battVoltage = 0;
    int16_t battVoltagePrev = 10;
    bool battMonitor = false;
    bool adcStart  = false;
    bool adcDone   = false;
    
    bool displayInhibit = false;
    uint8_t tableIndex = 0;
    uint8_t sampleIndex = 0;
    
//    USB_PrintLine("HELLO. Start typing");
//    USB_PrintPrompt();
    uint32_t cnt = 0;

    bool loadInProgress = false;
    
    // FLASH_test();
 
    TMR3_SetInterruptHandler(&TMR3_callBack);
    TMR3_Start();
    while (1)
    {
        cnt = (cnt + 1) % 3000;
        // called from interrupt HandleTrigger();
        
        if (GPIO_edgeDetect(LEFT_BUTTON, &leftButton, fallingEdge))
        {
            USB_printLinePrompt("Left");
            handleLeftButton();
            G_displayStart = true;
            adcStart = true; // FIXME for debug only
        }

        if (GPIO_edgeDetect(RIGHT_BUTTON, &rightButton, fallingEdge))
        {
            USB_printLinePrompt("Right");
            handleRightButton();
            G_displayStart = true;
        }

        if (GPIO_edgeDetect(CENTER_BUTTON, &centerButton, fallingEdge))
        {
            USB_printLinePrompt("Center");
            handleCenterButton();
            G_displayStart = true;
        }

        bool eoln = USB_readLine(G_rxLine, (uint16_t)sizeof(G_rxLine), G_echoChar);
        if (eoln) {
            G_displayStart = true;
            if (G_rxLine[0] != '\0')
            {
                strncpy(MAIN_cmd, G_rxLine, sizeof(MAIN_cmd)-1);
                MAIN_cmd[sizeof(MAIN_cmd)-1] = '\0';
            }
            // Process command line
            if (G_echoCommand)
            {
                USB_printEOL();
                USB_printfLine("cmd = '%s'", MAIN_cmd);
            }
            if (strcmp(MAIN_cmd,"b") == 0)
            {
                FONT_BlackOnWhite = !FONT_BlackOnWhite;
                USB_printfLine("Toggle white/black letters %d", FONT_BlackOnWhite);
            }
            else if (strcmp(MAIN_cmd,"a") == 0)
            {
                handleLeftButton();
                USB_printLine("Left Button pressed");

            }
            else if (strcmp(MAIN_cmd,"s") == 0)
            {
                handleCenterButton();
                USB_printLine("Center Button pressed");
            }
            else if (strcmp(MAIN_cmd,"d") == 0)
            {
                handleRightButton();
                USB_printLine("Right Button pressed");
            }
            else if (strcmp(MAIN_cmd,"f") == 0)
            {
                USB_triggerPressed = !USB_triggerPressed;
                if (USB_triggerPressed)
                {
                    USB_printLine("Trigger pressed");
                }
                else
                {
                    USB_printLine("Trigger released");
                }

                // HandleTrigger();
            }
            else if (strcmp(MAIN_cmd,"e") == 0)
            {
                tableIndex = getModeIndex();
                const char *m0 = getModeName(0);
                const char *m1 = getModeName(1);
                FLASH_erasePage(tableIndex);
                USB_printfLine("Erasing Waveform %d [%s,%s]", tableIndex, m0, m1);
            }
            else if (strcmp(MAIN_cmd,"h") == 0)
            {
                USB_printLines(G_help);
            }
            else if (strcmp(MAIN_cmd,"w") == 0)
            { // write Wave
                FLASH_clearLoadBuffer();
                loadInProgress = true;
                tableIndex = getModeIndex();
                const char *m0 = getModeName(0);
                const char *m1 = getModeName(1);
                
                USB_printfLine("Loading table %d [%s,%s]", tableIndex, m0, m1);
                USB_printLine("Enter one value per line. Enter -1 to end");
                sampleIndex = 0;
            }
            else if (isUint(MAIN_cmd) && loadInProgress)
            {
                uint16_t loadValue = (int16_t)strtol(MAIN_cmd, NULL, 10);
                FLASH_appendLoadBuffer((uint32_t)loadValue);
            }
            else if (strcmp(MAIN_cmd, "-1") == 0)
            {
                loadInProgress = false;
                FLASH_appendLoadBuffer(-1);
                uint8_t pageNumber = getModeIndex();
                FLASH_writeLoadBuffer(pageNumber);
                USB_printWave();
            }
            else if (strcmp(MAIN_cmd,"m") == 0)
            {
                uint8_t mi = getModeIndex();
                const char *m0 = getModeName(0);
                const char *m1 = getModeName(1);
                USB_printfLine("Mode = %d [%s,%s]", mi, m0, m1);
            }
            else if (strcmp(MAIN_cmd, "r") == 0) // read wave
            {
                USB_printWave();
            }
            else if (strcmp(MAIN_cmd,"status") == 0)
            {
                USB_printLines(G_txtScreen);
            }
            else if (strcmp(MAIN_cmd,"t") == 0)
            {
                timeMonitor = !timeMonitor;
                cnt500usec = 0;
                cntSeconds = 0;
            }
            else if (strcmp(MAIN_cmd,"w") == 0)
            {
                FONT_BlackOnWhite = !FONT_BlackOnWhite;
                USB_printfLine("Toggle white/black letters %d", FONT_BlackOnWhite);
            }
            else if (isUint(MAIN_cmd)) // change mode
            {
                uint8_t modeIndex = (int8_t)strtol(MAIN_cmd, NULL, 10);
                uint8_t mode0Size = getModeSize(0);
                uint8_t mode1Size = getModeSize(1);
                uint8_t m0 = modeIndex / mode1Size;
                uint8_t m1 = modeIndex % mode1Size;
                if ((m0 < mode0Size) && (m1 < mode1Size))
                {
                    setMode(0, m0);
                    setMode(1, m1);
                    updateMode(G_mode[G_modeSel]);
                    const char *m0 = getModeName(0);
                    const char *m1 = getModeName(1);
                    USB_printfLine("Changing to %d [%s,%s]", modeIndex, m0, m1);
                }
            }
            else if (stringInArray(MAIN_cmd, G_modeNames0, 3) >= 0)
            {
                if (G_modeSel != 0)
                {
                    handleCenterButton();
                }
                int newSel = (uint8_t)stringInArray(MAIN_cmd, G_modeNames0, 3);
                G_mode[G_modeSel] = newSel;
                updateMode(G_mode[G_modeSel]);
                USB_printfLine("Changing 1st row '%s'",  MAIN_cmd);
            }
            else if (stringInArray(MAIN_cmd, G_modeNames1, 3) >= 0)
            {
                if (G_modeSel != 1)
                {
                    handleCenterButton();
                }
                G_mode[G_modeSel] = (uint8_t)stringInArray(MAIN_cmd, G_modeNames1, 3);
                updateMode(G_mode[G_modeSel]);
                USB_printfLine("Changing 2nd row '%s'",  MAIN_cmd);                
            }
            else
            {
                USB_printfLine("Undefined command '%s'",  MAIN_cmd); 
            }
            USB_printPrompt();
            G_rxLine[0] = '\0';
        }

        tempStart = (cnt == 1);
        tempDone = TC74_readTemp(tempStart, &temperature);
        if (tempDone) {
            bool tempChanged = (temperature != temperaturePrev);
            if (tempChanged)
            {
                G_displayStart = true;
                char *p_tempStr = &(G_txtScreen[G_screenLineTemp][12]);
                sprintf(p_tempStr, "%4dC ", temperature);
                bool rising = temperature > temperaturePrev;
                temperaturePrev = temperature;
                if (tempMonitor)
                {
                    USB_printfLinePrompt("Temperature %s to %d", 
                                         rising ? "rising" : "falling",
                                         temperature);
                }
            }
        }

        adcStart = (cnt == 1);
        adcDone = ADC_readVoltage(adcStart, &battVoltage);      
        if (adcDone)
        {
            // USB_PrintLinePrompt("ADC done");
            bool battChanged = (battVoltage != battVoltagePrev);
            if (battChanged)
            {
                uint16_t battVoltageMax = 1023;
                uint16_t battVoltageMin = 0; // 1024 * 14 / 18;
                uint16_t battVoltageDeltaMax = battVoltageMax - battVoltageMin;
                uint16_t battVoltageDeltaActual = 0;
                if (battVoltage > battVoltageMin)
                {
                    battVoltageDeltaActual = battVoltage - battVoltageMin;
                }
                uint16_t percent = 100 * battVoltageDeltaActual / battVoltageDeltaMax; 
                G_displayStart = true;
                char *p_battStr = &(G_txtScreen[G_screenLineBatt][12]);
                sprintf(p_battStr, "%4d%% ", percent);
                bool rising = battVoltage > battVoltagePrev;
                battVoltagePrev = battVoltage;
                if (battMonitor)
                {
                    USB_printfLinePrompt("Battery %s to %d", 
                                         rising ? "rising" : "falling",
                                         battVoltage);
                }
            }
        }

        displayInhibit = G_triggerFiring;
        if (!displayInhibit)
        {
            if (G_displayStart && !DISP_busy)
            {
                DISP_writeFrame(true);
                G_displayStart = false;
            }
            else
            {
                DISP_writeFrame(true);
            }
        }
        else
        {
            GPIO_set(DISP_CS, 0);
        }
   
        GPIO_set(LED1, G_triggerFiring);
        GPIO_set(LED2, DISP_vcom);
        USB_flushPrintBuffer();
    } // while (1)
    return 1;
}


