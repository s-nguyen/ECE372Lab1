/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include "p24fj64ga002.h"
#include "timer.h"

#define FCY 7372800*4/2
#define PRESCALE 8



//Uses timer 2

void delayUs(unsigned int delay){
    PR2 = (FCY*(delay/1000000)/PRESCALE)-1;
    //TODO: Create a delay using timer 2 for "delay" microseconds.
    TMR2 = 0;
    IFS0bits.T1IF = 0;
    while(IFS0bits.T2IF == 0){
        //Do nothing
    }
}

void initTimer2(){
    TMR2 = 0; //Reset the counter to 0
    T2CONbits.TCKPS = 0b01; //1:256 prescale Value
    IFS0bits.T2IF = 0; //Put down flag first
    T2CONbits.TON = 0; //Turn off  timer
}
