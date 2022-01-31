/**
  @Generated 16-bit Bootloader Source File

  @Company:
    Microchip Technology Inc.

  @File Name: 
    interrupts.S

  @Summary:
    This is the interrupts.S file generated using 16-bit Bootloader

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
/* This file lists all of the interrupts in the system and how they will be
 * handled.  This file is use by both the hardware interrupt table and the 
 * user remap table to make sure they both stay in sync.
 *
 * IMPORTANT NOTE: Once a boot loader is deployed using this file, this file 
 * can not be modified in the end application.  Take care when selecting how to 
 * handle each interrupt at the development of the boot loader.
 *
 * Options:
 *   remap_to_application - this forwards the interrupt directly to the
 *   user application.  Each interrupt forwarded will require 2 instructions
 *   for the GOTO in the user reamapping table thus taking up 6 bytes of program
 *   memory each.  This is the safest option for all interrupts implemented in 
 *   hardware.  
 *
 *   keep_in_bootloader - this option will keep the interrupt in the boot
 *   loader.  If the interrupt function is defined, it will just to that
 *   function.  If it is not defined, it will jump to the default interrupt 
 *   handler function.
 *
 *   remap_to_application_default - this forwards the interrupt directly to the
 *   user application's default interrupt handler rather than the specified 
 *   unique interrupt vector.  This option is useful for interrupts that the
 *   application does not expect to use.  Since each interrupt forwarded by the
 *   remap_to_application option takes 2 instruction words, can get quite costly
 *   to forward all possible interrupts.  Interrupts forwarded with this option
 *   do not take any additional code space to forward.  Since multiple
 *   interrupts will be forwarded to the same vector, the user code will have to
 *   check to see which interrupt triggered to process them accordingly.  
 */
    
#ifdef REMAP_TABLE    

KEEP_IN_BOOTLOADER   OscillatorFail       
KEEP_IN_BOOTLOADER   AddressError       
KEEP_IN_BOOTLOADER   NVMError       
KEEP_IN_BOOTLOADER   StackError       
KEEP_IN_BOOTLOADER   MathError       
REMAP_TO_APPLICATION_DEFAULT   ReservedTrap5       
KEEP_IN_BOOTLOADER   GeneralError       
REMAP_TO_APPLICATION_DEFAULT   ReservedTrap7       
KEEP_IN_BOOTLOADER   INT0Interrupt       
KEEP_IN_BOOTLOADER   IC1Interrupt       
KEEP_IN_BOOTLOADER   OC1Interrupt       
KEEP_IN_BOOTLOADER   T1Interrupt       
KEEP_IN_BOOTLOADER   DMA0Interrupt       
KEEP_IN_BOOTLOADER   IC2Interrupt       
KEEP_IN_BOOTLOADER   OC2Interrupt       
KEEP_IN_BOOTLOADER   T2Interrupt       
KEEP_IN_BOOTLOADER   T3Interrupt       
KEEP_IN_BOOTLOADER   SPI1Interrupt       
KEEP_IN_BOOTLOADER   SPI1TXInterrupt       
KEEP_IN_BOOTLOADER   U1RXInterrupt       
KEEP_IN_BOOTLOADER   U1TXInterrupt       
KEEP_IN_BOOTLOADER   ADC1Interrupt       
KEEP_IN_BOOTLOADER   DMA1Interrupt       
KEEP_IN_BOOTLOADER   NVMInterrupt       
KEEP_IN_BOOTLOADER   SI2C1Interrupt       
KEEP_IN_BOOTLOADER   MI2C1Interrupt       
KEEP_IN_BOOTLOADER   CompInterrupt       
KEEP_IN_BOOTLOADER   IOCInterrupt       
KEEP_IN_BOOTLOADER   INT1Interrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt21       
KEEP_IN_BOOTLOADER   CCP5Interrupt       
KEEP_IN_BOOTLOADER   CCP6Interrupt       
KEEP_IN_BOOTLOADER   DMA2Interrupt       
KEEP_IN_BOOTLOADER   OC3Interrupt       
KEEP_IN_BOOTLOADER   OC4Interrupt       
KEEP_IN_BOOTLOADER   T4Interrupt       
KEEP_IN_BOOTLOADER   T5Interrupt       
KEEP_IN_BOOTLOADER   INT2Interrupt       
KEEP_IN_BOOTLOADER   U2RXInterrupt       
KEEP_IN_BOOTLOADER   U2TXInterrupt       
KEEP_IN_BOOTLOADER   SPI2Interrupt       
KEEP_IN_BOOTLOADER   SPI2TXInterrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt34       
REMAP_TO_APPLICATION_DEFAULT   Interrupt35       
KEEP_IN_BOOTLOADER   DMA3Interrupt       
KEEP_IN_BOOTLOADER   IC3Interrupt       
KEEP_IN_BOOTLOADER   IC4Interrupt       
KEEP_IN_BOOTLOADER   IC5Interrupt       
KEEP_IN_BOOTLOADER   IC6Interrupt       
KEEP_IN_BOOTLOADER   OC5Interrupt       
KEEP_IN_BOOTLOADER   OC6Interrupt       
KEEP_IN_BOOTLOADER   CCT3Interrupt       
KEEP_IN_BOOTLOADER   CCT4Interrupt       
KEEP_IN_BOOTLOADER   PMPInterrupt       
KEEP_IN_BOOTLOADER   DMA4Interrupt       
KEEP_IN_BOOTLOADER   CCT5Interrupt       
KEEP_IN_BOOTLOADER   CCT6Interrupt       
KEEP_IN_BOOTLOADER   SI2C2Interrupt       
KEEP_IN_BOOTLOADER   MI2C2Interrupt       
KEEP_IN_BOOTLOADER   CCT7Interrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt52       
KEEP_IN_BOOTLOADER   INT3Interrupt       
KEEP_IN_BOOTLOADER   INT4Interrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt55       
REMAP_TO_APPLICATION_DEFAULT   Interrupt56       
REMAP_TO_APPLICATION_DEFAULT   Interrupt57       
KEEP_IN_BOOTLOADER   SPI1RXInterrupt       
KEEP_IN_BOOTLOADER   SPI2RXInterrupt       
KEEP_IN_BOOTLOADER   SPI3RXInterrupt       
KEEP_IN_BOOTLOADER   DMA5Interrupt       
KEEP_IN_BOOTLOADER   RTCCInterrupt       
KEEP_IN_BOOTLOADER   CCP1Interrupt       
KEEP_IN_BOOTLOADER   CCP2Interrupt       
KEEP_IN_BOOTLOADER   U1ErrInterrupt       
KEEP_IN_BOOTLOADER   U2ErrInterrupt       
KEEP_IN_BOOTLOADER   CRCInterrupt       
KEEP_IN_BOOTLOADER   DMA6Interrupt       
KEEP_IN_BOOTLOADER   DMA7Interrupt       
KEEP_IN_BOOTLOADER   SI2C3Interrupt       
KEEP_IN_BOOTLOADER   MI2C3Interrupt       
KEEP_IN_BOOTLOADER   LVDInterrupt       
KEEP_IN_BOOTLOADER   CCP7Interrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt74       
REMAP_TO_APPLICATION_DEFAULT   Interrupt75       
REMAP_TO_APPLICATION_DEFAULT   Interrupt76       
KEEP_IN_BOOTLOADER   CTMUInterrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt78       
REMAP_TO_APPLICATION_DEFAULT   Interrupt79       
REMAP_TO_APPLICATION_DEFAULT   Interrupt80       
KEEP_IN_BOOTLOADER   U3ErrInterrupt       
KEEP_IN_BOOTLOADER   U3RXInterrupt       
KEEP_IN_BOOTLOADER   U3TXInterrupt       
KEEP_IN_BOOTLOADER   I2C1BCInterrupt       
KEEP_IN_BOOTLOADER   I2C2BCInterrupt       
KEEP_IN_BOOTLOADER   USB1Interrupt       
KEEP_IN_BOOTLOADER   U4ErrInterrupt       
KEEP_IN_BOOTLOADER   U4RXInterrupt       
KEEP_IN_BOOTLOADER   U4TXInterrupt       
KEEP_IN_BOOTLOADER   SPI3Interrupt       
KEEP_IN_BOOTLOADER   SPI3TXInterrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt92       
REMAP_TO_APPLICATION_DEFAULT   Interrupt93       
KEEP_IN_BOOTLOADER   CCP3Interrupt       
KEEP_IN_BOOTLOADER   CCP4Interrupt       
KEEP_IN_BOOTLOADER   CLC1Interrupt       
KEEP_IN_BOOTLOADER   CLC2Interrupt       
KEEP_IN_BOOTLOADER   CLC3Interrupt       
KEEP_IN_BOOTLOADER   CLC4Interrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt100       
KEEP_IN_BOOTLOADER   CCT1Interrupt       
KEEP_IN_BOOTLOADER   CCT2Interrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt103       
REMAP_TO_APPLICATION_DEFAULT   Interrupt104       
REMAP_TO_APPLICATION_DEFAULT   Interrupt105       
KEEP_IN_BOOTLOADER   FSTInterrupt       
REMAP_TO_APPLICATION_DEFAULT   Interrupt107       
REMAP_TO_APPLICATION_DEFAULT   Interrupt108       
KEEP_IN_BOOTLOADER   I2C3BCInterrupt       
KEEP_IN_BOOTLOADER   RTCCTSInterrupt       
KEEP_IN_BOOTLOADER   U5RXInterrupt       
KEEP_IN_BOOTLOADER   U5TXInterrupt       
KEEP_IN_BOOTLOADER   U5ErrInterrupt       
KEEP_IN_BOOTLOADER   U6RXInterrupt       
KEEP_IN_BOOTLOADER   U6TXInterrupt       
KEEP_IN_BOOTLOADER   U6ErrInterrupt       
KEEP_IN_BOOTLOADER   JTAGInterrupt       

#endif
