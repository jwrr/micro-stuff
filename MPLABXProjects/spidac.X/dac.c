
#include <stdint.h>
#include <stdbool.h>

#include "gpio.h"
#include "mcc_generated_files/spi2.h"

// ===============================================================

void DAC_SPI2_initialize(void)
{
    // AUDEN disabled; FRMEN disabled; AUDMOD I2S; FRMSYPW One clock wide; AUDMONO stereo; FRMCNT 0; MSSEN disabled; FRMPOL disabled; IGNROV disabled; SPISGNEXT not sign-extended; FRMSYNC disabled; URDTEN disabled; IGNTUR disabled; 
    SPI2CON1H = 0x00;
    // WLENGTH 0; 
    SPI2CON2L = 0x00;
    // SPIROV disabled; FRMERR disabled; 
    SPI2STATL = 0x00;
    // SPI2BRGL 0; 
    SPI2BRGL = 0x07; // Baud Rate Generator. MCC set this to 0x00; Changed it to 7 to match display
    // SPITBFEN disabled; SPITUREN disabled; FRMERREN disabled; SRMTEN disabled; SPIRBEN disabled; BUSYEN disabled; SPITBEN disabled; SPIROVEN disabled; SPIRBFEN disabled; 
    SPI2IMSKL = 0x00;
    // RXMSK 0; TXWIEN disabled; TXMSK 0; RXWIEN disabled; 
    SPI2IMSKH = 0x00;
    // SPI2URDTL 0; 
    SPI2URDTL = 0x00;
    // SPI2URDTH 0; 
    SPI2URDTH = 0x00;
    // SPIEN enabled; DISSDO disabled; MCLKEN FOSC/2; CKP Idle:Low, Active:High; SSEN disabled; MSTEN Master; MODE16 enabled; SMP Middle; DISSCK disabled; SPIFE Frame Sync pulse precedes; CKE Idle to Active; MODE32 disabled; SPISIDL disabled; ENHBUF enabled; DISSDI disabled; 
    SPI2CON1L = 0x8421;  
}

// DAC121S101


#define GPIO_clr(NAME) GPIO_concat(NAME,_PORT) &= ~(1 << GPIO_concat(NAME,_BIT))
#define GPIO_set(NAME) GPIO_concat(NAME,_PORT) |= (1 << GPIO_concat(NAME,_BIT))


static bool DAC_xferInProgress = false;
void DAC_writeSPI(uint16_t value)
{
    if (DAC_xferInProgress) {
        while (SPI2STATLbits.SPIRBE);
        uint16_t unused = SPI2BUFL; // clears SPIRBE
    }
//    LATE |= 0x0010;
//    LATE &= 0xFFEF;
    GPIO_set(GPIO_DACCS);
    GPIO_clr(GPIO_DACCS);
    SPI2BUFL = value;
    DAC_xferInProgress = true;
}


