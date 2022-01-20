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
static char USB_tmpStr[USB_LINELEN+1];
static bool G_enablePrompt = true;
static char G_prompt[] = "=> ";

// Allocate and reserve a page of flash for this test to use.  The compiler/linker will reserve this for data and not place any code here.
static __prog__  uint8_t flashPage0[FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS] __attribute__((space(prog),aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS)));
static __prog__  uint8_t flashPage1[FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS] __attribute__((space(prog),aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS)));
static __prog__  uint8_t flashPage2[FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS] __attribute__((space(prog),aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS)));

// We have detected a flash hardware error of some type.
static void FlashError()
{
    while (1) 
    { }
}

static void MiscompareError()
{
    while (1) 
    { }
}
   
void FLASH_writePage(uint32_t writeData[], uint32_t dataSize, uint16_t startIndex)
{
//    dataSize = 1024;
    uint32_t flash_storage_address, flashOffset;
    bool result;
    
    // Get flash page aligned address of flash reserved above for this test.
    if (startIndex < 1024)
    {
            flash_storage_address = FLASH_GetErasePageAddress((uint32_t)&flashPage0[0]);
    }
    else if (startIndex < 2*1024)
    {
            flash_storage_address = FLASH_GetErasePageAddress((uint32_t)&flashPage1[0]);
    }
    else
    {
        flash_storage_address = FLASH_GetErasePageAddress((uint32_t)&flashPage2[0]);
    }

    FLASH_Unlock(FLASH_UNLOCK_KEY);
    
    // ------------------------------------------
    // Fill a page of memory with data.  
    // ------------------------------------------
    
    // Erase the page of flash at this address
    result = FLASH_ErasePage(flash_storage_address);
    if (result == false)
    {
        FlashError();
    }
  
    // Program flash with a data pattern.  For the data pattern we will use the index 
    // into the flash as the data.
//    dataSize = (dataSize < FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS) ? dataSize : FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS;
    dataSize = (dataSize < 1024) ? dataSize : 1024;
    uint32_t iii = startIndex;
//    for (flashOffset= 0U; flashOffset< FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS; flashOffset += 4U)
    for (flashOffset= 0U; flashOffset < 2*dataSize; flashOffset += 4U)
    {
        uint32_t d0 = writeData[iii++];
        uint32_t d1 = writeData[iii++];
        result = FLASH_WriteDoubleWord24(flash_storage_address+flashOffset, d0, d1); // d0, d1); // wdata32[i++], wdata32[i++]);
        if (result == false)
        {
            FlashError();
        }   
    }

    // Clear Key for NVM Commands so accidental call to flash routines will not corrupt flash
    FLASH_Lock();
}

void FLASH_writePages(uint32_t writeData[], uint32_t dataSize)
{
    uint8_t pageIndex = 0;
    while (dataSize > 0)
    {
        FLASH_writePage(writeData, dataSize, pageIndex*1024);
        if (dataSize <= 1024) break;
        dataSize -= 1024;
        pageIndex++;
    }   
}


uint32_t FLASH_read_uint32(uint32_t flashOffset)
{
    const uint16_t pageSize = 1024;
    uint32_t flash_storage_address;
    if (flashOffset < 1*pageSize)
    {
        flash_storage_address = FLASH_GetErasePageAddress((uint32_t)&flashPage0[0]);
    }
    else if (flashOffset < 2*pageSize)
    {
        flashOffset -= 1*pageSize;
        flash_storage_address = FLASH_GetErasePageAddress((uint32_t)&flashPage1[0]);
    }
    else
    {
        flashOffset -= 2*pageSize;
        flash_storage_address = FLASH_GetErasePageAddress((uint32_t)&flashPage2[0]);        
    }

    flashOffset *= 2;
    uint32_t readData = FLASH_ReadWord24(flash_storage_address+flashOffset);
    return readData;
}



