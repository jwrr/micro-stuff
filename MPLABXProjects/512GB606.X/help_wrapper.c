
#include "usb_wrapper.h"

static const char HELP_helpMenu[] = {
    "Help Menu"USB_EOL
    "-------------------------------------"USB_EOL
    "left     (a) - Emulate left button"USB_EOL
    "select   (s) - Emulate select button"USB_EOL
    "right    (d) - Emulate right button"USB_EOL
    "trigger  (f) - Emulate trigger"USB_EOL
    "----------------------------------------"USB_EOL
    "erase    (e) - Erase wave"USB_EOL
    "help     (h) - Display this help message"USB_EOL
    "write    (w) - Write wave table"USB_EOL
    "read     (r) - Read wave table"USB_EOL
};


const char *HELP_getHelpMenu()
{
    return HELP_helpMenu;
}

