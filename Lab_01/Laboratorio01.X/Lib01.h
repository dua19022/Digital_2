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

//char tabla[16] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,
//    0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111, 0b01110111, 
//    0b01111100, 0b00111001, 0b01011110, 0b01111001, 0b01110001};
char translate_hex(char var);


#endif	/* LIB01_H */

