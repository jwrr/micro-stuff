/*
    (c) 2017 Microchip Technology Inc. and its subsidiaries. You may use this
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

/*
    MCC USB CDC Demo Usage:
 
    Call the MCC_USB_CDC_DemoTasks() function from your main loop.
    It will read data sent from the host and echo it back +1.  If you open
    up a terminal window and type 'a' then 'b' will be echoed back.
 */
#include <stdint.h>

#include "usb.h"
#include "../../ring.h"

static uint8_t readBuffer[64];
static uint8_t writeBuffer[64];

#define COM_RINGSIZE 512
static uint8_t USB_rxBuffer[COM_RINGSIZE] = {0};
static ring_t USB_rxRing = {0};
ring_t *USB_rx = &USB_rxRing;

static uint8_t USB_txBuffer[COM_RINGSIZE] = {0};
static ring_t USB_txRing = {0};
ring_t *USB_tx = &USB_txRing;

static uint8_t USB_tmpBuffer[COM_RINGSIZE] = {0};


void ringInit()
{
    if (!RING_isInit(USB_rx))
    {
        RING_init(USB_rx, USB_rxBuffer, sizeof(USB_rxBuffer));
    }

    if (!RING_isInit(USB_tx))
    {
        RING_init(USB_tx, USB_txBuffer, sizeof(USB_txBuffer));
    }
}

bool USB_isUp()
{
    if( USBGetDeviceState() < CONFIGURED_STATE )
    {
        return false;
    }

    if( USBIsDeviceSuspended()== true )
    {
        return false;
    }
    return true;
}
    
void USB_maintenance()
{
    if( USBUSARTIsTxTrfReady() == true)
    {
        while (!RING_isFull(USB_rx))
        {
            uint8_t ch;
            uint8_t numBytesRead = getsUSBUSART(&ch, 1);
            if (numBytesRead == 0) break;
            RING_write(USB_rx, &ch, 1);
        }

        if (RING_hasData(USB_tx)) {
            uint16_t len = RING_read(USB_tx, USB_tmpBuffer, sizeof(USB_tmpBuffer));
            putUSBUSART(USB_tmpBuffer, len);
        }
    }
    CDCTxService();
}

void MCC_USB_CDC_DemoTasks(void)
{
    if (!USB_isUp()) return;

    uint8_t i;
    uint8_t numBytesRead;
    ringInit();
    
    numBytesRead = RING_read(USB_rx, readBuffer, sizeof(readBuffer));
    memcpy(writeBuffer, readBuffer, sizeof(writeBuffer));
    RING_write(USB_tx, writeBuffer, numBytesRead);
    
    USB_maintenance();
}
