
#include <stdbool.h>
#include <string.h>
#include "ring.h"
#include "mcc_generated_files/usb/usb.h"

#define USB_RINGSIZE 512
static uint8_t USB_rxBuffer[USB_RINGSIZE] = {0};
static ring_t USB_rxRing = {0};
static ring_t *USB_rx = &USB_rxRing;

static uint8_t USB_txBuffer[USB_RINGSIZE] = {0};
static ring_t USB_txRing = {0};
static ring_t *USB_tx = &USB_txRing;

uint8_t USB_tmpBuffer[USB_RINGSIZE] = {0};

static bool USB_ringInit(ring_t *rx, ring_t *tx)
{
    if (!RING_isInit(rx))
    {
        bool success = RING_init(USB_rx, USB_rxBuffer, sizeof(USB_rxBuffer));
        if (!success) return false;
    }

    if (!RING_isInit(tx))
    {
        bool success = RING_init(USB_tx, USB_txBuffer, sizeof(USB_txBuffer));
        if (!success) return false;
    }
    return true;
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
    bool success = USB_ringInit(USB_rx, USB_tx);
    return success;
}

uint16_t USB_read(uint8_t *data, uint16_t maxReadLen)
{
    if (!USB_isUp()) return 0;
    uint16_t len = RING_read(USB_rx, data, maxReadLen);
    return len;
}

uint16_t USB_readString(char *str, uint16_t maxStrLen)
{
    uint16_t len = USB_read((uint8_t*)str, maxStrLen-1);
    str[len] = '\0';
    return len;
}

int16_t USB_readLine(char *str, uint16_t strSize)
{
    int16_t eolnPos = RING_search(USB_rx, '\n');
    bool found = (eolnPos >= 0);
    if (!found)
    {
        str[0] = '\0';
        return -1;
    }
    uint16_t len = eolnPos;
    if (len > strSize - 1)
    {
        len = strSize - 1;
    }
    USB_read((uint8_t*)str, len);
    str[len] = '\0';
    return len;
}

bool USB_write(uint8_t *data, uint16_t len)
{
    if (!USB_isUp()) return false;
    if (len == 0) return true;
    bool success = RING_write(USB_tx, data, len);
    return success;
}

bool USB_writeString(char *str)
{
    uint8_t len = strlen(str);
    bool success = USB_write((uint8_t*)str, len+1);
    return success;
}

bool USB_writeLine(char *str)
{
    bool success = USB_writeString(str);
    if (!success) return false;
    success = USB_writeString("\n\r");
    return success;
}

bool USB_maintenance()
{
    if (!USB_isUp()) return false;
    bool ready = USBUSARTIsTxTrfReady();
    if(ready)
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
    return ready;
}
