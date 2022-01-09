/* 
 * File:   main.h
 *
 * Created on January 3, 2022, 9:34 AM
 */

#ifndef MAIN_H
#define	MAIN_H

#define WELCOME_PROMPT "Hello from PIC 'p abc' to unlock. 'h' for help.\n\r> "
#define USB_PASSWORD "abc"
#define NUM_WAVEFORMS 12
#define WAVEFORM_SIZE 256
#define USB_LINELEN 255

static uint8_t G_readBuffer[CDC_DATA_OUT_EP_SIZE];
char     G_line[USB_LINELEN] = "";
char     G_outStr[2048];
char     G_mostRecentCommand[22] = "";

char     G_version[20]  = "1.2.3";
double   G_voltage      = 17.62;
uint8_t  G_temperature  = 0;
uint8_t  G_mode[2]      = {0, 0};
uint8_t  G_modeCount[2] = {3, 3};

const char G_modeNames0[][10] = {" AAAA  ", " BBBBB ", " CCC  ", "CUSTOM ", ""};
const char G_modeNames1[][10] = {" EEEEEE ", " FFFFFFF", "   GGG  ", ""};
uint8_t  G_modeSel          = 0;
uint8_t  G_config           = 0;
uint8_t  G_usb              = 0;
uint8_t  G_usbTrig          = 0;
uint8_t  G_usbLeft          = 0;
uint8_t  G_usbRight         = 0;
uint8_t  G_usbSel           = 0;
uint8_t  G_state            = 0;
bool     G_run_usb          = false;
bool     G_refreshScreen    = false;
bool     G_showGraphics     = false;
bool     G_usbLocked        = false;
bool     G_usbEcho          = true;
bool     G_selfTestResult   = true; // true = pass; false = fail
uint8_t  G_triggerCountDown = 0;
uint8_t  G_triggerCountDownMax = 5;
bool     G_engineeringMode  = false;
uint8_t  G_customLoadIndex  = 0;
bool     G_waveLoadInProgress = false;
bool     G_customLoaded     = false;
bool     G_forceDisplayUpdate = false;
uint32_t G_spinTime         = 10000;
    
int16_t G_waveformTable[NUM_WAVEFORMS][WAVEFORM_SIZE];

char G_screen[13][22] = {
    "BATTERY:      100%\n\r", // 0
    "TEMPERATURE:   25C\n\r", // 1
    "SELF TEST:    PASS\n\r", // 1
    "    SIGNAL OFF    \n\r", // 3
    "                  \n\r", // 4
    "<      AAAA      >\n\r", // 5
    "                  \n\r", // 6
    "<     EEEEEEE    >\n\r", // 7
    "                  \n\r", // 8
    "  P/N: PN123-01   \n\r", // 9
    "  F/W: FW123-01   \n\r", // 10
    "      USB ON      \n\r", // 11
    "> "
};

char G_screenPrev[13][22] = { 
    "xxxxxx:       100%\n\r", // 0
    "xxxxxxxxx:    PASS\n\r", // 1
    "                  \n\r", // 2
    "    SIGNAL OFF    \n\r", // 3
    "                  \n\r", // 4
    "<      AAAA      >\n\r", // 5
    "                  \n\r", // 6
    "<     EEEEEEE    >\n\r", // 7
    "                  \n\r", // 8
    "  P/N: PN123-01   \n\r", // 9
    "  F/W: FW123-01   \n\r", // 10
    "      USB ON      \n\r", // 11
    "> "
};

char *G_screenBatteryLevel = &(G_screen[0][14]);
char *G_screenTemperature  = &(G_screen[1][14]);
char *G_screenPassFail     = &(G_screen[2][14]);
char *G_screenSignal       = &(G_screen[3][11]);
char *G_screenMode0        = &(G_screen[5][7]);
char *G_screenMode1        = &(G_screen[7][5]);
char *G_screenUSB          = &(G_screen[11][0]);

char G_prompt[] = "\n\r> ";
char G_help[] = "\n\r"
    "Help Menu\n\r"
    "-------------------------------------------\n\r"
    "left     (a) - Emulate left button\n\r"
    "select   (s) - Emulate select button\n\r"
    "right    (d) - Emulate right button\n\r"
    "trigger  (f) - Emulate trigger\n\r"
    "-------------------------------------------\n\r"
    "clear    (c) - Clear current custom waveform table\n\r"
    "eng      (e) - Toggle engineering mode\n\r"
    "graphics (g) - Toggle between graphics/text display\n\r"
    "help     (h) - Display this help message\n\r"
    "load     (l) - Load wave table\n\r"
    "refresh  (r) - Refresh screen\n\r"
    "view     (v) - View current waveform table\n\r"
    "> ";

enum button_t {NONE=0, RIGHTARROW=1, LEFTARROW=2, SELECT=4, TRIGGER=8};

const uint8_t G_font[][8+1] = {
    {'A',  0x1c, 0x22, 0x41, 0x7f, 0x41, 0x41, 0x41, 0x00} /* 0 */,
    {'B',  0x7e, 0x41, 0x41, 0x7e, 0x41, 0x41, 0x7e, 0x00} /* 1 */,
    {'C',  0x3e, 0x41, 0x40, 0x40, 0x40, 0x41, 0x3e, 0x00} /* 2 */,
    {'D',  0x7c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x7c, 0x00} /* 3 */,
    {'E',  0x7f, 0x40, 0x40, 0x78, 0x40, 0x40, 0x7f, 0x00} /* 4 */,
    {'F',  0x7f, 0x40, 0x40, 0x78, 0x40, 0x40, 0x40, 0x00} /* 5 */,
    {'G',  0x3e, 0x40, 0x40, 0x47, 0x41, 0x41, 0x3e, 0x00} /* 6 */,
    {'H',  0x41, 0x41, 0x41, 0x7f, 0x41, 0x41, 0x41, 0x00} /* 7 */,
    {'I',  0x3e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x3e, 0x00} /* 8 */,
    {'J',  0x0f, 0x02, 0x02, 0x02, 0x42, 0x42, 0x3c, 0x00} /* 9 */,
    {'K',  0x41, 0x42, 0x44, 0x78, 0x44, 0x42, 0x41, 0x00} /* 10 */,
    {'L',  0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7f, 0x00} /* 11 */,
    {'M',  0x41, 0x63, 0x55, 0x49, 0x41, 0x41, 0x41, 0x00} /* 12 */,
    {'N',  0x41, 0x61, 0x51, 0x49, 0x45, 0x43, 0x41, 0x00} /* 13 */,
    {'O',  0x1c, 0x22, 0x41, 0x41, 0x41, 0x22, 0x1c, 0x00} /* 14 */,
    {'P',  0x7e, 0x41, 0x41, 0x7e, 0x40, 0x40, 0x40, 0x00} /* 15 */,
    {'Q',  0x1c, 0x22, 0x41, 0x41, 0x41, 0x22, 0x1c, 0x06} /* 16 */,
    {'R',  0x7e, 0x41, 0x41, 0x7e, 0x44, 0x42, 0x41, 0x00} /* 17 */,
    {'S',  0x3e, 0x41, 0x40, 0x3e, 0x01, 0x41, 0x3e, 0x00} /* 18 */,
    {'T',  0x7f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00} /* 19 */,
    {'U',  0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x3e, 0x00} /* 20 */,
    {'V',  0x41, 0x41, 0x22, 0x22, 0x14, 0x14, 0x08, 0x00} /* 21 */,
    {'W',  0x41, 0x49, 0x49, 0x49, 0x49, 0x55, 0x22, 0x00} /* 22 */,
    {'X',  0x41, 0x22, 0x14, 0x08, 0x14, 0x22, 0x41, 0x00} /* 23 */,
    {'Y',  0x41, 0x41, 0x22, 0x14, 0x08, 0x08, 0x1c, 0x00} /* 24 */,
    {'Z',  0x7f, 0x01, 0x06, 0x08, 0x30, 0x40, 0x7f, 0x00} /* 25 */,
    {'0',  0x3e, 0x43, 0x45, 0x49, 0x51, 0x61, 0x3e, 0x00} /* 26 */,
    {'1',  0x08, 0x18, 0x28, 0x08, 0x08, 0x08, 0x7f, 0x00} /* 27 */,
    {'2',  0x3e, 0x41, 0x01, 0x0e, 0x70, 0x40, 0x7f, 0x00} /* 28 */,
    {'3',  0x3e, 0x41, 0x01, 0x0e, 0x01, 0x41, 0x3e, 0x00} /* 29 */,
    {'4',  0x0e, 0x12, 0x22, 0x7f, 0x02, 0x02, 0x1f, 0x00} /* 30 */,
    {'5',  0x7f, 0x40, 0x40, 0x7e, 0x01, 0x41, 0x3e, 0x00} /* 31 */,
    {'6',  0x3e, 0x41, 0x40, 0x7e, 0x41, 0x41, 0x3e, 0x00} /* 32 */,
    {'7',  0x7f, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x00} /* 33 */,
    {'8',  0x3e, 0x41, 0x41, 0x3e, 0x41, 0x41, 0x3e, 0x00} /* 34 */,
    {'9',  0x3e, 0x41, 0x41, 0x3f, 0x01, 0x41, 0x3e, 0x00} /* 35 */,
    {' ',  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} /* 36 */,
    {'<',  0x01, 0x06, 0x1c, 0x70, 0x1c, 0x06, 0x01, 0x00} /* 37 */,
    {'>',  0x40, 0x30, 0x1c, 0x07, 0x1c, 0x30, 0x40, 0x00} /* 38 */,
    {'%',  0x31, 0x52, 0x64, 0x08, 0x13, 0x25, 0x46, 0x00} /* 39 */,
    {':',  0x00, 0x0c, 0x0c, 0x00, 0x0c, 0x0c, 0x00, 0x00} /* 40 */,
    {'/',  0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00} /* 41 */,
    {'-',  0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00} /* 42 */
};

enum {LETTER_A=0, DIGIT_0=26, SPACE=36, LT=37, GT=38, PERCENT=39, COLON=40,
      SLASH=41, DASH=42};

#endif	/* MAIN_H */

