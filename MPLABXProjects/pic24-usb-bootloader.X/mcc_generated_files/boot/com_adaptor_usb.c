/**
  @Generated 16-bit Bootloader Source File

  @Company:
    Microchip Technology Inc.

  @File Name: 
    com_adaptor_uart.c

  @Summary:
    This is the com_adaptor_uart.c file generated using 16-bit Bootloader

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  16-bit Bootloader - 1.19.0
        Device            :  PIC24FJ1024GB610
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36B
        MPLAB             :  MPLAB X v5.15
*/
/*
Copyright (c) [2012-2022] Microchip Technology Inc.  

    All rights reserved.

    You are permitted to use the accompanying software and its derivatives 
    with Microchip products. See the Microchip license agreement accompanying 
    this software, if any, for additional info regarding your rights and 
    obligations.
    
    MICROCHIP SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT 
    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
    LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT 
    AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP OR ITS
    LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT 
    LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE 
    THEORY FOR ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT 
    LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
    OR OTHER SIMILAR COSTS. 
    
    To the fullest extend allowed by law, Microchip and its licensors 
    liability will not exceed the amount of fees, if any, that you paid 
    directly to Microchip to use this software. 
    
    THIRD PARTY SOFTWARE:  Notwithstanding anything to the contrary, any 
    third party software accompanying this software is subject to the terms 
    and conditions of the third party's license agreement.  To the extent 
    required by third party licenses covering such third party software, 
    the terms of such license will apply in lieu of the terms provided in 
    this notice or applicable license.  To the extent the terms of such 
    third party licenses prohibit any of the restrictions described here, 
    such restrictions will not apply to such third party software.
*/
#include <string.h>
#include "com_adaptor.h"
#include "boot_config.h"
// #include "../uart5.h"
#include "../../usblib.h"

#define INVALID_PEEK_REQUEST_DATA 0x42


struct COM_DATA_STRUCT {
    uint8_t pendingCommand[BOOT_CONFIG_MAX_PACKET_SIZE];
    uint16_t pendingCommandLength;
};

static struct COM_DATA_STRUCT COM_comData;

uint8_t BOOT_COM_Peek(uint16_t location)
{
    if(location >= COM_comData.pendingCommandLength)
    {
        return INVALID_PEEK_REQUEST_DATA;
    }
    return COM_comData.pendingCommand[location];
}

uint16_t BOOT_COM_Read(uint8_t* data, uint16_t length)
{
    uint16_t bytesToRead = BOOT_COM_GetBytesReady();
    
    if(length < bytesToRead)
    {
        bytesToRead = length;
    }
    
    memcpy(data, &COM_comData.pendingCommand[0], bytesToRead);
    memmove(&COM_comData.pendingCommand[0], &COM_comData.pendingCommand[bytesToRead], BOOT_CONFIG_MAX_PACKET_SIZE - bytesToRead);
    COM_comData.pendingCommandLength -= bytesToRead;

    return bytesToRead;
};

// FIXME
bool BOOT_COM_Write(uint8_t* data, uint16_t length)
{
    bool success = USB_write(data, length);
    return success;
};

// FIXME
uint16_t BOOT_COM_GetBytesReady()
{
    static bool initilized=false;
    if (!initilized)
    {
        // ======================================================================================================
        // During com_adaptor_initialization the user may want to check the UART for any errors here before 
        // proceeding. Make sure the RX line is either driven high by the transmitter or pulled high via a pullup.
        // Failure to do so could cause the user to encounter frame errors or other line errors which can be 
        // difficult to debug.
        // ======================================================================================================      
        memset(&COM_comData,0, sizeof(struct COM_DATA_STRUCT )/sizeof(uint8_t));
        initilized = true;
    }
//    while ( UART5_IsRxReady() && (uartComData.pendingCommandLength < BOOT_CONFIG_MAX_PACKET_SIZE) )
    while (COM_comData.pendingCommandLength < BOOT_CONFIG_MAX_PACKET_SIZE)
    {
        uint8_t ch;
        uint16_t len = USB_read(&ch, 1);
        if (len == 0) break;
        COM_comData.pendingCommand[COM_comData.pendingCommandLength++]= ch;
    }

    return COM_comData.pendingCommandLength;
}