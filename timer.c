/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include "p24fj64ga002.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>

#define FCY 7372800.0*2
#define PRESCALE 8.0

//Uses timer 2

void delayUs(unsigned int delay){
    TMR2 = 0;
    PR2 = 14*delay;
    IFS0bits.T2IF = 0;
    T2CONbits.TCKPS = 0x0;
    T2CONbits.TON = 1;
    while(IFS0bits.T2IF == 0){
        
    }
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

void getTimedString(int watch, char* str){
    int FF = watch % 100;
    int SS = (watch / 100) % 60;
    int MM = ((watch / 100) - SS) / 60;
    //char* s = (char*)malloc(9*sizeof(char));
    
    sprintf(str, "%02d:%02d:%02d", MM, SS, FF);

}

void initTimer1(){
    TMR1 = 0;
    PR1 = (FCY*.01)/256 - 1;

    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
    T1CONbits.TCKPS = 0b11;
    T1CONbits.TON = 1;
}


