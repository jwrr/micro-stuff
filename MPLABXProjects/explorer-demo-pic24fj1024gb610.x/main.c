/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "bsp/adc.h"
#include "bsp/lcd.h"
#include "bsp/timer_1ms.h"
#include "bsp/buttons.h"
#include "bsp/leds.h"
#include "bsp/rtcc.h"
 
#include "io_mapping.h"

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables and Functions
// *****************************************************************************
// *****************************************************************************
extern void SYS_Initialize ( void ) ;
static void BlinkAliveEventHandler( void );
static void ScreenUpdateEventHandler( void );

static RTCC_DATETIME time;
static RTCC_DATETIME lastTime = {0};
static volatile bool toggleBlinkAlive = false;
static volatile bool allowScreenUpdate = true;

#define MEMCMP_VALUES_IDENTICAL 0

#define VERSION        "123"
#define MENU_SIZE          5
#define MENU_TIME     200000
#define DEBOUNCE_TIME   2000
#define WAVEFORM_SIZE    512

const char *G_menu[][9] = {
    {"M1",  "M2",  "M3",  NULL,  NULL,  NULL,  NULL,  NULL,  NULL},
    {"T11", "T12", "T13", "T14", "T15", "T16", "T17", "T18", NULL},
    {"T21", "T22", "T23", "T24", NULL,  NULL,  NULL,  NULL,  NULL},
    {"T31", "T32", NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL},
    {NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL}
};

uint8_t G_menuSel = 0;
uint8_t G_mode0 = 0;
uint8_t G_mode1 = 0;

uint16_t G_waveformTable[WAVEFORM_SIZE];

enum button_t {NONE=0, NEXT=1, PREV=2, SEL=4, TRIG=8};


static void dbg_button_led(void)
{
    /* To determine how the LED and Buttons are mapped to the actual board
    * features, please see io_mapping.h. */
    
    if(toggleBlinkAlive == true)
    {
        LED_Toggle( LED_BLINK_ALIVE );
        toggleBlinkAlive = false;
    }
    
    if(BUTTON_IsPressed( BTN_NEXT ) == true)
    {
        LED_On( LED_DBG_NEXT );
    }
    else
    {
        LED_Off( LED_DBG_NEXT );
    }
    
    if(BUTTON_IsPressed( BTN_TRIG ) == true)
    {
        LED_On( LED_DBG_TRIG );
    }
    else
    {
        LED_Off( LED_DBG_TRIG );
    }
        
    if(BUTTON_IsPressed( BTN_SEL ) == true)
    {
        LED_On( LED_DBG_SEL );
    }
    else
    {
        LED_Off( LED_DBG_SEL );
    }
    
    if(BUTTON_IsPressed( BTN_PREV ) == true)
    {
        LED_On( LED_DBG_PREV );
    }
    else
    {
        LED_Off( LED_DBG_PREV );
    } 
} // dbg_button_led

static void spin(uint32_t cnt)
{
    uint32_t i;
    for (i=0; i<cnt; i++);
}

static uint8_t len(const char *arr[])
{
    uint8_t i = 0;
    for (i=0; arr[i]!=NULL; i++);
    return i;
}

static uint8_t debounceButtons(void)
{
    uint8_t button = 0;
    uint32_t cnt = 0;
    while (cnt < DEBOUNCE_TIME)
    {
        cnt++;
        bool button_trig = BUTTON_IsPressed(BTN_TRIG);
        bool button_next = BUTTON_IsPressed(BTN_NEXT);
        bool button_prev = BUTTON_IsPressed(BTN_PREV);
        bool button_sel  = BUTTON_IsPressed(BTN_SEL);
        button =    button_trig ? TRIG :
                    button_sel  ? SEL  :
                    button_next ? NEXT :
                    button_prev ? PREV : NONE;
        if (button == NONE) {
            return NONE;
        }
    }
    return button;
}

static void waitIdle(void)
{
    bool next = false;
    bool prev = false;
    bool sel  = false;
    bool isPressed = true;
    while (isPressed)
    {
        prev = BUTTON_IsPressed(BTN_PREV);
        sel  = BUTTON_IsPressed(BTN_SEL);
        next = BUTTON_IsPressed(BTN_NEXT);
        isPressed = prev | sel | next;
    }
}

static double checkBattery()
{
    uint16_t adcResult = ADC_Read10bit( ADC_CHANNEL_POTENTIOMETER ) + 1;
    double   batteryLevel = (double)adcResult*18.0/1024;
    return batteryLevel;
}

static void updateDisplay(uint8_t fmt, const char *menu[], uint8_t sel, uint8_t cnt)
{
    double   batteryLevel = checkBattery();

    char str[80];
    switch (fmt)
    {
    case 0:
        sprintf(str, "\f%2.2fV %s\r\n", batteryLevel, menu[sel]);
        break;
    case 1:
        sprintf(str, "\f%2.2fV %s %s\r\n", batteryLevel, G_menu[0][G_mode0], menu[sel]);
        break;
    case 2:
        sprintf(str, "\f%2.2fV %s %s\r\n", batteryLevel, G_menu[0][G_mode0], G_menu[G_mode0+1][G_mode1]);
        break;
    default:
        break;
    }

    bool isActive = BUTTON_IsPressed(BTN_TRIG);
    if (isActive) {
        strcat(str, "ACTIVE ");
        int i;
        for (i=0; i<cnt; i++)
        {
            strcat(str, "*");
        }
        strcat(str, "\r\n");
    } else {
        strcat(str, "standby\r\n");
    }
    printf(str);
}

static uint8_t navMenu(const char *menu[], uint8_t sel, uint8_t displayFormat)
{
    uint8_t menuLen = len(menu);
    if (sel > menuLen-1) {
        sel = 0;
    }

    updateDisplay(displayFormat, menu, sel, 0);
    bool done = BUTTON_IsPressed(BTN_TRIG);

    while (!done)
    {
        waitIdle();
        uint8_t button = NONE;
        while (button == NONE)
        {
            spin(MENU_TIME);
            updateDisplay(displayFormat, menu, sel, 0);
            button = debounceButtons();
        }
        dbg_button_led();
        switch (button)
        {
        case NEXT:
            sel = (sel >= menuLen-1) ? 0 : sel + 1;
            break;
        case PREV:
            sel = (sel == 0) ? menuLen - 1 : sel - 1;
            break;
        default:
            break;
        }

        updateDisplay(displayFormat, menu, sel, 0);
        done = (button == SEL) || (button == TRIG);    
    } // while
    return sel;
} // navMenu


static void loadWaveform(uint8_t mode0, uint8_t mode1, uint16_t table[])
{
    static uint8_t mode0_prev = 255;
    static uint8_t mode1_prev = 255;
    
    bool waveformChanged = (mode0 != mode0_prev) || (mode1 != mode1_prev);
    
    if (waveformChanged)
    {
        mode0_prev = mode0;
        mode1_prev = mode1;
        // Copy FLASH to MEM
    }
}

static void xmitWaveform(uint16_t table[])
{
    static uint8_t cnt = 0;
    cnt++;
    cnt = cnt & 0x07;
    spin(200000);
    uint8_t displayFormat = 2;
    updateDisplay(displayFormat, NULL, 0, cnt);
}



// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
int main ( void )
{
    uint16_t adcResult;
    double   adcResultDouble;
    uint16_t lastAdcResult = 0xFFFF;
    
    /* Call the System Initialize routine*/
    SYS_Initialize ( );
    
    /* To determine how the LED and Buttons are mapped to the actual board
     * features, please see io_mapping.h. */
    LED_Enable ( LED_BLINK_ALIVE );
    LED_Enable ( LED_DBG_NEXT );
    LED_Enable ( LED_DBG_TRIG );
    LED_Enable ( LED_DBG_SEL );
    LED_Enable ( LED_DBG_PREV );

    BUTTON_Enable ( BTN_TRIG );
    BUTTON_Enable ( BTN_NEXT );
    BUTTON_Enable ( BTN_PREV );
    BUTTON_Enable ( BTN_SEL );
    
    /* Get a timer event once every 100ms for the blink alive. */
    TIMER_SetConfiguration ( TIMER_CONFIGURATION_1MS );
    TIMER_RequestTick( &BlinkAliveEventHandler, 500 );
    TIMER_RequestTick( &ScreenUpdateEventHandler, 170 );
    
    /* The TIMER_1MS configuration should come before the RTCC initialization as
     * there are some processor modules that require the TIMER_1MS module to be
     * configured before the RTCC module, as the RTCC module is emulated using
     * the TIMER_1MS module. */
    time.bcdFormat = false;
    lastTime.bcdFormat = false;
    RTCC_BuildTimeGet( &time );
    RTCC_Initialize( &time );
    memset(&lastTime,0,sizeof(lastTime)); 

    ADC_SetConfiguration ( ADC_CONFIGURATION_DEFAULT );
    ADC_ChannelEnable ( ADC_CHANNEL_POTENTIOMETER );
    
    /* Clear the screen */
    printf( "\f" );
    while ( 1 )
    {
        if (BUTTON_IsPressed(BTN_TRIG))
        {
            loadWaveform(G_mode0, G_mode1, G_waveformTable);
            xmitWaveform(G_waveformTable);
        }
        else
        {
            G_mode1 = navMenu(G_menu[G_mode0+1], G_mode1, 1);
            G_mode0 = navMenu(G_menu[0], G_mode0, 0);
        }
    }
    
        
//        adcResult = ADC_Read10bit( ADC_CHANNEL_POTENTIOMETER );
//        adcResultDouble = (double)adcResult*3.3/1024;
//
//        RTCC_TimeGet( &time );
//        
//        //Only print if the ADC value or time has changed since the last time 
//        // around the loop and we haven't updated recently too recently.
//        if(allowScreenUpdate == true)
//        {
//            if( (adcResult != lastAdcResult) ||
//                (memcmp(&time, &lastTime, sizeof(time)) != MEMCMP_VALUES_IDENTICAL) )
//            {   
//                //Either ADC or time has changed, and the screen update refresh
//                // limit has expired, update the screen.
//                allowScreenUpdate = false;
//                
//                printf( "Time %02d:%02d:%02d %1d \r\nPot=%4d (%1.2fV)\r\n", 
//                        time.hour, 
//                        time.minute, 
//                        time.second,
//                        sel,
//                        adcResult,
//                        adcResultDouble
//                      );
//
//                lastAdcResult = adcResult;
//                memcpy(&lastTime, &time, sizeof(time));
//            }
//        }
//        dbg_button_led();
//
//    }
}

static void BlinkAliveEventHandler(void)
{    
    toggleBlinkAlive = true;
}

static void ScreenUpdateEventHandler(void)
{
    allowScreenUpdate = true;
}
