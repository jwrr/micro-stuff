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

#define MENU_SIZE 5
#define MENU_B2B_TIME  200000

enum button_t {NONE=0, NEXT=1, PREV=2, SEL=4, TRIG=8};

static uint8_t updateMenu(void);
static void xmitStim(uint8_t sel);
static void dbg_button_led(void);

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
    uint8_t  sel = 0;
    
    /* Call the System Initialize routine*/
    SYS_Initialize ( );
    
    /* To determine how the LED and Buttons are mapped to the actual board
     * features, please see io_mapping.h. */
    LED_Enable ( LED_BLINK_ALIVE );
    LED_Enable ( LED_DBG_DOWN );
    LED_Enable ( LED_DBG_TRIG );
    LED_Enable ( LED_DBG_SEL );
    LED_Enable ( LED_DBG_PREV );

    BUTTON_Enable ( BTN_NEXT );
    BUTTON_Enable ( BTN_TRIG );
    BUTTON_Enable ( BTN_SEL );
    BUTTON_Enable ( BTN_PREV );
    
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
        
        sel = updateMenu();
        xmitStim(sel);
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



static inline uint8_t getButton(void)
{
    uint8_t button = 0; 
    button =    BUTTON_IsPressed(BTN_NEXT) ? 1 :
                BUTTON_IsPressed(BTN_PREV) ? 2 :
                BUTTON_IsPressed(BTN_SEL)  ? 3 :
                BUTTON_IsPressed(BTN_TRIG) ? 4 : 0;
    return button;
}

static void updateDisplay(uint8_t sel)
{
    dbg_button_led();
    printf("\f");
    printf("%2.1fV ",(double)16.7);
    if (sel!=4 && getButton()==TRIG)
    {
        printf("ACTIVE ");
    }
    else
    {
        printf("STANDBY");
    }
    printf(" %d\r\n", sel);
    printf("IR/UV HF/R/MW\r\n");
}

static uint8_t updateMenu(void){
    static uint8_t sel = 0;
    uint8_t button = getButton();
    bool selectionDone = false;
    updateDisplay(sel);
    while(!selectionDone)
    {
        // Wait until next or prev button is pressed
        while (button == NONE)
        {
            button = getButton();
        }

        // Process selection
        switch (button) {
        case NEXT :
            sel = (sel==MENU_SIZE) ? 0 : sel+1;
            break;
        case PREV :
            sel = (sel==0) ? MENU_SIZE : sel-1;
            break;
        default :
            break;
        }
        updateDisplay(sel);
        
        // Wait until next or prev button is released
        uint32_t cnt = 0;
        while ((button == NEXT) || (button == PREV))
        {
            cnt++;
            if (cnt >= MENU_B2B_TIME)
            {
                break;
            }
            button = getButton();
        }
        selectionDone = (button == LED_DBG_TRIG) && sel!=0;
    }
    return sel;
} // updateMenu


static void xmitStim(uint8_t sel)
{
    updateDisplay(sel);
}

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
        LED_On( LED_DBG_DOWN );
    }
    else
    {
        LED_Off( LED_DBG_DOWN );
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
