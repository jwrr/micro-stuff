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

#include "bsp/buttons.h"
#include "bsp/leds.h"

#define LED_BLINK_ALIVE LED_D3
#define LED_DBG_NEXT LED_D9
#define LED_DBG_PREV LED_D8
#define LED_DBG_SEL LED_D7
#define LED_DBG_TRIG LED_D6

#define BTN_PREV BUTTON_S3
#define BTN_TRIG BUTTON_S5
#define BTN_NEXT BUTTON_S4
#define BTN_SEL BUTTON_S6