
#include "usb_wrapper.h"
#include <stdbool.h>
#include "mcc_generated_files/usb/usb.h"

static uint8_t USB_readBuffer[CDC_DATA_OUT_EP_SIZE];
static char USB_tmpStr[USB_LINELEN+1];
static char USB_writeBuffer[USB_WRITE_BUFFER_SIZE];
static char *USB_writeBufferHead = USB_writeBuffer;
static char *USB_writeBufferTail = USB_writeBuffer;
static char *USB_writeBufferMax = USB_writeBuffer + sizeof(USB_writeBuffer);

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

uint8_t USB_print(const char *str)
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


uint8_t USB_flushPrintBuffer(void)
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

bool USB_readLine(char line[], uint16_t maxLen, bool echo)
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
        readBufferLen = getsUSBUSART(USB_readBuffer, sizeof(USB_readBuffer));
        if (readBufferLen == 0)
        {
            return false;
        }
    }
    
    while (readBufferPos < readBufferLen) {
        ch = USB_readBuffer[readBufferPos++];
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


static char USB_prompt[8] = "=> ";
void USB_setPrompt(char *newPrompt)
{
    uint16_t promptSize = sizeof(USB_prompt);
    strncpy(USB_prompt, newPrompt, promptSize);
    USB_prompt[promptSize-1] = '\0';
}

const char *USB_getPrompt(void)
{
    return USB_prompt;
}

static bool USB_enablePrompt = true;
void USB_setEnablePrompt(bool newVal)
{
    USB_enablePrompt = newVal;
}

bool USB_getEnablePrompt(void)
{
    return USB_enablePrompt;
}


static bool USB_echoCommand = false;
void USB_setEchoCommand(bool newVal)
{
    USB_echoCommand = newVal;
}

bool USB_getEchoCommand(void)
{
    return USB_echoCommand;
}

static bool USB_echoChar = false;
void USB_setEchoChar(bool newVal)
{
    USB_echoChar = newVal;
}

bool USB_getEchoChar(void)
{
    return USB_echoChar;
}


char *USB_getTmpStr(void)
{
    return USB_tmpStr;
}


#include "disp_wrapper.h"
#include "flash_wrapper.h"
void USB_printWave(void)
{
    uint8_t tableIndex = DISP_getModeIndex();
    if (FLASH_isValid(tableIndex, 0))
    {
        USB_printfLine("Custom Waveform[%d] = ", tableIndex);
    }
    else
    {
        USB_printfLine("Factory Waveform[%d] = ", tableIndex);
    }
    uint16_t i;
    bool done = false;
    for (i=0; i<257; i+=2)
    {
        int16_t value16 = FLASH_readSample(tableIndex, i);
        done = (value16 < 0);
        if (done) break;
        USB_printf("%d, ", (int)value16);
        
        // flash is initially 0
        // after page is written and erased it's 0x00FFFFFF
        // table writer sets bit 16 "valid" bit, so all values should  be in
        // the range of 0x10000 to 0x1ffff
//        int32_t value32 = FLASH_readFromPage(tableIndex, i);
//        bool outOfRange = (value32 < 0x10000) || (value32 > 0x1ffff);
//        int32_t value16 = value32 & 0xffff; // trim valid bit
//        bool isNegative = (value16 > 0x7fff);
//        done = outOfRange || isNegative;
//        if (done) break;
//        USB_printf("%d, ", (int)value16);
//        int32_t upper = value32 >> 16;
//        int32_t lower = value32 & 0xFFFF;
//        USB_printfLine("%04x%04x %d %d %d %d, ", (int)upper, (int)lower, (int)value16,  outOfRange, isNegative, done);
    }
    USB_printLine("-1");
}
