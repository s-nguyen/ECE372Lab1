/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include "p24fj64ga002.h"
#include "timer.h"

#define FCY 7372800*4/2
#define TIME 0.005 //5ms
#define prVal (FCY*TIME)/8 - 1


//Uses timer 2
void delayUs(unsigned int delay){
    //TODO: Create a delay using timer 2 for "delay" microseconds.
}

void initTimer1(){
    //unsigned int prVal = (FCY*TIME)/256.0 - 1.0;
    PR1 = prVal; //PRVAL //2 Seconds
    

    TMR1 = 0; //Reset the counter to 0
    T1CONbits.TCKPS = 0b01; //1:256 prescale Value
    IFS0bits.T1IF = 0; //Put down flag first
    //IEC0bits.T1IE = 1; //Enable Timer Interrupt at start
    T1CONbits.TON = 0; //Turn off  timer
}

void deBounce5ms(){
    TMR1 = 0;
    IFS0bits.T1IF = 0;
    while(IFS0bits.T1IF == 0){
        //Do nothing
    }
}