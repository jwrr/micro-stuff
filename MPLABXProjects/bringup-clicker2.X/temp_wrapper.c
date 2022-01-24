

#include <stdint.h>
#include <stdbool.h>
#include "mcc_generated_files/i2c3.h"
#include "disp_wrapper.h"
#include "usb_wrapper.h"

// ==========================================================
// TC74 i2c temperature sensor

#define I2C_ADDR_TC74  0X4D  // A5 Default

uint8_t TC74_state = 0;
uint8_t TC74_temp = 0;
uint8_t TC74_cmd = 0; // read temperature. 1 = standby
I2C3_MESSAGE_STATUS TC74_status;

bool TEMP_readTemperature(bool start, int8_t *t)
{
    const uint8_t len = 1;
    bool done = false;
    *t = TC74_temp;
    
    switch (TC74_state)
    {
    case 0:
        if (start)
        {
            I2C3_MasterWrite( &TC74_cmd, len, I2C_ADDR_TC74, &TC74_status);
            TC74_state = 1;
        }
        break;
    case 1:
        if (TC74_status != I2C3_MESSAGE_PENDING) {
            TC74_state++;
        }
        break;
    case 2:
        I2C3_MasterRead( &TC74_temp, len, I2C_ADDR_TC74, &TC74_status);
        TC74_state++;
        break;
    case 3:
        if (TC74_status != I2C3_MESSAGE_PENDING) {
            TC74_state++;
        }
        break;
    case 4:
        TC74_state = 0;
        *t = (int8_t)(TC74_temp);
        done = true;
        break;
    default:
        TC74_state = 0;
        break;
    }
    return done;
}

static int8_t TEMP_temperatureCurr = 0;
static int8_t TEMP_temperaturePrev = 0;
static bool TEMP_temperatureMonitor = false;

void TEMP_handleTemperature(uint16_t pollingLoopCnt)
{
    bool tempStart = (pollingLoopCnt == 1);
    bool tempDone = TEMP_readTemperature(tempStart, &TEMP_temperatureCurr);
    if (tempDone) {
        bool tempChanged = (TEMP_temperatureCurr != TEMP_temperaturePrev);
        if (tempChanged)
        {
            DISP_enableDisplayThisCycle();
            char *temperatureLine = DISP_getTemperatureLinePtr();
            char *temperatureField = &(temperatureLine[12]);
            sprintf(temperatureField, "%4dC ", TEMP_temperatureCurr);
            TEMP_temperaturePrev = TEMP_temperatureCurr;
            if (TEMP_temperatureMonitor)
            {
                bool rising = TEMP_temperatureCurr > TEMP_temperaturePrev;
                USB_printfLinePrompt("Temperature %s to %d", 
                                     rising ? "rising" : "falling",
                                     TEMP_temperatureCurr);
            }
        }
    }
}

uint16_t TEMP_getTemperature(void)
{
    return TEMP_temperatureCurr;
}
