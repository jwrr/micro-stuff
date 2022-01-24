/* 
 * File:   font_wrapper.h
 * 
 */

#ifndef FONT_WRAPPER_H
#define	FONT_WRAPPER_H

#include <stdint.h>
#include <stdbool.h>

uint8_t FONT_charToIndex(char ch);
uint8_t FONT_getTxtLineNumber(uint8_t pixLineNumber);
void FONT_getPixLine(uint8_t pixLineNumber, uint8_t *pixLine);
bool FONT_isTxtLineAllSpaces(uint8_t pixLineNumber);
bool FONT_isStartingBlankLine(uint8_t pixLineNumber);

void FONT_toggleBlackOnWhite(void);
bool FONT_getBlackOnWhite(void);

#endif	/* FONT_WRAPPER_H */

