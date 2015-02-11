/*
* File:   leds.c
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#include "p24fj64ga002.h"
#include "leds.h"


void initLEDs(){

    //TODO: Initialize the appropriate pins to work with the LEDs
    TRISAbits.TRISA0 = 0; //IO1
    TRISAbits.TRISA1 = 0; //IO2

    LATAbits.LATA0 = 1;
    LATAbits.LATA1 = 1;

    ODCAbits.ODA0 = 1;
    ODCAbits.ODA1 = 1;

    AD1PCFGbits.PCFG0 = 1;
    AD1PCFGbits.PCFG1 = 1;
    
}

void initSW2(){
    AD1PCFGbits.PCFG4 = 1;
    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1;


    TRISBbits.TRISB2 = 1; //IO5
    
    CNPU1bits.CN6PUE = 1;
    CNEN1bits.CN6IE = 1;
    

    

    //TODO: Initialize the appropriate pins to work with the external switch using a
    //change notification interrupt.
    
}