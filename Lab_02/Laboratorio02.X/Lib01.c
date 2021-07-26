///* 
// * File:   Lib01.c
// * Author: marco
// *
// * Created on July 19, 2021, 8:09 PM
// */
#define _XTAL_FREQ 250000
#include <xc.h>
#include <stdint.h>
#include "Lib01.h"
////-----------------------------------------------------------------------------
////                            Variables 
////-----------------------------------------------------------------------------



////-----------------------------------------------------------------------------
////                            Funciones
////-----------------------------------------------------------------------------
void ADC_conf(char frec) { //en este caso para seleccionar la frecuencia ADC
    switch(frec){
        case 0: //FOSC/2
            ADCON0bits.CHS = 0;     //canal 0
            __delay_us(100);
    
            ADCON0bits.ADCS0 = 0;   //para que el clock select sea FOSC/2
            ADCON0bits.ADCS1 = 0;   
            ADCON0bits.ADON = 1;    //ADC enable bit
            ADCON1bits.ADFM = 0;    //left justified
            ADCON1bits.VCFG1 = 0;   //5 voltios
            ADCON1bits.VCFG0 = 0;   //tierra
            break;
        case 1: //FOSC/8
            ADCON0bits.CHS = 0;     //canal 0
            __delay_us(100);

            ADCON0bits.ADCS0 = 1;   //para que el clock select sea FOSC/8
            ADCON0bits.ADCS1 = 0;   
            ADCON0bits.ADON = 1;    //ADC enable bit
            ADCON1bits.ADFM = 0;    //left justified
            ADCON1bits.VCFG1 = 0;   //5 voltios
            ADCON1bits.VCFG0 = 0;   //tierra
            break;
        case 2: //FOSC/32
            ADCON0bits.CHS = 0;     //canal 0
            __delay_us(100);

            ADCON0bits.ADCS0 = 0;   //para que el clock select sea FOSC/32
            ADCON0bits.ADCS1 = 1;   
            ADCON0bits.ADON = 1;    //ADC enable bit
            ADCON1bits.ADFM = 0;    //left justified
            ADCON1bits.VCFG1 = 0;   //5 voltios
            ADCON1bits.VCFG0 = 0;   //tierra
            break;
        case 3: //FRC
            ADCON0bits.CHS = 0;     //canal 0
            __delay_us(100);

            ADCON0bits.ADCS0 = 1;   //para que el clock select sea FRC
            ADCON0bits.ADCS1 = 1;   
            ADCON0bits.ADON = 1;    //ADC enable bit
            ADCON1bits.ADFM = 0;    //left justified
            ADCON1bits.VCFG1 = 0;   //5 voltios
            ADCON1bits.VCFG0 = 0;   //tierra
            break;
    }
    return;
}

//char translate_hex(char var){
//    char hex_code;
//    hex_code = tabla[var];
//    return hex_code;
//}
