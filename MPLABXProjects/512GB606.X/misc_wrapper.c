
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

void spin(uint32_t cnt)
{
    while (cnt--);
}

uint16_t getTableLen16(int16_t *table)
{
    uint16_t maxLen = 256;
    uint16_t len = 0;
    for (; len < maxLen; len++)
    {
        if (table[len] == -1)
        {
            return len+1;
        }
    }
    return maxLen;
}

bool isUint(char *s)
{
    uint16_t i = 0;
    if (s[0] == '\0') return false;
    for (i=0; s[i] != '\0'; i++)
    {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

    
int stringInArray(char *str, const char *strArray[], int len)
{
    int i = 0;
    for (; i < len; i++)
    {
        if (strcmp(str, strArray[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

