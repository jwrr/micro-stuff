/**
  PIN MANAGER Generated Driver File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the generated manager file for the PIC24 / dsPIC33 / PIC32MM MCUs device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description:
    This source file provides implementations for PIN MANAGER.
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

#ifndef _PIN_MANAGER_H
#define _PIN_MANAGER_H
/**
    Section: Includes
*/
#include <xc.h>

/**
    Section: Device Pin Macros
*/
/**
  @Summary
    Sets the GPIO pin, RD2, high using LATD2.

  @Description
    Sets the GPIO pin, RD2, high using LATD2.

  @Preconditions
    The RD2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD2 high (1)
    SDO2_SetHigh();
    </code>

*/
#define SDO2_SetHigh()          (_LATD2 = 1)
/**
  @Summary
    Sets the GPIO pin, RD2, low using LATD2.

  @Description
    Sets the GPIO pin, RD2, low using LATD2.

  @Preconditions
    The RD2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD2 low (0)
    SDO2_SetLow();
    </code>

*/
#define SDO2_SetLow()           (_LATD2 = 0)
/**
  @Summary
    Toggles the GPIO pin, RD2, using LATD2.

  @Description
    Toggles the GPIO pin, RD2, using LATD2.

  @Preconditions
    The RD2 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RD2
    SDO2_Toggle();
    </code>

*/
#define SDO2_Toggle()           (_LATD2 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RD2.

  @Description
    Reads the value of the GPIO pin, RD2.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RD2
    postValue = SDO2_GetValue();
    </code>

*/
#define SDO2_GetValue()         _RD2
/**
  @Summary
    Configures the GPIO pin, RD2, as an input.

  @Description
    Configures the GPIO pin, RD2, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD2 as an input
    SDO2_SetDigitalInput();
    </code>

*/
#define SDO2_SetDigitalInput()  (_TRISD2 = 1)
/**
  @Summary
    Configures the GPIO pin, RD2, as an output.

  @Description
    Configures the GPIO pin, RD2, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD2 as an output
    SDO2_SetDigitalOutput();
    </code>

*/
#define SDO2_SetDigitalOutput() (_TRISD2 = 0)
/**
  @Summary
    Sets the GPIO pin, RD3, high using LATD3.

  @Description
    Sets the GPIO pin, RD3, high using LATD3.

  @Preconditions
    The RD3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD3 high (1)
    SCK2OUT_SetHigh();
    </code>

*/
#define SCK2OUT_SetHigh()          (_LATD3 = 1)
/**
  @Summary
    Sets the GPIO pin, RD3, low using LATD3.

  @Description
    Sets the GPIO pin, RD3, low using LATD3.

  @Preconditions
    The RD3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD3 low (0)
    SCK2OUT_SetLow();
    </code>

*/
#define SCK2OUT_SetLow()           (_LATD3 = 0)
/**
  @Summary
    Toggles the GPIO pin, RD3, using LATD3.

  @Description
    Toggles the GPIO pin, RD3, using LATD3.

  @Preconditions
    The RD3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RD3
    SCK2OUT_Toggle();
    </code>

*/
#define SCK2OUT_Toggle()           (_LATD3 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RD3.

  @Description
    Reads the value of the GPIO pin, RD3.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RD3
    postValue = SCK2OUT_GetValue();
    </code>

*/
#define SCK2OUT_GetValue()         _RD3
/**
  @Summary
    Configures the GPIO pin, RD3, as an input.

  @Description
    Configures the GPIO pin, RD3, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD3 as an input
    SCK2OUT_SetDigitalInput();
    </code>

*/
#define SCK2OUT_SetDigitalInput()  (_TRISD3 = 1)
/**
  @Summary
    Configures the GPIO pin, RD3, as an output.

  @Description
    Configures the GPIO pin, RD3, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD3 as an output
    SCK2OUT_SetDigitalOutput();
    </code>

*/
#define SCK2OUT_SetDigitalOutput() (_TRISD3 = 0)
/**
  @Summary
    Sets the GPIO pin, RE4, high using LATE4.

  @Description
    Sets the GPIO pin, RE4, high using LATE4.

  @Preconditions
    The RE4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE4 high (1)
    IO_RE4_LED1_SetHigh();
    </code>

*/
#define IO_RE4_LED1_SetHigh()          (_LATE4 = 1)
/**
  @Summary
    Sets the GPIO pin, RE4, low using LATE4.

  @Description
    Sets the GPIO pin, RE4, low using LATE4.

  @Preconditions
    The RE4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE4 low (0)
    IO_RE4_LED1_SetLow();
    </code>

*/
#define IO_RE4_LED1_SetLow()           (_LATE4 = 0)
/**
  @Summary
    Toggles the GPIO pin, RE4, using LATE4.

  @Description
    Toggles the GPIO pin, RE4, using LATE4.

  @Preconditions
    The RE4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RE4
    IO_RE4_LED1_Toggle();
    </code>

*/
#define IO_RE4_LED1_Toggle()           (_LATE4 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RE4.

  @Description
    Reads the value of the GPIO pin, RE4.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RE4
    postValue = IO_RE4_LED1_GetValue();
    </code>

*/
#define IO_RE4_LED1_GetValue()         _RE4
/**
  @Summary
    Configures the GPIO pin, RE4, as an input.

  @Description
    Configures the GPIO pin, RE4, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE4 as an input
    IO_RE4_LED1_SetDigitalInput();
    </code>

*/
#define IO_RE4_LED1_SetDigitalInput()  (_TRISE4 = 1)
/**
  @Summary
    Configures the GPIO pin, RE4, as an output.

  @Description
    Configures the GPIO pin, RE4, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE4 as an output
    IO_RE4_LED1_SetDigitalOutput();
    </code>

*/
#define IO_RE4_LED1_SetDigitalOutput() (_TRISE4 = 0)
/**
  @Summary
    Sets the GPIO pin, RE8, high using LATE8.

  @Description
    Sets the GPIO pin, RE8, high using LATE8.

  @Preconditions
    The RE8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE8 high (1)
    IO_RE8_DACCS_SetHigh();
    </code>

*/
#define IO_RE8_DACCS_SetHigh()          (_LATE8 = 1)
/**
  @Summary
    Sets the GPIO pin, RE8, low using LATE8.

  @Description
    Sets the GPIO pin, RE8, low using LATE8.

  @Preconditions
    The RE8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RE8 low (0)
    IO_RE8_DACCS_SetLow();
    </code>

*/
#define IO_RE8_DACCS_SetLow()           (_LATE8 = 0)
/**
  @Summary
    Toggles the GPIO pin, RE8, using LATE8.

  @Description
    Toggles the GPIO pin, RE8, using LATE8.

  @Preconditions
    The RE8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RE8
    IO_RE8_DACCS_Toggle();
    </code>

*/
#define IO_RE8_DACCS_Toggle()           (_LATE8 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RE8.

  @Description
    Reads the value of the GPIO pin, RE8.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RE8
    postValue = IO_RE8_DACCS_GetValue();
    </code>

*/
#define IO_RE8_DACCS_GetValue()         _RE8
/**
  @Summary
    Configures the GPIO pin, RE8, as an input.

  @Description
    Configures the GPIO pin, RE8, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE8 as an input
    IO_RE8_DACCS_SetDigitalInput();
    </code>

*/
#define IO_RE8_DACCS_SetDigitalInput()  (_TRISE8 = 1)
/**
  @Summary
    Configures the GPIO pin, RE8, as an output.

  @Description
    Configures the GPIO pin, RE8, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RE8 as an output
    IO_RE8_DACCS_SetDigitalOutput();
    </code>

*/
#define IO_RE8_DACCS_SetDigitalOutput() (_TRISE8 = 0)
/**
  @Summary
    Sets the GPIO pin, RG13, high using LATG13.

  @Description
    Sets the GPIO pin, RG13, high using LATG13.

  @Preconditions
    The RG13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RG13 high (1)
    IO_RG13_LED2_SetHigh();
    </code>

*/
#define IO_RG13_LED2_SetHigh()          (_LATG13 = 1)
/**
  @Summary
    Sets the GPIO pin, RG13, low using LATG13.

  @Description
    Sets the GPIO pin, RG13, low using LATG13.

  @Preconditions
    The RG13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RG13 low (0)
    IO_RG13_LED2_SetLow();
    </code>

*/
#define IO_RG13_LED2_SetLow()           (_LATG13 = 0)
/**
  @Summary
    Toggles the GPIO pin, RG13, using LATG13.

  @Description
    Toggles the GPIO pin, RG13, using LATG13.

  @Preconditions
    The RG13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RG13
    IO_RG13_LED2_Toggle();
    </code>

*/
#define IO_RG13_LED2_Toggle()           (_LATG13 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RG13.

  @Description
    Reads the value of the GPIO pin, RG13.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RG13
    postValue = IO_RG13_LED2_GetValue();
    </code>

*/
#define IO_RG13_LED2_GetValue()         _RG13
/**
  @Summary
    Configures the GPIO pin, RG13, as an input.

  @Description
    Configures the GPIO pin, RG13, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RG13 as an input
    IO_RG13_LED2_SetDigitalInput();
    </code>

*/
#define IO_RG13_LED2_SetDigitalInput()  (_TRISG13 = 1)
/**
  @Summary
    Configures the GPIO pin, RG13, as an output.

  @Description
    Configures the GPIO pin, RG13, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RG13 as an output
    IO_RG13_LED2_SetDigitalOutput();
    </code>

*/
#define IO_RG13_LED2_SetDigitalOutput() (_TRISG13 = 0)

/**
    Section: Function Prototypes
*/
/**
  @Summary
    Configures the pin settings of the PIC24FJ1024GB610
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description
    This is the generated manager file for the PIC24 / dsPIC33 / PIC32MM MCUs device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void SYSTEM_Initialize(void)
    {
        // Other initializers are called from this function
        PIN_MANAGER_Initialize();
    }
    </code>

*/
void PIN_MANAGER_Initialize (void);



#endif
