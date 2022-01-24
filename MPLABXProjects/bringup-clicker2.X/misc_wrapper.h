/* 
 * File:   helpers.h
 * 
 */

#ifndef MISC_WRAPPER_H
#define	MISC_WRAPPER_H


void spin(uint32_t cnt);
uint16_t getTableLen16(int16_t *table);
bool isUint(char *s);
int stringInArray(char *str, const char *strArray[], int len);

#endif	/* MISC_WRAPPER_H */

