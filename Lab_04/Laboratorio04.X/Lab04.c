/******************************************************************************
 * Laboratorio 3
 ******************************************************************************
 * File:   Lab01.c
 * Author: Marco
 * 
 *
 */

//-----------------------------------------------------------------------------
//                            Librerias 
//-----------------------------------------------------------------------------

#define _XTAL_FREQ 4000000
#include <xc.h>
#include <stdint.h>
#include <stdio.h>  // Para usar printf
#include <string.h> // Concatenar
#include <stdlib.h>

// Librerias propias
#include "I2C.h"


//-----------------------------------------------------------------------------
//                            Bits de configuracion 
//-----------------------------------------------------------------------------
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


//-----------------------------------------------------------------------------
//                            Variables 
//-----------------------------------------------------------------------------

int full;

//-----------------------------------------------------------------------------
//                            Prototipos 
//-----------------------------------------------------------------------------

void setup(void);


//-----------------------------------------------------------------------------
//                            Interrupciones
//-----------------------------------------------------------------------------
void __interrupt() isr(void)
{
     
}

//-----------------------------------------------------------------------------
//                            Main
//-----------------------------------------------------------------------------
void main(void) {
    
    setup();    // Llamo a mi configuracion

    
    while(1)    // Equivale al loop
    {

        //Obtener informacion del primer slave
        I2C_Master_Start();
        I2C_Master_Write(0x51); //51, el 1 para que lea
        PORTB = I2C_Master_Read(0); //lo escribo en el puerto de leds
        I2C_Master_Stop();
        __delay_ms(200);
       //Obtener informacion del sensor de temperatura
        //Direccion 0x90 porque A0 A1 y A2 estan a tierra
        I2C_Master_Start();
        I2C_Master_Write(0x80); //seleccionar el sensor y se escribe
        I2C_Master_Write(0xF3); //read temperature
        I2C_Master_Stop();
        __delay_ms(200);
        
        I2C_Master_Start();
        I2C_Master_Write(0x81); //para que ahora lea
        PORTD = I2C_Master_Read(0); //read temperature
        I2C_Master_Stop();
        __delay_ms(200);

    }
}

//-----------------------------------------------------------------------------
//                            Funciones
//-----------------------------------------------------------------------------

void setup(void){
    
    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0;
    PORTB = 0;
    TRISD = 0;
    
    //limpiar puertos
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;
    
//    //Configurar reloj interno
    OSCCONbits.IRCF0 = 0;        //reloj interno de 8mhz
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.SCS = 1;  //internal oscillator is used for system clock
    
//    //configuracion de interrupciones
//    PIE1bits.ADIE = 1;      //enable de la int del ADC
//    PIR1bits.ADIF = 0;      //limpiar la interrupcion del ADC
//    INTCONbits.GIE = 1;     //habilita las interrupciones globales
//    INTCONbits.PEIE = 1;    //periferical interrupts
 
    // I2C configuracion Maestro
    I2C_Master_Init(100000);        // Inicializar Comuncaci�n I2C
}
