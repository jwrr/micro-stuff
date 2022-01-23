#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "mcc_generated_files/system.h"

// ===============================================================
// GPIO

void GPIO_set(char port, uint8_t pos, bool value)
{
    uint16_t mask1 = 1 << pos;
    uint16_t mask0 = ~mask1;
    switch (port)
    {
    case 'A': LATA = value ? (LATA | mask1) : (LATA & mask0); break;
    case 'B': LATB = value ? (LATB | mask1) : (LATB & mask0); break;
    case 'C': LATC = value ? (LATC | mask1) : (LATC & mask0); break;
    case 'D': LATD = value ? (LATD | mask1) : (LATD & mask0); break;
    case 'E': LATE = value ? (LATE | mask1) : (LATE & mask0); break;
    case 'F': LATF = value ? (LATF | mask1) : (LATF & mask0); break;
    case 'G': LATG = value ? (LATG | mask1) : (LATG & mask0); break;
    default: break;
    }
}

void GPIO_toggle(char port, uint8_t pos)
{
    uint16_t massk = 1 << pos;
    switch (port)
    {
    case 'A': LATA ^= massk;
    case 'B': LATB ^= massk;
    case 'C': LATC ^= massk;
    case 'D': LATD ^= massk;
    case 'E': LATE ^= massk;
    case 'F': LATF ^= massk;
    case 'G': LATG ^= massk;
    default: break;
    }
}

// bool GPIO_Get(char port, uint8_t pos)
bool GPIO_get(char *pin)
{
    uint8_t pinLen = strlen(pin);
    if (pinLen < 3) return false;
    
    char port = pin[1];
    uint8_t pos = (uint8_t)strtol(&(pin[2]), NULL, 10);
    uint16_t mask0 = 1 << pos;
    switch (port)
    {
    case 'A': return (bool)(PORTA & mask0);
    case 'B': return (bool)(PORTB & mask0);
    case 'C': return (bool)(PORTC & mask0);
    case 'D': return (bool)(PORTD & mask0);
    case 'E': return (bool)(PORTE & mask0);
    case 'F': return (bool)(PORTF & mask0);
    case 'G': return (bool)(PORTG & mask0);
    default: return false;
    }
    return false;
}

// l GPIO_EdgeDetect(char port, uint8_t pos, bool *val, uint8_t whichEdge)
bool GPIO_edgeDetect(char *pin, bool *val, uint8_t whichEdge)
{
    bool prevVal = *val;
    bool newVal = GPIO_get(pin);
    *val = newVal;
    bool falling = whichEdge == 0;
    bool rising  = whichEdge == 1;
    bool both    = !falling && !rising;
    bool edgeDetected = (rising  && !prevVal && newVal) ||
                        (falling && prevVal && !newVal) ||
                        (both && (prevVal != newVal));
    return edgeDetected;
}
