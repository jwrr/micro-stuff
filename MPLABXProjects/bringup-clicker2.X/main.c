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

#define CLICKER2

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/usb/usb.h"
#include "mcc_generated_files/interrupt_manager.h"
#include "mcc_generated_files/i2c3.h"
#include "mcc_generated_files/spi2.h"
#include "mcc_generated_files/tmr3.h"
#include "tc74_wrapper.h"
#include "main.h"
#include "gpio_wrapper.h"
#include "usb_wrapper.h"
#include "disp_wrapper.h"
#include "font_wrapper.h"
#include "flash_wrapper.h"
#include "dac_wrapper.h"
#include "adc_wrapper.h"
#include "trigger_wrapper.h"
#include "helper_wrapper.h"
#include "timer_wrapper.h"

#define LINELEN 255
char G_rxLine[LINELEN-10];
char G_txLine[LINELEN];


// ==========================================================================
// ==========================================================================
// ==========================================================================


char MAIN_cmd[USB_LINELEN] = "";

int main(void)
{
    SYSTEM_Initialize(); // Generated by MCC
    
    bool leftButton = true;
    bool rightButton = true;
    bool centerButton = true;
    uint8_t fallingEdge = 0;
//    uint8_t bothEdges   = 2;
//    uint8_t risingEdge  = 1;

    int8_t temperature = 0;
    int8_t temperaturePrev = 25;
    bool tempMonitor = false;
    bool tempStart  = false;
    bool tempDone   = false;

    int16_t battVoltage = 0;
    int16_t battVoltagePrev = 10;
    bool battMonitor = false;
    bool adcStart  = false;
    bool adcDone   = false;
    
    bool displayInhibit = false;
    uint8_t tableIndex = 0;
    uint8_t sampleIndex = 0;
    
//    USB_PrintLine("HELLO. Start typing");
//    USB_PrintPrompt();
    uint32_t cnt = 0;

    bool loadInProgress = false;
    
    // FLASH_test();
 
    TMR3_SetInterruptHandler(&TMR3_callBack);
    TMR3_Start();
    while (1)
    {
        cnt = (cnt + 1) % 3000;
        // called from interrupt HandleTrigger();
        
        if (GPIO_edgeDetect(GPIO_LEFT_BUTTON, &leftButton, fallingEdge))
        {
            USB_printLinePrompt("Left");
            DISP_handleLeftButton();
            DISP_enableDisplayThisCycle();
            adcStart = true; // FIXME for debug only
        }

        if (GPIO_edgeDetect(GPIO_RIGHT_BUTTON, &rightButton, fallingEdge))
        {
            USB_printLinePrompt("Right");
            DISP_handleRightButton();
            DISP_enableDisplayThisCycle();
        }

        if (GPIO_edgeDetect(GPIO_CENTER_BUTTON, &centerButton, fallingEdge))
        {
            USB_printLinePrompt("Center");
            DISP_handleCenterButton();
            DISP_enableDisplayThisCycle();
        }

        bool eoln = USB_readLine(G_rxLine, (uint16_t)sizeof(G_rxLine), USB_getEchoChar());
        if (eoln) {
            DISP_enableDisplayThisCycle();
            if (G_rxLine[0] != '\0')
            {
                strncpy(MAIN_cmd, G_rxLine, sizeof(MAIN_cmd)-1);
                MAIN_cmd[sizeof(MAIN_cmd)-1] = '\0';
            }
            // Process command line
            if (USB_getEchoCommand() == true)
            {
                USB_printEOL();
                USB_printfLine("cmd = '%s'", MAIN_cmd);
            }
            if (strcmp(MAIN_cmd,"b") == 0)
            {
                FONT_toggleBlackOnWhite();
                USB_printfLine("Toggle white/black letters %d", FONT_getBlackOnWhite());
            }
            else if (strcmp(MAIN_cmd,"a") == 0)
            {
                DISP_handleLeftButton();
                USB_printLine("Left Button pressed");

            }
            else if (strcmp(MAIN_cmd,"s") == 0)
            {
                DISP_handleCenterButton();
                USB_printLine("Center Button pressed");
            }
            else if (strcmp(MAIN_cmd,"d") == 0)
            {
                DISP_handleRightButton();
                USB_printLine("Right Button pressed");
            }
            else if (strcmp(MAIN_cmd,"f") == 0)
            {
                TRIG_setUSBPressed( !TRIG_isUSBPressed() );
                if (TRIG_isUSBPressed())
                {
                    USB_printLine("Trigger pressed");
                }
                else
                {
                    USB_printLine("Trigger released");
                }

                // HandleTrigger();
            }
            else if (strcmp(MAIN_cmd,"e") == 0)
            {
                tableIndex = DISP_getModeIndex();
                const char *m0 = DISP_getModeName(0);
                const char *m1 = DISP_getModeName(1);
                FLASH_erasePage(tableIndex);
                USB_printfLine("Erasing Waveform %d [%s,%s]", tableIndex, m0, m1);
            }
            else if (strcmp(MAIN_cmd,"h") == 0)
            {
                USB_printLines(G_help);
            }
            else if (strcmp(MAIN_cmd,"w") == 0)
            { // write Wave
                FLASH_clearLoadBuffer();
                loadInProgress = true;
                tableIndex = DISP_getModeIndex();
                const char *m0 = DISP_getModeName(0);
                const char *m1 = DISP_getModeName(1);
                
                USB_printfLine("Loading table %d [%s,%s]", tableIndex, m0, m1);
                USB_printLine("Enter one value per line. Enter -1 to end");
                sampleIndex = 0;
            }
            else if (isUint(MAIN_cmd) && loadInProgress)
            {
                uint16_t loadValue = (int16_t)strtol(MAIN_cmd, NULL, 10);
                FLASH_appendLoadBuffer((uint32_t)loadValue);
            }
            else if (strcmp(MAIN_cmd, "-1") == 0)
            {
                loadInProgress = false;
                FLASH_appendLoadBuffer(-1);
                uint8_t pageNumber = DISP_getModeIndex();
                FLASH_writeLoadBuffer(pageNumber);
                USB_printWave();
            }
            else if (strcmp(MAIN_cmd,"m") == 0)
            {
                uint8_t mi = DISP_getModeIndex();
                const char *m0 = DISP_getModeName(0);
                const char *m1 = DISP_getModeName(1);
                USB_printfLine("Mode = %d [%s,%s]", mi, m0, m1);
            }
            else if (strcmp(MAIN_cmd, "r") == 0) // read wave
            {
                USB_printWave();
            }
            else if (strcmp(MAIN_cmd,"status") == 0)
            {
                DISP_printScreen();
            }
            else if (strcmp(MAIN_cmd,"t") == 0)
            {
                TIME_enableTimeMonitor( !TIME_isTimeMonitorEnabled() );
                TIME_clearCount();
            }
            else if (isUint(MAIN_cmd)) // change mode
            {
                uint8_t modeIndex = (int8_t)strtol(MAIN_cmd, NULL, 10);
                uint8_t mode0Size = DISP_getModeSize(0);
                uint8_t mode1Size = DISP_getModeSize(1);
                uint8_t m0 = modeIndex / mode1Size;
                uint8_t m1 = modeIndex % mode1Size;
                if ((m0 < mode0Size) && (m1 < mode1Size))
                {
                    DISP_setMode(0, m0);
                    DISP_setMode(1, m1);
                    DISP_updateMode();
                    const char *m0 = DISP_getModeName(0);
                    const char *m1 = DISP_getModeName(1);
                    USB_printfLine("Changing to %d [%s,%s]", modeIndex, m0, m1);
                }
            }
            else if (stringInArray(MAIN_cmd, DISP_getModeNames(0), 3) >= 0)
            {
                uint8_t modeSel = DISP_getModeSel();
                if (modeSel != 0)
                {
                    DISP_handleCenterButton();
                }
                uint8_t newSel = (uint8_t)stringInArray(MAIN_cmd, DISP_getModeNames(0), 3);
                DISP_setMode(modeSel, newSel);
                DISP_updateMode();
                USB_printfLine("Changing 1st row '%s'",  MAIN_cmd);
            }
            else if (stringInArray(MAIN_cmd, DISP_getModeNames(1), 3) >= 0)
            {
                uint8_t modeSel = DISP_getModeSel();
                if (modeSel != 1)
                {
                    DISP_handleCenterButton();
                }
                uint8_t newSel = (uint8_t)stringInArray(MAIN_cmd, DISP_getModeNames(1), 3);
                DISP_setMode(modeSel, newSel);
                DISP_updateMode();
                USB_printfLine("Changing 2nd row '%s'",  MAIN_cmd);                
            }
            else
            {
                USB_printfLine("Undefined command '%s'",  MAIN_cmd); 
            }
            USB_printPrompt();
            G_rxLine[0] = '\0';
        }

        tempStart = (cnt == 1);
        tempDone = TC74_readTemp(tempStart, &temperature);
        if (tempDone) {
            bool tempChanged = (temperature != temperaturePrev);
            if (tempChanged)
            {
                DISP_enableDisplayThisCycle();
                char *temperatureLine = DISP_getTemperatureLinePtr();
                char *temperatureField = &(temperatureLine[12]);
                sprintf(temperatureField, "%4dC ", temperature);
                bool rising = temperature > temperaturePrev;
                temperaturePrev = temperature;
                if (tempMonitor)
                {
                    USB_printfLinePrompt("Temperature %s to %d", 
                                         rising ? "rising" : "falling",
                                         temperature);
                }
            }
        }

        adcStart = (cnt == 1);
        adcDone = ADC_readVoltage(adcStart, &battVoltage);      
        if (adcDone)
        {
            // USB_PrintLinePrompt("ADC done");
            bool battChanged = (battVoltage != battVoltagePrev);
            if (battChanged)
            {
                uint16_t battVoltageMax = 1023;
                uint16_t battVoltageMin = 0; // 1024 * 14 / 18;
                uint16_t battVoltageDeltaMax = battVoltageMax - battVoltageMin;
                uint16_t battVoltageDeltaActual = 0;
                if (battVoltage > battVoltageMin)
                {
                    battVoltageDeltaActual = battVoltage - battVoltageMin;
                }
                uint16_t percent = 100 * battVoltageDeltaActual / battVoltageDeltaMax; 
                DISP_enableDisplayThisCycle();
                char *batteryLine = DISP_getBatteryLinePtr();
                char *batteryField = &(batteryLine[12]);
                sprintf(batteryField, "%4d%% ", percent);
                bool rising = battVoltage > battVoltagePrev;
                battVoltagePrev = battVoltage;
                if (battMonitor)
                {
                    USB_printfLinePrompt("Battery %s to %d", 
                                         rising ? "rising" : "falling",
                                         battVoltage);
                }
            }
        }

        displayInhibit = TRIG_isSignalOn();
        if (!displayInhibit)
        {
            if (DISP_getStart() && !DISP_isBusy())
            {
                DISP_writeFrame(true);
                DISP_preventDispThisCycle();
            }
            else
            {
                DISP_writeFrame(true);
            }
        }
        else
        {
            GPIO_set(GPIO_DISP_CS, 0);
        }
   
        GPIO_set(LED1, TRIG_isSignalOn());
        GPIO_set(LED2, DISP_getVcom());
        USB_flushPrintBuffer();
    } // while (1)
    return 1;
}


