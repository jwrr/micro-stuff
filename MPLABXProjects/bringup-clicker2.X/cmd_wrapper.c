#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "usb_wrapper.h"
#include "disp_wrapper.h"
#include "flash_wrapper.h"
#include "timer_wrapper.h"
#include "font_wrapper.h"
#include "trigger_wrapper.h"
#include "help_wrapper.h"
#include "misc_wrapper.h"

static bool CMD_loadInProgress = false;

void CMD_interpreter(char *rxLine)
{
    char cmdStr[USB_LINELEN] = "";
    DISP_enableDisplayThisCycle();
    if (rxLine[0] != '\0')
    {
        strncpy(cmdStr, rxLine, sizeof(cmdStr)-1);
        cmdStr[sizeof(cmdStr)-1] = '\0';
    }
    // Process command line
    if (USB_getEchoCommand() == true)
    {
        USB_printEOL();
        USB_printfLine("cmd = '%s'", cmdStr);
    }
    if (strcmp(cmdStr,"b") == 0)
    {
        FONT_toggleBlackOnWhite();
        USB_printfLine("Toggle white/black letters %d", FONT_getBlackOnWhite());
    }
    else if (strcmp(cmdStr,"a") == 0)
    {
        DISP_handleLeftButton();
        USB_printLine("Left Button pressed");

    }
    else if (strcmp(cmdStr,"s") == 0)
    {
        DISP_handleCenterButton();
        USB_printLine("Center Button pressed");
    }
    else if (strcmp(cmdStr,"d") == 0)
    {
        DISP_handleRightButton();
        USB_printLine("Right Button pressed");
    }
    else if (strcmp(cmdStr,"f") == 0)
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
    else if (strcmp(cmdStr,"e") == 0)
    {
        uint8_t tableIndex = DISP_getModeIndex();
        const char *m0 = DISP_getModeName(0);
        const char *m1 = DISP_getModeName(1);
        FLASH_erasePage(tableIndex);
        USB_printfLine("Erasing Waveform %d [%s,%s]", tableIndex, m0, m1);
    }
    else if (strcmp(cmdStr,"h") == 0)
    {
        USB_printLine(HELP_getHelpMenu());
    }
    else if (strcmp(cmdStr,"w") == 0)
    { // write Wave
        FLASH_clearLoadBuffer();
        CMD_loadInProgress = true;
        uint8_t tableIndex = DISP_getModeIndex();
        const char *m0 = DISP_getModeName(0);
        const char *m1 = DISP_getModeName(1);

        USB_printfLine("Loading table %d [%s,%s]", tableIndex, m0, m1);
        USB_printLine("Enter one value per line. Enter -1 to end");
    }
    else if (isUint(cmdStr) && CMD_loadInProgress)
    {
        uint16_t loadValue = (int16_t)strtol(cmdStr, NULL, 10);
        FLASH_appendLoadBuffer((uint32_t)loadValue);
    }
    else if (strcmp(cmdStr, "-1") == 0)
    {
        CMD_loadInProgress = false;
        FLASH_appendLoadBuffer(-1);
        uint8_t pageNumber = DISP_getModeIndex();
        FLASH_writeLoadBuffer(pageNumber);
        USB_printWave();
    }
    else if (strcmp(cmdStr,"m") == 0)
    {
        uint8_t mi = DISP_getModeIndex();
        const char *m0 = DISP_getModeName(0);
        const char *m1 = DISP_getModeName(1);
        USB_printfLine("Mode = %d [%s,%s]", mi, m0, m1);
    }
    else if (strcmp(cmdStr, "r") == 0) // read wave
    {
        USB_printWave();
    }
    else if (strcmp(cmdStr,"status") == 0)
    {
        DISP_printScreen();
    }
    else if (strcmp(cmdStr,"t") == 0)
    {
        TIME_enableTimeMonitor( !TIME_isTimeMonitorEnabled() );
        TIME_clearCount();
    }
    else if (isUint(cmdStr)) // change mode
    {
        uint8_t modeIndex = (int8_t)strtol(cmdStr, NULL, 10);
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
    else if (stringInArray(cmdStr, DISP_getModeNames(0), 3) >= 0)
    {
        uint8_t modeSel = DISP_getModeSel();
        if (modeSel != 0)
        {
            DISP_handleCenterButton();
        }
        uint8_t newSel = (uint8_t)stringInArray(cmdStr, DISP_getModeNames(0), 3);
        DISP_setMode(modeSel, newSel);
        DISP_updateMode();
        USB_printfLine("Changing 1st row '%s'",  cmdStr);
    }
    else if (stringInArray(cmdStr, DISP_getModeNames(1), 3) >= 0)
    {
        uint8_t modeSel = DISP_getModeSel();
        if (modeSel != 1)
        {
            DISP_handleCenterButton();
        }
        uint8_t newSel = (uint8_t)stringInArray(cmdStr, DISP_getModeNames(1), 3);
        DISP_setMode(modeSel, newSel);
        DISP_updateMode();
        USB_printfLine("Changing 2nd row '%s'",  cmdStr);                
    }
    else
    {
        USB_printfLine("Undefined command '%s'",  cmdStr); 
    }
}

#define CMD_rxLineLen  256
static char CMD_rxLine[CMD_rxLineLen];
void CMD_handleUSB()
{
    bool eoln = USB_readLine(CMD_rxLine, CMD_rxLineLen, USB_getEchoChar());
    if (eoln) {
        CMD_interpreter(CMD_rxLine);
        USB_printPrompt();
        CMD_rxLine[0] = '\0';
    }
}
