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

// Librerias propias

#include "ADC.h"
#include "SPI.h"


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

int ADC, ADC2;
int trash01, trash02, trash03;
int contador;

//-----------------------------------------------------------------------------
//                            Prototipos 
//-----------------------------------------------------------------------------

void setup(void);
void putch(char data); //funcion para recibir el dato que se desea transmitir

//-----------------------------------------------------------------------------
//                            Interrupciones
//-----------------------------------------------------------------------------
void __interrupt() isr(void)
{
     // Interrupcion del ADC
    
       if(PIR1bits.ADIF == 1)       // Reviso la bandera del ADC
       {
           if(ADCON0bits.CHS == 0) { // Si estoy en el canal 0 desplegar al portc
               ADC = ADRESH;
               ADCON0bits.CHS = 1;
//               PIR1bits.ADIF = 0;
           }
           else if(ADCON0bits.CHS == 1){
            ADCON0bits.CHS = 0;
               ADC2 = ADRESH; 
//               PIR1bits.ADIF = 0;
            }
           PIR1bits.ADIF = 0;        // Bajo la bandera del ADC
       }

       
       // Interrupcion del SPI
       
        if(SSPIF == 1){
            trash01 = spiRead();
            spiWrite(ADC2);
            trash02 = spiRead();
            spiWrite(ADC);
            SSPIF = 0;
    }
}

//-----------------------------------------------------------------------------
//                            Main
//-----------------------------------------------------------------------------
void main(void) {
    
    setup();    // Llamo a mi configuracion

    
    while(1)    // Equivale al loop
    {
      if (ADCON0bits.GO == 0){ //se apaga automaticamente entonces hay que
            __delay_us(100);     //volver a encenderlo
            ADCON0bits.GO = 1;
        }  
    }
}

//-----------------------------------------------------------------------------
//                            Funciones
//-----------------------------------------------------------------------------

void setup(void){
    
    ANSEL = 0b00000011;
    ANSELH = 0;
    
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    
    TRISB = 0;
    
    TRISD = 0;
    
    PORTB = 0;
    PORTD = 0;
    
    INTCONbits.GIE = 1;         // Habilitamos interrupciones
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones PEIE
    PIR1bits.SSPIF = 0;         // Borramos bandera interrupci�n MSSP
    PIE1bits.SSPIE = 1;         // Habilitamos interrupci�n MSSP
    TRISAbits.TRISA5 = 1;       // Slave Select
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW,
            SPI_IDLE_2_ACTIVE);
    
    //Configurar reloj interno
    OSCCONbits.IRCF0 = 0;        //reloj interno de 4mhz
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.SCS = 1;  //internal oscillator is used for system clock
    
    // Configuracion del ADC
    ADC_config(2);
}

