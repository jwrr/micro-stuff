

#include <stdint.h>
#include <stdbool.h>
#include "gpio_wrapper.h"
#include "disp_wrapper.h"

static uint8_t  G_triggerCountDown = 0;
static uint8_t  G_triggerCountDownMax = 5;

static bool G_triggerPressedPrev   = false;
static bool G_triggerFiring        = false;
static bool USB_triggerPressed     = false;
static bool USB_triggerPressedPrev = false;

bool TRIG_isSignalOn(void)
{
    return G_triggerFiring;
}

bool TRIG_isUSBPressed(void)
{
    return USB_triggerPressed;
}
void TRIG_setUSBPressed(bool newVal)
{
    USB_triggerPressed = newVal;
}

void TRIG_handleTrigger(void)
{
    bool triggerVal      = GPIO_get(GPIO_TRIGGER_BUTTON);
    bool triggerPressed  = !triggerVal;
    bool triggerEdge     = !G_triggerPressedPrev && triggerPressed;
    G_triggerPressedPrev = triggerPressed;
    bool USB_triggerEdge = !USB_triggerPressedPrev && USB_triggerPressed;
    USB_triggerPressedPrev = USB_triggerPressed;

    if (G_triggerCountDown == 0){
        if (triggerEdge || USB_triggerEdge)
        {
            G_triggerFiring = false;
            G_triggerCountDown = G_triggerCountDownMax + 1;
            DISP_center(DISP_getScreenWidthInChar(), DISP_getSignalLinePtr(), ">>> SIGNAL ON <<<");
            DISP_enableDisplayThisCycle();
        }
        else if (triggerPressed || USB_triggerPressed)
        {
            DISP_center(DISP_getScreenWidthInChar(), DISP_getSignalLinePtr(), "RELEASE / RE-PRESS");
            DISP_enableDisplayThisCycle();
        }
        else
        {
            DISP_center(DISP_getScreenWidthInChar(), DISP_getSignalLinePtr(), "SIGNAL OFF");
            DISP_enableDisplayThisCycle();
        }
    }
    else if ((triggerPressed || USB_triggerPressed) && (G_triggerCountDown > 1))
    {
        G_triggerCountDown--;
        G_triggerFiring = true;
        DISP_center(DISP_getScreenWidthInChar(), DISP_getSignalLinePtr(), ">>> SIGNAL ON <<<");
        DISP_preventDispThisCycle();
    }
    else
    {
        G_triggerFiring = false;
        G_triggerCountDown = 0;
        DISP_center(DISP_getScreenWidthInChar(), DISP_getSignalLinePtr(), "SIGNAL OFF");
        DISP_enableDisplayThisCycle();
    }
}
