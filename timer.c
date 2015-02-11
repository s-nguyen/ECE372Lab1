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
    TMR2 = 0;
    PR2 = 14*delay;
    IFS0bits.T2IF = 0;
    T2CONbits.TCKPS = 0x0;
    T2CONbits.TON = 1;
    while(IFS0bits.T2IF == 0);
    T2CONbits.TON = 0;
}

void delay5ms(){
    TMR2 = 0;
    PR2 = (FCY*0.005)/PRESCALE - 1;
    IFS0bits.T2IF = 0;
    T2CONbits.TCKPS = 0b01;
    T2CONbits.TON = 1;
    while(IFS0bits.T2IF == 0){
        //Do nothing
    }
    T2CONbits.TON = 0;
}



