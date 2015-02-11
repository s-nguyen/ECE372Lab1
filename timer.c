/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include "p24fj64ga002.h"
#include "timer.h"

#define FCY 7372800.0*2
#define PRESCALE 8.0

//Uses timer 2

void delayUs(unsigned int delay){
    unsigned int prVal = (FCY*delay/1000000.0)/PRESCALE - 1.0; //(FCY*(delay/1000000)/PRESCALE) - 1;
    PR2 = prVal;
    //TODO: Create a delay using timer 2 for "delay" microseconds.
    TMR2 = 0;
    IFS0bits.T2IF = 0;
    while(IFS0bits.T2IF == 0){
        //Do nothing
    }
}

void initTimer2(){
    TMR2 = 0; //Reset the counter to 0
    T2CONbits.TCKPS = 0b01; //1:256 prescale Value
    IFS0bits.T2IF = 0; //Put down flag first
    T2CONbits.TON = 1;
}
