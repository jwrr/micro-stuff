
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "gpio_wrapper.h"
#include "disp_wrapper.h"
#include "font_wrapper.h"
#include "usb_wrapper.h"
#include "mcc_generated_files/spi2.h"


const char *G_modeNames0[] = {"AAAA", "BBBB", "CCCC", ""};
const char *G_modeNames1[] = {"DDDD", "EEEE", "FFFF", ""};

uint8_t  G_mode[2]      = {0, 0};
uint8_t  G_modeSize[2]  = {3, 3};
uint8_t  G_modeSel          = 0;


char G_txtScreen[][20] = {
    " BATTERY:    100% ", // 0
    " TEMP:        25C ", // 1
    " SELF TEST:  PASS ", // 2
    "                  ", // 3
    "    SIGNAL OFF    ", // 4
    "                  ", // 5
    "<      AAAA      >", // 6
    "                  ", // 7
    "       DDDD       ", // 8
    "                  ", // 9
    "  P/N: PN123-01   ", // 10
    "  F/W: FW123-01   ", // 11
    "                  ", // 12 (off screen)
    ""
};

uint8_t DISP_pixLine[G_txtCharPerLine];

const uint8_t G_screenLineBatt  = 0;
const uint8_t G_screenLineTemp  = 1;
const uint8_t G_screenLineSignal  = 4;
const uint8_t G_screenLineMode0 = 6;
const uint8_t G_screenLineMode1 = 8;
const uint8_t G_screenLineCmd   = 12;


// ==========================================================
// DISP
// SHARP 144x168 DISPLAY (LS013B7DH05)

uint8_t DISP_cmd  = 0x80;
bool    DISP_vcom = true;
uint8_t DISP_ScreenWidthInPixels = 144;
uint8_t DISP_screenWidthInBytes = 18;
uint8_t DISP_screenWidthInChar  = 18;
uint8_t DISP_timeout = 255;
uint8_t DISP_pixLineIndex = 0;
uint8_t FONT_pixLineIndex = 0;
uint8_t DISP_frameCount = 0;
bool    DISP_busy = false;

bool DISP_isBusy(void)
{
    return DISP_busy;
}

uint8_t DISP_sendByteSPI(uint8_t val)
{
    uint8_t cnt;
    for (cnt = 0; cnt < DISP_timeout; cnt++)
    {
        if (SPI2STATLbits.SPITBF == false) break;
    }
    if (SPI2STATLbits.SPITBF == true) return 0;
    SPI2BUFL = val;
    
     for (cnt = 0; cnt < DISP_timeout; cnt++)
    {
        if (SPI2STATLbits.SPIRBE == false) break;
    }   
    
    if (SPI2STATLbits.SPIRBE == true) return 0;
    uint8_t rdata = SPI2BUFL; // sets SPIRBE
    return rdata;
}
 
void DISP_drawPixLine(uint8_t addr, uint8_t pixels[])
{
    uint8_t i = 0;
    DISP_sendByteSPI(addr);
    for (i = 0; i < DISP_screenWidthInBytes; i++)
    {
        DISP_sendByteSPI(pixels[i]);
    }
    DISP_sendByteSPI(0x00);
}


uint8_t DISP_reverseBits(uint8_t val)
{
    uint8_t reverseVal = 0;
    uint8_t i;
    uint8_t mask = 1;
    for (i = 0; i < 8; i++)
    {
        if (val & mask)
        {
            reverseVal += (1 << (7-i));
        }
        mask <<= 1;
    }
    return reverseVal;
}

// SHARP 144x168 DISPLAY (LS013B7DH05)

void DISP_writeFrame(bool start)
{
    if (start && (DISP_pixLineIndex == 0))
    {
        DISP_busy = true;
        DISP_pixLineIndex = 1;
        FONT_pixLineIndex = 0;
        GPIO_set(GPIO_DISP_CS, 1);
        DISP_vcom = !DISP_vcom;
        DISP_cmd = DISP_vcom ? 0xc0 : 0x80;
        DISP_sendByteSPI(DISP_cmd);
    }
    
    if (DISP_pixLineIndex > 0 && DISP_pixLineIndex <= 168)
    {
//            FONT_isAllSpaces
        FONT_getPixLine(FONT_pixLineIndex, DISP_pixLine);
        if (FONT_isStartingBlankLine(FONT_pixLineIndex))
        {
            FONT_pixLineIndex += 11; // Reduce height of blank lines
        }
        FONT_pixLineIndex++;
        uint8_t reverseAddr = DISP_reverseBits(DISP_pixLineIndex);
        DISP_drawPixLine(reverseAddr, DISP_pixLine);
        DISP_pixLineIndex++;
    }
    else if (DISP_pixLineIndex > 168)
    {
        DISP_busy = false;
        DISP_sendByteSPI(0x00);
        GPIO_set(GPIO_DISP_CS, 0);
        DISP_pixLineIndex = 0;
        FONT_pixLineIndex = 0;
        DISP_frameCount++;
    }
}

bool DISP_getVcom(void)
{
    return DISP_vcom;
}

void DISP_setVcom(bool newVcom)
{
    DISP_vcom = newVcom;
}

void DISP_append8BitsToPixLine(uint8_t pixVal, uint8_t *pixLine, uint8_t index)
{
    if (index < G_txtCharPerLine)
    {
        pixLine[index] = pixVal;
        USB_printGraphicsLinePixels(DISP_getShowGraphics(), pixVal);
    }
}

// ================================================================
// ================================================================



void DISP_printScreen(void)
{
    USB_printLines(G_txtScreen);
}

char *DISP_getLinePtr(int txtLineNumber)
{
    char *txtLine = G_txtScreen[txtLineNumber];
    return txtLine;
}

uint8_t DISP_getScreenWidthInChar(void)
{
    return DISP_screenWidthInChar;
}

void DISP_setScreenWidthInChar(uint8_t newWidth)
{
    DISP_screenWidthInChar = newWidth;
}

bool G_showGraphics = false;
bool DISP_getShowGraphics(void)
{
    return G_showGraphics;
}

void DISP_setShowGraphics(bool newVal)
{
    G_showGraphics = newVal;
}



uint8_t DISP_getModeIndex(void)
{
    uint8_t tableIndex = G_mode[0] * G_modeSize[1] + G_mode[1];
    return tableIndex;
}

uint8_t DISP_getModeSize(uint8_t mode)
{
    if (mode >= 2) return 0;
    return G_modeSize[mode];
}


const char **DISP_getModeNames(uint8_t m)
{
    if (m >= 2) return NULL;
    if (m == 0) return G_modeNames0;
    if (m == 1) return G_modeNames1;
    return NULL;  
}

const char *DISP_getModeName(uint8_t m)
{
    if (m >= 2) return NULL;
    if (m == 0) return G_modeNames0[G_mode[m]];
    if (m == 1) return G_modeNames1[G_mode[m]];
    return NULL;
}

uint8_t DISP_getModeSel(void)
{
    return G_modeSel;
}

void DISP_setModeSel(uint8_t newVal)
{
    G_modeSel = newVal;
}


void DISP_setMode(uint8_t mode, uint8_t val)
{
    if (mode >= 2) return;
    G_mode[mode] = val;
}

char *DISP_center(uint8_t width, char centered[], const char uncentered[])
{
    uint8_t uncenteredLen = strlen(uncentered);
    if (uncenteredLen > width)
    {
        strncpy(centered, uncentered, width);
        centered[width] = '\0';
        return centered;
    }
    
    uint8_t lenDelta = width - uncenteredLen;
    uint8_t startPos = lenDelta / 2;
    uint8_t i;
    for (i=0; i<width; i++)
    {
        centered[i] = ' ';
    }
 
    for (i=0; i<uncenteredLen; i++)
    {
        centered[i+startPos] = uncentered[i];
    }
    // centered[width] = '\0';
    return centered;
}   

void DISP_handleCenterButton(void)
{
    G_modeSel = (G_modeSel + 1) % 2;
    if (G_modeSel == 0) {
        G_txtScreen[G_screenLineMode0][0] = '<';
        G_txtScreen[G_screenLineMode1][0] = ' ';
        G_txtScreen[G_screenLineMode0][G_txtCharPerLine - 1] = '>';
        G_txtScreen[G_screenLineMode1][G_txtCharPerLine - 1] = ' ';        
    }
    else
    {
        G_txtScreen[G_screenLineMode0][0] = ' ';
        G_txtScreen[G_screenLineMode1][0] = '<';
        G_txtScreen[G_screenLineMode0][G_txtCharPerLine - 1] = ' ';
        G_txtScreen[G_screenLineMode1][G_txtCharPerLine - 1] = '>';          
    }
}

void DISP_updateMode(void)
{
    uint8_t wid = DISP_screenWidthInChar-2;
    DISP_center(wid, &(G_txtScreen[G_screenLineMode0][1]), G_modeNames0[G_mode[0]]);
    DISP_center(wid, &(G_txtScreen[G_screenLineMode1][1]), G_modeNames1[G_mode[1]]);
    if (G_modeSel == 0) {
        G_txtScreen[G_screenLineMode0][0] = '<';
        G_txtScreen[G_screenLineMode1][0] = ' ';
        G_txtScreen[G_screenLineMode0][G_txtCharPerLine - 1] = '>';
        G_txtScreen[G_screenLineMode1][G_txtCharPerLine - 1] = ' ';        
    }
    else
    {
        G_txtScreen[G_screenLineMode0][0] = ' ';
        G_txtScreen[G_screenLineMode1][0] = '<';
        G_txtScreen[G_screenLineMode0][G_txtCharPerLine - 1] = ' ';
        G_txtScreen[G_screenLineMode1][G_txtCharPerLine - 1] = '>';          
    }
}

void DISP_handleLeftButton(void)
{
    if (G_mode[G_modeSel] == 0)
    {
        G_mode[G_modeSel] = G_modeSize[G_modeSel];
    }
    G_mode[G_modeSel]--;
    DISP_updateMode();
}

void DISP_handleRightButton(void)
{
    G_mode[G_modeSel]++;
    if (G_mode[G_modeSel] >= G_modeSize[G_modeSel])
    {
        G_mode[G_modeSel] = 0;
    }
    DISP_updateMode();
}

static bool G_displayStart = true;
bool DISP_getStart(void)
{
    return G_displayStart;
}
void DISP_enableDisplayThisCycle()
{
    G_displayStart = true;
}
void DISP_preventDispThisCycle()
{
    G_displayStart = false;
}
