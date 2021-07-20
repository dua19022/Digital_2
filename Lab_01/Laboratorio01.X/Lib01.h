/* 
 * File:   Lib01.h
 * Author: marco
 *
 * Created on July 19, 2021, 7:31 PM
 */

#ifndef LIB01_H_
#define	LIB01_H_

#pragma config FOSC = INTRC_NOCLKOUT
#include <xc.h>


void oscilator(void);
void timer_0(void);
void ADC_config(void);
#endif	/* LIB01_H */

