/* 
* File:   leds.h
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#ifndef LEDS_H
#define	LEDS_H

#define LED1 LATAbits.LATA0
#define LED2 LATAbits.LATA1


void initLEDs();
void initSW2();

#endif	/* LEDS_H */

