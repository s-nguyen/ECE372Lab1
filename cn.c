#include "p24fj64ga002.h"
#include "cn.h"

void initCNForSW1(){
    //Use the switch on the board connected to RB5
    TRISBbits.TRISB5 = 1;
    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1;
    CNEN2bits.CN27IE = 1;
}

void initSW2(){
    AD1PCFGbits.PCFG4 = 1;
    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1;


    TRISBbits.TRISB2 = 1; //IO5

    CNPU1bits.CN6PUE = 1;
    CNEN1bits.CN6IE = 1;

}