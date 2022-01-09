/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  PIC24FJ1024GB610
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB 	          :  MPLAB X v5.45
*/

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

/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/interrupt_manager.h"
#include "mcc_generated_files/i2c3.h"

/*
                         Main application
 */

//#define I2C_ADDR_TC74  0X48  // A0
//#define I2C_ADDR_TC74  0X49  // A1
//#define I2C_ADDR_TC74  0X4A  // A2
//#define I2C_ADDR_TC74  0X4B  // A3
//#define I2C_ADDR_TC74  0X4C  // A4
#define I2C_ADDR_TC74  0X4D  // A5 Default
//#define I2C_ADDR_TC74  0X4E  // A6
//#define I2C_ADDR_TC74  0X4F  // A7

uint8_t TC74_readTemp(void)

//    I2C3_MESSAGE_FAIL,
//    I2C3_MESSAGE_PENDING,
//    I2C3_MESSAGE_COMPLETE,
//    I2C3_STUCK_START,
//    I2C3_MESSAGE_ADDRESS_NO_ACK,
//    I2C3_DATA_NO_ACK,
//    I2C3_LOST_STATE

{
    uint8_t temp;
    uint8_t TC74_cmd = 0; // read temperature. 1 = standby
    I2C3_MESSAGE_STATUS status;
    uint8_t len = 1;
    I2C3_MasterWrite( &TC74_cmd, len, I2C_ADDR_TC74, &status);
    while (status == I2C3_MESSAGE_PENDING);
//    return (status == I2C3_MESSAGE_COMPLETE) ? 60 : 10;

    I2C3_MasterRead( &temp, len, I2C_ADDR_TC74, &status);
    while (status == I2C3_MESSAGE_PENDING);
//    return (status == I2C3_MESSAGE_COMPLETE) ? 60 : 10;
        
    return temp;
}

int main(void)
{
    
    uint8_t temp = 0;
    
    // initialize the device
    SYSTEM_Initialize();
    
    // FOR I2C TC74
    INTERRUPT_GlobalEnable();
    // INTERRUPT_PeripheralInterruptEnable();
    
    
    uint32_t i = 0;
    RE8_LED1_Toggle();
    while (1)
    {
        
        for (i=0; i<1000000; i++);
        RG13_LED2_Toggle();
        
        temp = TC74_readTemp();
        
//        if ( (temp >= 19) && (temp <= 20))
        if ( (temp > 15) && (temp < 23))
        {
            RE8_LED1_SetHigh();
        }
        else
        {
            RE8_LED1_SetLow();
        }
        
// Trial 2    
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

// Trial 1        
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
/**
 End of File
*/

