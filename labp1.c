// ******************************************************************************************* //
//
// File:         lab1p1.c
// Date:         
// Authors:      Stephen Nguyen
//
// Description: Part 1 for lab 1
// ******************************************************************************************* //

#include "p24fj64ga002.h"
#include "leds.h"
#include "timer.h"
#include <stdio.h>


_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_ON & COE_OFF & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )

// ******************************************************************************************* //

typedef enum stateTypeEnum{


    Led1, Led2, Debounce


} stateType;

volatile stateType curState;
volatile stateType nextState;

int main(void)
{

    initLEDs();
    initSW2();
    initTimer2();
    curState = Led1;
    
    while(1)
    {
        //TODO: Using a finite-state machine, define the behavior of the LEDs
        //Debounce the switch
        
        switch(curState){
            case(Led1):
                LED1 = 0;
                LED2 = 1;
                nextState = Led2;
                break;
            case(Led2):
                LED1 = 1;
                LED2 = 0;
                nextState = Led1;
                break;
            case(Debounce):
                if(PORTBbits.RB2 == 1){
                    curState = nextState;
                }
                break;
            default:
                curState = Led1;
                break;
        }
    }
    
    return 0;
}

void _ISR _CNInterrupt(void){
    //TODO: Implement the interrupt to capture the press of the button
    IFS1bits.CNIF = 0;
    delayUs(5000);
    if(PORTBbits.RB5 == 1){
        curState = Debounce;
    }
    

}