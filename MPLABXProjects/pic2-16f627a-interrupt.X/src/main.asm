PROCESSOR 16F627A

#include <xc.inc>
    
; Include Path: C:\Program Files\Microchip\xc8\v2.32\pic\include\proc
; The following is not needed anymore
#include "pic16f627.inc"

; CONFIG
  CONFIG  WDTE = OFF            ; Watchdog Timer (WDT disabled)
  CONFIG  CP = OFF              ; Code Protect (Code protection off)
  CONFIG  MCLRE = OFF           ; Master Clear Enable (GP3/MCLR pin fuction is digital I/O, MCLR internally tied to VDD)

temp	EQU 70h	; general purpose
w_save	EQU 71h	; working file reg context save
s_save	EQU 72h	; status file reg context save

d1	EQU 73h	; delay routine
d2	EQU 74h
d3	EQU 75h
	
isr_d1	EQU 76h ; isr delay routine
isr_d2  EQU 77h
isr_d3	EQU 78h

; In MPLAB X: File -> project properties -> pic-as linker -> Custom linker options
; Enter: -pres_vect=0h; -pint_vec=4h
; Set delta=2 for code. Set delta=1 for data
PSECT rst_vec, class=CODE, delta=2
rst_vec:
    goto main
    
PSECT int_vec, class=CODE, delta=2
int_vec:
    btfss   INTF
    retfie
    bcf	    INTF
    
    movwf   w_save
    movf    STATUS, W
    movwf   s_save
    
    BANKSEL PORTB
    bsf	    RB3
    call    isr_delay
    bcf	    RB3
    
    movf    s_save, w
    movwf   STATUS
    movf    w_save, w

    retfie
    
PSECT code
delay_500ms:
    movlw   0x03
    movwf   d1
    movlw   0x18
    movwf   d2
    movlw   0x02
    movwf   d3
delay_500ms_0:
    decfsz  d1, f
    goto    $+2
    decfsz  d2, f
    goto    $+2
    decfsz  d3, f
    goto    delay_500ms_0
    goto    $+1
    return
    
isr_delay:
    movlw   0x07
    movwf   isr_d1
    movlw   0x2F
    movwf   isr_d2
    movlw   0x03
    movwf   isr_d3
isr_delay_0:
    decfsz  isr_d1, f
    goto    $+2
    decfsz  isr_d2, f
    goto    $+2
    decfsz  isr_d3, f
    goto    isr_delay_0
    goto    $+1
    goto    $+1
    goto    $+1
    return
    
main:
    banksel TRISB
    movlw   00000001B ; RB0 input, others are output
    movwf   TRISB
    
    banksel PORTB
    clrf    PORTB
    BSF	    RB5
    
poll_input:
    btfsc   RB0
    goto    poll_input
    call    delay_500ms
    
    ; config interrupt
    banksel OPTION_REG
    bcf	    INTEDG
    banksel INTCON
    bcf	    INTF    ; clear flag before enabling interrupt
    bsf	    INTE    ; enable interrupt
    bsf	    GIE	    ; emable all unmasked interrupts
    
main_loop:
    nop
    bsf	    RB5
    call    delay_500ms
    bcf	    RB5
    call    delay_500ms
    goto    main_loop
    
END
