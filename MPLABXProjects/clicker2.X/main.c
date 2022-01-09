/*
 * When LEFT button is pressed LED1 is on
 * When RIGHT button is pressed LED2 is on
 * When CENTER button is pressed both LED1 and LED2 are on
 * When T2 Trig is pressed both LED1 and LED2 flash
 * When T3 button is press LED1 flashes fast and LED2 flashes slow
 * When no buttons are pressed LED2 flashes and LED1 is on when near room temp.
*/


#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/interrupt_manager.h"
#include "mcc_generated_files/i2c3.h"

/*
                         Main application
 */

#define I2C_ADDR_TC74  0X4D  // A5 Default

int8_t TC74_readTemp(void)
{
    uint8_t temp;
    uint8_t TC74_cmd = 0; // read temperature. 1 = standby
    I2C3_MESSAGE_STATUS status;
    uint8_t len = 1;
    I2C3_MasterWrite( &TC74_cmd, len, I2C_ADDR_TC74, &status);
    while (status == I2C3_MESSAGE_PENDING);

    I2C3_MasterRead( &temp, len, I2C_ADDR_TC74, &status);
    while (status == I2C3_MESSAGE_PENDING);
    return (int8_t)temp;
}

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    INTERRUPT_GlobalEnable(); // FOR I2C TC74
    
    uint32_t i = 0;
    RE8_LED1_Toggle();
    while (1)
    {
        for (i=0; i<100000; i++);
        if (!RG0_LEFT_GetValue())
        {
            RE8_LED1_SetHigh();
            RG13_LED2_SetLow();            
        }
        else if (!RF2_RIGHT_GetValue())
        {
            RE8_LED1_SetLow();
            RG13_LED2_SetHigh(); 
        }
        else if (!RD6_CENTER_GetValue())
        {
            RE8_LED1_SetHigh();
            RG13_LED2_SetHigh();
        }
        else if (!RA0_T2_GetValue())
        {
            RE8_LED1_Toggle();
            RG13_LED2_Toggle();
        }
        else if (!RE2_T3_GetValue())
        {
            RE8_LED1_Toggle();
            if (RE8_LED1_GetValue())
            {
                RG13_LED2_Toggle();
            }
        }
        else // no buttons pressed. check temperature
        {
//            RE8_LED1_SetLow();
//            RG13_LED2_SetLow();
    
            int8_t temp = TC74_readTemp();
            bool roomTemp = (temp >= 17) && (temp <= 22);

//          if ( (temp >= 19) && (temp <= 20))
            if (roomTemp)
            {
                RE8_LED1_SetHigh();
            }
            else
            {
                RE8_LED1_SetLow();
            }
            RG13_LED2_Toggle();
        }    

// Trial 2 - external buttons
//        if (!RG0_LEFT_GetValue())
//        {
//            RE8_LED1_SetHigh();
//            RG13_LED2_SetLow();            
//        }
//        else if (!RF2_RIGHT_GetValue())
//        {
//            RE8_LED1_SetLow();
//            RG13_LED2_SetHigh(); 
//        }
//        else if (!RD6_CENTER_GetValue())
//        {
//            RE8_LED1_SetHigh();
//            RG13_LED2_SetHigh();
//        }
//        else if (!RA0_T2_GetValue())
//        {
//            RE8_LED1_Toggle();
//            RG13_LED2_Toggle();
//        }
//        else if (!RE2_T3_GetValue())
//        {
//            RE8_LED1_Toggle();
//            if (RE8_LED1_GetValue())
//            {
//                RG13_LED2_Toggle();
//            }
//        }
//        else
//        {
//            RE8_LED1_SetLow();
//            RG13_LED2_SetLow();            
//        }

// Trial 1 - clicker2 buttons and LEDS
//        if ( RE2_T3_GetValue())
//        {
//            RE8_LED1_Toggle();
//        }
//        else
//        {
//            RE8_LED1_SetHigh();
//        }
//        
//        if (RA0_T2_GetValue())
//        {
//            RG13_LED2_Toggle();
//        }
//        else
//        {
//            RG13_LED2_SetHigh();
//        }
    } // while

    return 1;
}

