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

#include "mcc_generated_files/memory/flash.h"
#include "usbprint.h"

static const uint8_t G_flashNumPages = 10;
static const uint16_t G_flashPageSize = 1024;

// Allocate and reserve pages of flash.  The compiler/linker will reserve this for data and not place any code here.
static __prog__  uint8_t flashPage0[FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS] __attribute__((space(prog),aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS)));
static __prog__  uint8_t flashPage1[FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS] __attribute__((space(prog),aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS)));
static __prog__  uint8_t flashPage2[FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS] __attribute__((space(prog),aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS)));
static __prog__  uint8_t flashPage3[FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS] __attribute__((space(prog),aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS)));
static __prog__  uint8_t flashPage4[FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS] __attribute__((space(prog),aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS)));
static __prog__  uint8_t flashPage5[FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS] __attribute__((space(prog),aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS)));
static __prog__  uint8_t flashPage6[FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS] __attribute__((space(prog),aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS)));
static __prog__  uint8_t flashPage7[FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS] __attribute__((space(prog),aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS)));
static __prog__  uint8_t flashPage8[FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS] __attribute__((space(prog),aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS)));
static __prog__  uint8_t flashPage9[FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS] __attribute__((space(prog),aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS)));

static uint32_t FLASH_getPageAddress(uint32_t flashPageNumber)
{
    switch (flashPageNumber)
    {
    case 0:  return FLASH_GetErasePageAddress((uint32_t)&flashPage0[0]);
    case 1:  return FLASH_GetErasePageAddress((uint32_t)&flashPage1[0]);
    case 2:  return FLASH_GetErasePageAddress((uint32_t)&flashPage2[0]);
    case 3:  return FLASH_GetErasePageAddress((uint32_t)&flashPage3[0]);
    case 4:  return FLASH_GetErasePageAddress((uint32_t)&flashPage4[0]);
    case 5:  return FLASH_GetErasePageAddress((uint32_t)&flashPage5[0]);
    case 6:  return FLASH_GetErasePageAddress((uint32_t)&flashPage6[0]);
    case 7:  return FLASH_GetErasePageAddress((uint32_t)&flashPage7[0]);
    case 8:  return FLASH_GetErasePageAddress((uint32_t)&flashPage8[0]);
    default: return FLASH_GetErasePageAddress((uint32_t)&flashPage9[0]);
    }
    return 0;
}

uint32_t FLASH_getPageSize()
{
    return G_flashPageSize;
}

uint32_t FLASH_getNumPages()
{
    return G_flashNumPages;
}

uint8_t FLASH_erasePage(uint8_t PageNumber)
{
    uint32_t flashPageBaseAddress = FLASH_getPageAddress(PageNumber);
    bool success = FLASH_ErasePage(flashPageBaseAddress);
    return success ? 0 : 1;
}


uint8_t FLASH_writePage(int32_t writeData[], uint32_t dataSize, uint8_t pageNumber)
{
    uint8_t  err = 0;
    uint32_t flashPageBaseAddress = FLASH_getPageAddress(pageNumber);
    
    // Get flash page aligned address of flash reserved above for this test.
    if (flashPageBaseAddress == 0) // invalid NULL address
    {
        return 1;
    }

    FLASH_Unlock(FLASH_UNLOCK_KEY);
    
    // ------------------------------------------
    // Fill a page of memory with data.  
    // ------------------------------------------
    
    // Erase the page of flash at this address
    bool success = FLASH_ErasePage(flashPageBaseAddress);
    if (!success)
    {
        err = 2;
    }
  
    // Program flash with a data pattern.  For the data pattern we will use the index 
    // into the flash as the data.
    uint32_t pageSize = FLASH_getPageSize();
    dataSize = (dataSize < pageSize) ? dataSize : pageSize;
    uint32_t iii = 0;
//    for (flashOffset= 0U; flashOffset< FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS; flashOffset += 4U)
    uint32_t flashOffset;
    for (flashOffset= 0U; flashOffset < 2*dataSize; flashOffset += 4U)
    {
        uint32_t d0 = writeData[iii++];
        uint32_t d1 = writeData[iii++];
        uint32_t flashAddress = flashPageBaseAddress+flashOffset;
        success = FLASH_WriteDoubleWord24(flashAddress, d0, d1);
        if (!success)
        {
            err = 3;
        }   
    }

    // Clear Key for NVM Commands so accidental call to flash routines will not corrupt flash
//    FLASH_Lock();
//    
//       for (flashOffset= 0U; flashOffset < 2*10; flashOffset += 4U)
//    {
//        uint32_t flashAddress = flashPageBaseAddress+flashOffset;
//        int32_t readData = FLASH_ReadWord24(flashAddress);
//        USB_printfLine("%4x", (int)readData);
//    } 
    
    return err;
}

uint8_t FLASH_writePages(int32_t writeData[], uint32_t dataLen)
{
    uint8_t err = 0;
    uint8_t pageNumber = 0;
    uint16_t pageSize = FLASH_getPageSize();
    while (dataLen > 0)
    {
        uint32_t writeDataOffset = pageNumber * pageSize;
        int32_t *writeDataPageAddress = &(writeData[writeDataOffset]);
        err = FLASH_writePage(writeDataPageAddress, dataLen, pageNumber);
        if (err)
        {
            break;
        }
        if (dataLen <= pageSize) break;
        dataLen -= pageSize;
        pageNumber++;
    }
    return err;
}



char USB_tmpStr[80];
static bool G_enablePrompt = true;
static char *G_prompt = "> ";

int32_t FLASH_read(uint32_t flashOffset)
{
    const uint16_t pageSize = FLASH_getPageSize();
    const uint8_t pageNumber = flashOffset / pageSize;
    const uint16_t pageOffset = 2 * (flashOffset % pageSize);
    const uint32_t flashPageBaseAddress = FLASH_getPageAddress(pageNumber);
    const uint32_t flashAddress = flashPageBaseAddress + pageOffset;
    int32_t readData = FLASH_ReadWord24(flashAddress);
//    if (pageOffset >= 2048) {
//       USB_printfLine("ps=%d, pn=%d, fox2=%d rd=%04x", pageSize, pageNumber, (int)pageOffset, (int)readData);
//    }
    return readData;
}

uint8_t FLASH_writeTable(int32_t currentTable[], uint16_t tableLen, uint8_t flashPageNumber)
{
    uint8_t err = FLASH_writePage(currentTable, tableLen, flashPageNumber);
    return err;
}

uint8_t FLASH_verify(const int32_t dataTable[], uint16_t len, uint8_t pageNumber)
{
    int32_t flashRdata;
    uint16_t failCnt = 0;
    uint16_t i = 0;
    uint16_t pageBase = pageNumber * FLASH_getPageSize();
    for (; i < len; i++)
    {
        int raddr = pageBase + i;
        flashRdata = FLASH_read(raddr);
        bool fail = (flashRdata != dataTable[i]);
        if (fail)
        {
            failCnt++;
            if (failCnt < 10)
            {
                int16_t upper = flashRdata >> 16;
                int16_t lower = flashRdata & 0xffff;
                USB_printfLine("Fail: addr = %d, actual = %04x_%04x expected = %04x", raddr, upper, lower, (int)dataTable[i]);
            }
            else if (failCnt == 11)
            {
                USB_printLine("Fail again: fail message disabled...");
            }
        }
    }
    return (failCnt > 0) ? 1 : 0;
}


uint8_t FLASH_test()
{
    const uint32_t pageSize = FLASH_getPageSize();
    int32_t testData[pageSize];


    int pageNumber = 0;
    uint8_t err = 0;
    const int32_t valid = 0x00010000;
    for (; pageNumber<9; pageNumber++)
    {
        int i;
        for (i=0; i < pageSize; i++)
        {
            testData[i] = (pageNumber*pageSize + i) | valid;
        }
        err = FLASH_writePage(testData, pageSize, pageNumber);
        if (err)
        {
            USB_printfLinePrompt("FLASH WRITE ERROR #%d", err);
            return 1;
        }
    }
    USB_printLine("FLASH WRITE done");
    
    for (pageNumber=0; pageNumber<9; pageNumber++)
    {
        int i;
        for (i=0; i < pageSize; i++)
        {
            testData[i] = (pageNumber*pageSize + i) | valid;
        }
        err = FLASH_verify(testData, pageSize, pageNumber);
        if (err)
        {
            USB_printLinePrompt("FLASH READ Test failed");
            return 2;
        }
    }
    USB_printLine("FLASH READ done");

    for (pageNumber=0; pageNumber<9; pageNumber++)
    {
        err = FLASH_erasePage(pageNumber);
        if (err)
        {
            USB_printLinePrompt("FLASH ERASE failed");
            return 3;
        }
        int i;
        for (i=0; i < pageSize; i++)
        {
            testData[i] = 0x00ffffff;
        }
        err = FLASH_verify(testData, pageSize, pageNumber);
        if (err)
        {
            USB_printLinePrompt("FLASH ERASE failed");
            return 4;
        }
    }        

    USB_printLinePrompt("FLASH WRITE/READ/ERASE Test passed");
    return 0;
}    
    
void FLASH_memcpy16to32(int32_t dest32[], int16_t src16[], uint16_t len, int32_t upperWordVal)
{
    int i = 0;
    for (; i < len; i++)
    {
        dest32[i] = ((int32_t)src16[i]) | (upperWordVal << 16);
    }
}


