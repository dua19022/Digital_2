/*
 * File:   Proyecto02.c
 * Author: marco
 *
 * Created on May 18, 2021, 1:35 AM
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


#include <xc.h>
#include <stdint.h>

//-----------------------------------------------------------------------------
//                            Variables 
//-----------------------------------------------------------------------------

char var01;      // Variable del multiplexeo
char var02;  // Variables pra la divisiones
char flag;
char unidades;
char res;
char contador;  // Variable que posee el valor del puerto
char tabla[4] = {0b00111111, 0b00000110, 0b01011011, 0b01001111};


//-----------------------------------------------------------------------------
//                            Prototipos 
//-----------------------------------------------------------------------------
void setup(void);   // Defino las funciones antes de crearlas
char division(void);

//-----------------------------------------------------------------------------
//                            Interrupciones
//-----------------------------------------------------------------------------
void __interrupt() isr(void)
{
    if(T0IF == 1)   // Verificar la bandera del timer0
    {   
        
        
    }
    if (RBIF == 1)  // Verificar bandera de la interrupcion del puerto b
    {
        if (PORTBbits.RB0 == 0) // Si oprimo el boton 1
        {
            flag = 1;
        }
        if  (PORTBbits.RB1 == 0)    // Se oprimo el boton 2
            {
            PORTC = var01;
            var01 <<= 1;

            }
        if  (PORTBbits.RB2 == 0)    // Se oprimo el boton 3
            {
            PORTD = var02;
            var02 <<= 1;
                
            }
            
        
    }
        
        INTCONbits.RBIF = 0;    // Se limpia la bandera de la interrupcion
}

//-----------------------------------------------------------------------------
//                            Main
//-----------------------------------------------------------------------------
void main(void) {
    
    setup();    // Llamo a mi configuracion
    
    
    while(1)    // Equivale al loop
    {
        
      
    }
}

//-----------------------------------------------------------------------------
//                            Configuraciones
//-----------------------------------------------------------------------------

void setup(void){
    
    // Configuraciones de puertos digitales
    ANSEL = 0x00;
    ANSELH = 0x00;
    
    // Configurar bits de salida o entradaas
    TRISA = 0x00;
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
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
    WPUB = 0b00000111;
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1;
    IOCBbits.IOCB2 = 1;
    
    // Configuacion de las interrupciones
    INTCONbits.GIE = 1;
    INTCONbits.RBIF = 1;
    INTCONbits.RBIE = 1;
    INTCONbits.T0IE = 1;
    INTCONbits.T0IF = 0;  
    
    // algo llamado inicialiazacion de variables
    var01 = 0b00000001;
    var02 = 0b00000001;
}