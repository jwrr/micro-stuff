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
    if( USBGetDeviceState() < CONFIGURED_STATE )
    {
        return false;
    }

    /* If we are currently suspended, then we need to see if we need to
     * issue a remote wakeup.  In either case, we shouldn't process any
     * keyboard commands since we aren't currently communicating to the host
     * thus just continue back to the start of the while loop. */
    if( USBIsDeviceSuspended()== true )
    {
        return false;
    }

    CDCTxService();

    /* Make sure that the CDC driver is ready for a transmission.
    * Check to see if there is a transmission in progress, if there isn't, then
    * we can see about performing an echo response to data received.
    */
    if (USBUSARTIsTxTrfReady() == false)
        return false;

    return true;
} // usbUp

uint8_t usbGetByte(uint8_t *val)
{
    if (!usbUp())
    {
        return 0;
    }
    uint8_t numBytesRead = getsUSBUSART(readBuffer, 1);
    *val = readBuffer[0];
    return numBytesRead;
} // usbGetByte

uint8_t usbPutByte(uint8_t val)
{
    if (!usbUp())
    {
        return 0;
    }
    writeBuffer[0] = val;           
    putUSBUSART(writeBuffer,1);
    return 1;
} // usbPutByte

uint8_t usbPutString(char *str)
{
    if (!usbUp())
    {
        return 0;
    }
    putrsUSBUSART(str);
    return 1;
} // usbPutString

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
    uint8_t ch;
    
    while (1)
    {
        switch (state)
        {
        case 0:
            numBytes = usbPutString("Hello from PIC\r\n");
            if (numBytes > 0) {
                state = 1;
            }
            break;
        case 1:
            numBytes = usbGetByte(&ch);
            if (numBytes > 0) {
                numBytes = usbPutByte(toupper(ch));
            }
            break;
        default:
            break;
        }

    } // while

    return 1;
}
/**
 End of File
*/

