
#include "mcc_generated_files/system.h"
#include "gpio.h"
#include "dac.h"

#define DAC_IDLE 0xFFFF


void DAC_writeSPI1(uint16_t dacVal)
{
    GPIO_set(GPIO_DACCS);
    GPIO_clr(GPIO_DACCS);
    SPI2BUFL = dacVal;
}

uint16_t DAC_csHigh;
uint16_t DAC_csLow;

void DAC_writeSPI2(uint16_t dacVal)
{
    uint8_t cnt = 2;
    while (cnt) cnt--;
//    GPIO_set(GPIO_DACCS);
//    GPIO_clr(GPIO_DACCS);
    LATE = DAC_csHigh;
    LATE = DAC_csLow;
//    while (SPI2STATLbits.SPIRBE);
    SPI2BUFL = dacVal;
//    GPIO_clr(GPIO_DACCS);
    uint16_t unused = SPI2BUFL; // clears SPIRBE
}



int main(void)
{
    uint16_t dacVal = 0;

    // initialize the device
    SYSTEM_Initialize();
    DAC_writeSPI1(0);
    
    DAC_csLow = LATE;
    DAC_csHigh = DAC_csLow | 0x0010;
    
    while (1)
    {
//        cnt = (cnt==100000) ? 0 : cnt + 1;
//        if (cnt == 1)
//        {
//            GPIO_toggle(GPIO_LED1);
//            GPIO_toggle(GPIO_LED2);
//
//        }
        DAC_writeSPI2(dacVal);
        dacVal += 512;
        dacVal &= 0xfff;
    }
    return 1;
}
/**
 End of File
*/

