/******************************************************************************
 * Laboratorio 1
 ******************************************************************************
 * File:   Lab01.c
 * Author: Marco
 * 
 *
 */

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

#define _XTAL_FREQ 250000
#include <xc.h>
#include <stdint.h>
#include <stdio.h>  // Para usar printf
#include "Lib01.h"
//-----------------------------------------------------------------------------
//                            Variables 
//-----------------------------------------------------------------------------
char tabla[16] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,
    0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111, 0b01110111, 
    0b01111100, 0b00111001, 0b01011110, 0b01111001, 0b01110001};
int multi;
int ADC;
int flag;
char display;
uint8_t nib_up;
uint8_t nib_do;

//-----------------------------------------------------------------------------
//                            Prototipos 
//-----------------------------------------------------------------------------

void setup(void);
char nibbles_setup (char display);
void alarma(void);

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
    if(T0IF == 1)   // Verificar la bandera del timer0
    {   
        RA5 = 0;
        RA6 = 0;
       if (flag == 1){
            PORTAbits.RA5 = 1; 
//            PORTAbits.RA6 = 0;
            PORTD = tabla[nib_up];
            flag = 0;
        }
        else {
            PORTAbits.RA6 = 1;
//            PORTAbits.RA5 = 0;
            PORTD = tabla[nib_do];
            flag = 1;
        }
       
        INTCONbits.T0IF = 0;    // Limpio la interrupcion del timer0
        TMR0 = 255;     // Configuro el valor de reinicio del timer0
        
    }
    if (RBIF == 1)  // Verificar bandera de la interrupcion del puerto b
    {
        if (PORTBbits.RB0 == 0) // Si oprimo el boton 1
        {
            PORTC = PORTC + 1;  // Se suma 1 al puerto
        }
        if  (PORTBbits.RB1 == 0)    // Se oprimo el boton 2
        {
            PORTC = PORTC - 1;  // Se le resta 1 al puerto
        }
        INTCONbits.RBIF = 0;    // Se limpia la bandera de la interrupcion
    }
}

//-----------------------------------------------------------------------------
//                            Main
//-----------------------------------------------------------------------------
void main(void) {
    
    setup();    // Llamo a mi configuracion

    
    while(1)    // Equivale al loop
    {
        
        nibbles_setup(ADC);
        if (GO == 0){
            __delay_us(100);
            GO = 1;
        }
        alarma();
    }
}

//-----------------------------------------------------------------------------
//                            Funciones
//-----------------------------------------------------------------------------

void setup(void){
    
    flag = 1;
    
    // Configuraciones de puertos digitales
    ANSEL = 0b00000001;
    ANSELH = 0x00;
    
    // Configurar bits de salida o entradaas
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISAbits.TRISA6 = 0;
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISC = 0x00;
    TRISD = 0x00;
    
    // Se limpian los puertos
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    
    // Se configura el oscilador
    OSCCONbits.IRCF2 = 0;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 0;   // Se configura a 250kHz
    OSCCONbits.SCS = 1;
    
    // Timer0
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS2 = 1;
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS0 = 1;
    
    // Configuracion de pull-up interno
    OPTION_REGbits.nRBPU = 0;
    WPUB = 0b00000011;
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1;
    
    // Configuacion de las interrupciones
    INTCONbits.GIE = 1;
    INTCONbits.RBIF = 1;    // Para que el boton funcione a la primera
    INTCONbits.RBIE = 1;    // Interrupcion Puerto B
    INTCONbits.PEIE = 1;    // Periferical interrupt
    INTCONbits.T0IF = 0; 
    PIE1bits.ADIE = 1;      // Activar la interrupcion del ADC
    PIR1bits.ADIF = 0;      // Bandera del ADC
    
    // Configuracion del ADC
//    ADCON0bits.ADCS0 = 0;
//    ADCON0bits.ADCS1 = 1;       // FOSC/32
//    ADCON0bits.ADON = 1;        // Activar el ADC  
//    ADCON0bits.CHS = 0;         // Canal 0
//    __delay_us(50);  
//    ADCON1bits.ADFM = 0;        // Justificado a la izquierda
//    ADCON1bits.VCFG0 = 0;       // Volataje de referencia vss y vddd
//    ADCON1bits.VCFG1 = 0;

    ADC_conf(2);
}

char nibbles_setup (char display){    //funcion para recibir datos del ADC
    nib_do = display & 0x0F;       //Pasan bits menos significativos
    nib_up = (display>>4) & 0x0F; //paso a bits mas significativos
    return nib_do, nib_up;
}

void alarma (void){
    if (ADC < PORTC){
        RA4 = 1;
    }
    else {
        RA4 = 0;
    }
}