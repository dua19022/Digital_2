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


void ADC_conf(char frec);

char translate_hex(char var);


#endif	/* LIB01_H */

