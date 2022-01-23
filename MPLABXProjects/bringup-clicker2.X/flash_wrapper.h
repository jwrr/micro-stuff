/* 
 * File:   flash_wrapper.h
 * Author: robin
 *
 * Created on January 21, 2022, 11:22 AM
 */

#ifndef FLASH_WRAPPER_H
#define	FLASH_WRAPPER_H

uint32_t FLASH_getPageSize();
uint32_t FLASH_getNumPages();
uint8_t FLASH_erasePage(uint8_t PageNumber);
uint8_t FLASH_writePage(int32_t writeData[], uint32_t dataSize, uint8_t pageNumber);
uint8_t FLASH_writePages(int32_t writeData[], uint32_t dataLen);
int32_t FLASH_readFromPage(uint8_t pageNumber, uint16_t pageOffset);
uint32_t FLASH_read(uint32_t flashOffset);
uint8_t FLASH_writeTable(int32_t currentTable[], uint16_t tableLen, uint8_t flashPageNumber);
uint8_t FLASH_verify(const int32_t dataTable[], uint16_t len, uint8_t pageNumber);
uint8_t FLASH_test();

void FLASH_memcpy16to32(int32_t dest32[], int16_t src16[], uint16_t len, int32_t upperWordVal);
\
void FLASH_clearLoadBuffer();
void FLASH_appendLoadBuffer(uint32_t value);
void FLASH_getLoaddBufferLen();
uint32_t FLASH_getLoadBuffer(uint16_t i);
uint8_t FLASH_writeLoadBuffer(uint8_t pageNumber);

#endif	/* FLASH_WRAPPER_H */

