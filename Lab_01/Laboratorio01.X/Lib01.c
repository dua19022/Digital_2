///* 
// * File:   Lib01.c
// * Author: marco
// *
// * Created on July 19, 2021, 8:09 PM
// */
//
//#include <xc.h>
//#include <stdint.h>
//#include "Lib01.h"
////-----------------------------------------------------------------------------
////                            Variables 
////-----------------------------------------------------------------------------
//
char tabla[16] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,
    0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111, 0b01110111, 
    0b01111100, 0b00111001, 0b01011110, 0b01111001, 0b01110001};


////-----------------------------------------------------------------------------
////                            Prototipos 
////-----------------------------------------------------------------------------
//
//void oscilator(void);
//void timer_0(void);
//void ADC_config(void);
//
//
////-----------------------------------------------------------------------------
////                            Funciones
////-----------------------------------------------------------------------------
//void oscilator(uint8_t frec){
//    switch(frec){                   //31kHz
//        case 0: 
//            OSCCONbits.IRCF = 000;     
//            break;   
//        case 1:                     //125kHz
//            OSCCONbits.IRCF = 001;     
//            break;
//        case 2:                     //250kHz
//            OSCCONbits.IRCF = 010;     
//            break;
//        case 3:                     //500kHz
//            OSCCONbits.IRCF = 011;     
//            break;
//        case 4:                     //1MHz
//            OSCCONbits.IRCF = 100;     
//            break;
//        case 5:                     //2MHz
//            OSCCONbits.IRCF = 101;     
//            break;
//        case 7:                     //8MHz
//            OSCCONbits.IRCF = 111;     
//            break;   
//        default:                     //4MHz
//            OSCCONbits.IRCF = 110;     
//            break;            
//    }
//    OSCCONbits.SCS = 1; //se utiliza el reloj interno del sistema
//}
//
//void timer_0(uint8_t prescaler){
//    switch(prescaler){              //1:2 rate
//        case 0: 
//            OPTION_REGbits.PS = 000;     
//            break;   
//        case 1:                     //1:4 rate
//            OPTION_REGbits.PS = 001;     
//            break;
//        case 2:                     //1:8 rate
//            OPTION_REGbits.PS = 010;     
//            break;
//        case 3:                     //1:16 rate
//            OPTION_REGbits.PS = 011;     
//            break;
//        case 4:                     //1:32 rate
//            OPTION_REGbits.PS = 100;     
//            break;
//        case 5:                     //1:64 rate
//            OPTION_REGbits.PS = 101;     
//            break;
//        case 7:                     //1:256 rate
//            OPTION_REGbits.PS = 111;     
//            break;   
//        default:                     //1:128 rate
//            OPTION_REGbits.PS = 110;     
//            break;            
//    }
//    OPTION_REGbits.T0CS = 0; //fuente del reloj interna Fosc/4  
//    OPTION_REGbits.PSA = 0;  //preescalar asignado a TMR0  
//}
//
//void ADC_config(uint8_t adcFrec){
//    switch(adcFrec){              
//        case 0: 
//            ADCON0bits.ADCS = 00;     //Fosc/2
//            break;   
//        case 1:                       //Fosc/8
//            ADCON0bits.ADCS = 01;     
//            break;
//        default:                      //Fosc/32
//            ADCON0bits.ADCS = 10;     
//            break;
//    }
//}
