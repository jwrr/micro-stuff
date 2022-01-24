

#include <stdint.h>
#include <stdbool.h>
#include "mcc_generated_files/adc1.h"
#include "disp_wrapper.h"
#include "usb_wrapper.h"


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


static int16_t ADC_battVoltageCurr =  0;
static int16_t ADC_battVoltagePrev =  0;
static bool ADC_battMonitor = false;

void ADC_handleBatteryVoltage(uint16_t pollingLoopCnt)
{
    bool adcStart = (pollingLoopCnt == 1);
    bool adcDone = ADC_readVoltage(adcStart, &ADC_battVoltageCurr);      
    if (adcDone)
    {
        // USB_PrintLinePrompt("ADC done");
        bool battChanged = (ADC_battVoltageCurr != ADC_battVoltagePrev);
        if (battChanged)
        {
            uint16_t battVoltageMax = 1023;
            uint16_t battVoltageMin = 0; // 1024 * 14 / 18;
            uint16_t battVoltageDeltaMax = battVoltageMax - battVoltageMin;
            uint16_t battVoltageDeltaActual = 0;
            if (ADC_battVoltageCurr > battVoltageMin)
            {
                battVoltageDeltaActual = ADC_battVoltageCurr - battVoltageMin;
            }
            uint16_t percent = 100 * battVoltageDeltaActual / battVoltageDeltaMax; 
            DISP_enableDisplayThisCycle();
            char *batteryLine = DISP_getBatteryLinePtr();
            char *batteryField = &(batteryLine[12]);
            sprintf(batteryField, "%4d%% ", percent);
            bool rising = ADC_battVoltageCurr > ADC_battVoltagePrev;
            ADC_battVoltagePrev = ADC_battVoltageCurr;
            if (ADC_battMonitor)
            {
                USB_printfLinePrompt("Battery %s to %d", 
                                     rising ? "rising" : "falling",
                                     ADC_battVoltageCurr);
            }
        }
    }
}

