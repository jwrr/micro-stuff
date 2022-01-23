

#include <stdint.h>
#include <stdbool.h>
#include "usb_wrapper.h"
#include "trigger_wrapper.h"
#include "dac_wrapper.h"
#include "disp_wrapper.h"
#include "flash_wrapper.h"
#include "mcc_generated_files/tmr3.h"


static int16_t TIME_sampleCurr = 0; // *p_waveformSample;
static int16_t TIME_samplePrev = 0; // FIXME use this in polling loop for interpolation

static uint16_t TIME_cnt500usec = 0;
static uint16_t TIME_cntSeconds = 0;
static bool TIME_timeTickMonitor = false;


bool TIME_isTimeMonitorEnabled(void)
{
    return TIME_timeTickMonitor;
}

void TIME_enableTimeMonitor(bool newVal)
{
    TIME_timeTickMonitor = newVal;
}

void TIME_clearCount()
{
    TIME_cnt500usec = 0;
    TIME_cntSeconds = 0;
}

static uint8_t  TIME_pageNumber = 0;
static uint16_t TIME_pageOffset = 0;

void TMR3_callBack(void)
{
    bool isSignalOn = TRIG_isSignalOn();
    if (isSignalOn)
    {
        int16_t sample = FLASH_readSample(TIME_pageNumber, TIME_pageOffset);
        if (sample < 0)
        {
            TIME_pageOffset = 0;
            sample = FLASH_readSample(TIME_pageNumber, TIME_pageOffset);
            if (sample < 0) return;
        }
        TIME_pageOffset++;
        sample &= 0x0FFF; // clamp to 12-bits
        DAC_writeSPI(true, (uint16_t)TIME_sampleCurr);
    }
    TIME_cnt500usec++;
    
    if (TIME_cnt500usec >= 2000)
    {
        if (!isSignalOn)
        {
            TIME_pageNumber = DISP_getModeIndex();
            TIME_pageOffset = 0;
        }
        TRIG_handleTrigger();
        TIME_cnt500usec = 0; // reset every second
        TIME_cntSeconds++; // increment every second
        if (TIME_timeTickMonitor)
        {
            uint16_t tm3TimerCount = TMR3_Counter16BitGet();
            USB_printfLinePrompt("TMR3 callback = %d seconds %d. sample = %d", TIME_cntSeconds, tm3TimerCount, TIME_samplePrev);
        }
    }
}
