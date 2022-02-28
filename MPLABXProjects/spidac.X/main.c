
#include "mcc_generated_files/system.h"
#include "gpio.h"
#include "dac.h"

int main(void)
{
    uint16_t dacVal = 0;

    // initialize the device
    SYSTEM_Initialize();
    DAC_writeSPI1(0);
    
    DAC_setCS((LATE | 0x0010), LATE);
    
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

