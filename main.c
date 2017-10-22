/*
 * File:   main.c
 * Author: alberto
 *
 * Created on September 2, 2017, 5:55 PM
 */



// PIC16F1503 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ  500000      // oscillator frequency for _delay()

#define MAXRT   200             // Maximum reaction time (in ms)

#include <xc.h>


void main(void) {
    
    // initialize
    TRISA = 0b111011;   // set RA2 as output
    TRISC = 0b111110;   // set RC0 as output
    
    // configure oscillator
    OSCCONbits.SCS1 = 1;        // select internal clock
    OSCCONbits.IRCF = 0b0111;   // internal oscillator = 500 kHz
    
    
    LATCbits.LATC0 = 0; // write 0 RC0
    
    // configure Timer0
    OPTION_REGbits.TMR0CS = 0;  // select timer mode
    OPTION_REGbits.PSA = 0;     // assign prescaler to Timer0
    OPTION_REGbits.PS = 0b111;  // prescale = 256
    
    // enable interrupts
    INTCONbits.TMR0IE = 1;  // enable Timer0 interrupt
    ei();                   // enable global interrupts

   
    //TMR0 = 0;               // clear timer0
    
   
    while(1){
        LATAbits.LATA2 = 1; // write 1 RA2 to RA1
        __delay_ms(1000);
        LATAbits.LATA2 = 0; // write 0 RA2 to RA1
        __delay_ms(1000);
        
        
        
        /*
        if (!INTCONbits.TMR0IF && TMR0 < (int)(MAXRT/2.048)) {
            LATCbits.LATC0 = 1; // write 0 RC0
        }
        */
        /*
        if (INTCONbits.TMR0IF) {
            LATCbits.LATC0 = 1; // write 0 RC0
        }
        */
        
    }
}


void interrupt isr(void) {
    INTCONbits.TMR0IF = 0;  // and overflow flag
    LATCbits.LATC0 = ~LATCbits.LATC0; // write 0 RC0
}
