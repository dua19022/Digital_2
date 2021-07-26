/******************************************************************************
 * Laboratorio 2
 ******************************************************************************
 * File:   Lab02.c
 * Author: Marco
 */

//-----------------------------------------------------------------------------
//                            Librerias 
//-----------------------------------------------------------------------------
#define _XTAL_FREQ 4000000
#include <xc.h>
#include <stdint.h>
#include <stdio.h>  // Para usar printf
#include "Lib_LCD.h"
#include "Lib01.h"

#define RS RE0
#define EN RE1
#define D0 RD0
#define D1 RD1
#define D2 RD2
#define D3 RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

//  Bits de configuracion   //
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
char volt01;
char volt02;
char div;
char display;
char ADC;

//-----------------------------------------------------------------------------
//                            Prototipos 
//-----------------------------------------------------------------------------

void setup(void);


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
           }
           PIR1bits.ADIF = 0;        // Bajo la bandera del ADC
       }
       
        INTCONbits.T0IF = 0;    // Limpio la interrupcion del timer0
        TMR0 = 255;     // Configuro el valor de reinicio del timer0
        
    
}

//-----------------------------------------------------------------------------
//                            Main
//-----------------------------------------------------------------------------
void main(void) {
    
    setup();    // Llamo a mi configuracion
    char a;
    
    Lcd_Init();
    Lcd_Clear();
    
    while(1)    // Equivale al loop
    {
       Lcd_Set_Cursor(1, 1);
       Lcd_Write_String("S_1: S_2 S_3:");
       Lcd_Set_Cursor(2,1);
       Lcd_Write_String("0.00");
       __delay_ms(2000);
        
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

    
    // Configuraciones de puertos digitales
    ANSEL = 0b00000011;
    ANSELH = 0x00;
    
    // Configurar bits de salida o entradaas
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 0;
    TRISD = 0x00;
    TRISE = 0x00;
    
    // Se limpian los puertos
    PORTA = 0x00;    
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;
    
    // Se configura el oscilador
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 0;   // Se configura a 4mhz
    OSCCONbits.SCS = 1;
    
    // Timer0
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS2 = 1;
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS0 = 1;
    
    
    // Configuacion de las interrupciones
    INTCONbits.GIE = 1;
    INTCONbits.RBIF = 1;    // Para que el boton funcione a la primera
    INTCONbits.RBIE = 1;    // Interrupcion Puerto B
    INTCONbits.PEIE = 1;    // Periferical interrupt
    INTCONbits.T0IF = 0; 
    PIE1bits.ADIE = 1;      // Activar la interrupcion del ADC
    PIR1bits.ADIF = 0;      // Bandera del ADC
    
    // Configuracion del ADC
//    ADC_conf(2);    // Se llama a la libreria del ADC
}

