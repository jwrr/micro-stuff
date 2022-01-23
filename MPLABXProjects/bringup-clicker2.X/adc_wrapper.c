

#include <stdint.h>
#include <stdbool.h>
#include "mcc_generated_files/adc1.h"


#define ADC_BATT_CHANNEL channel_AN3

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
        ADC1_ChannelSelect(ADC_BATT_CHANNEL);
        ADC1_SoftwareTriggerEnable();
        ADC_conversionCnt = 1;
    }
    
    if (ADC_conversionCnt >= 1000)
    {
        ADC1_SoftwareTriggerDisable();
        while(!ADC1_IsConversionComplete(ADC_BATT_CHANNEL));
        *v = ADC1_ConversionResultGet(ADC_BATT_CHANNEL);
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
