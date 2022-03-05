
#include "mcc_generated_files/system.h"
#include "gpio.h"
#include "dac.h"

extern uint16_t DAC_val;

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
//    DAC_writeSPI2FastInit(0);
//    DAC_setCS((LATE | 0x0010), LATE);
    
    GPIO_clr(GPIO_LED1);
    GPIO_clr(GPIO_LED2);
    uint16_t cnt = 0;
    const uint16_t cntMax = 100000;
    DAC_init(GPIO_DACSPI, GPIO_DACCS);
    while (1)
    {
        cnt = (cnt==cntMax) ? 0 : cnt + 1;
        if (cnt == 1)
        {
            GPIO_toggle(GPIO_LED1);
        }
        if (cnt == cntMax >> 1)
        {
            GPIO_toggle(GPIO_LED2);
        }
        DAC_val += 512;
        DAC_write(GPIO_DACSPI, GPIO_DACCS, DAC_val);
//        DAC_writeSPI2Fast();
    }
    return 1;
}

