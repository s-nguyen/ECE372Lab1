/* 
 * File:   stopwatchmain.c
 * Author: Stephen Nguyen
 *
 * Created on February 11, 2015, 8:23 PM
 */

#include "p24fj64ga002.h"
#include "lcd.h"
#include "timer.h"
#include "leds.h"
#include "cn.h"
#include <stdio.h>


_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_ON & COE_OFF & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )

typedef enum stateTypeEnum{


    Stop, Run, Debounce


} stateType;

volatile stateType curState;
volatile stateType nextState;
volatile int watch;
volatile int reset; //For If SW1 is pressed

int main(void)
{
    char s[9]; //Character array to fill LCD. Used speceficaly for getTimedString.
    
    initLCD();
    initLEDs();
    initSW2();
    initTimer1();
    initCNForSW1();
    
    curState = Run;
    watch = 0;
    
    while(1)
    {
        switch(curState){
            case(Run):
                LED1 = 1;
                LED2 = 0;
                moveCursorLCD(0,0);
                printStringLCD("Running:");
                getTimedString(watch, s);
                moveCursorLCD(1, 0);
                printStringLCD(s);
                nextState = Stop;
                break;
            case(Stop):
                LED1 = 0;
                LED2 = 1;
                moveCursorLCD(0,0);     //Always move cursor to correct position before printing
                printStringLCD("Stopped:");
                getTimedString(watch, s); //Function to turn time into string and set into s
                moveCursorLCD(1,0);
                printStringLCD(s);
                if(reset != 1){         //Don't set nextState if reset is activated, want to go to the same state when reseted
                  nextState = Run;
                }
                break;
            case(Debounce):
                if(BUTTON == RELEASED || RESET == RELEASED){
                    curState = nextState;
                }
                break;
            default:
                curState = Run;
                break;
        }
    }

    return 0;
}

void _ISR _CNInterrupt(void){
    IFS1bits.CNIF = 0;
    delay5ms();
    
    if(RESET == PRESSED && curState == Stop){ //Only Reset on button press during Stop stage
        curState = Debounce;
        nextState = Stop;
        watch = 0;
    }
    if(RESET == PRESSED){ //Reset flag should go up regardless of state when SW1 is pressed
        reset = 1;
    }
    else if(BUTTON == RELEASED && reset != 1){  //Don't allow this to work if reset flag is high
        curState = Debounce;
    }
    else if(RESET == RELEASED){        //Put flag down when button is released.
        reset = 0;
    }
}

void _ISR _T1Interrupt(void){
    //Put down the timer 1 flag first!
    IFS0bits.T1IF = 0;
    if(curState == Run){
        watch++;        //Increments watch which is every 10ms
    }
    
}
