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

char pot1, pot2;
int contador;
char hundreds, tens, units, residuo;
char cen, dec, uni;
char var;
char con;
int full;

//-----------------------------------------------------------------------------
//                            Prototipos 
//-----------------------------------------------------------------------------

void setup(void);
void ReadSlave(void);
char division (char valor);
void mensaje(void);


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
        
        
    PORTCbits.RC2 = 0;       //Slave Select
       __delay_ms(1);
       
       spiWrite(0x0A);
       pot1 = spiRead();
       __delay_ms(1);
       spiWrite(0x0A);
       pot2 = spiRead();
       __delay_ms(1);
       
       
       __delay_ms(1);
       PORTCbits.RC2 = 1;       //Slave Deselect 
       mensaje();
       
       PORTB = full;
        
    }
}

//-----------------------------------------------------------------------------
//                            Funciones
//-----------------------------------------------------------------------------

void setup(void){
    
    ANSEL = 0;
    ANSELH = 0;
    TRISC2 = 0;
    TRISB = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTCbits.RC2 = 1;
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE,
            SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    
    // Configuraciones TX y RX
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 1;
    BAUDCTLbits.BRG16 = 0;
    
    SPBRG = 25;
    SPBRGH = 1;
    
    RCSTAbits.SPEN = 1;
    RCSTAbits.RX9 = 0;
    RCSTAbits.CREN = 1;
    TXSTAbits.TX9 = 0;          // 8 bits
    
    TXSTAbits.TXEN = 1;
    
    PIR1bits.RCIF = 0;  // Bandera rx
    PIR1bits.TXIF = 0;  // bandera tx
    
    //Configurar reloj interno
    OSCCONbits.IRCF0 = 0;        //reloj interno de 4mhz
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.SCS = 1;  //internal oscillator is used for system clock
}

char division (char valor){
    hundreds = valor/50;//esto me divide entre 100 y se queda con el entero
    residuo = valor%100; //el residuo de lo que estoy operando
    tens = residuo/10; 
    units = residuo%10; //se queda con las units de las tens
    // Se les suma 47 para que me den al valor requerido
    hundreds = hundreds + 48;
    tens = tens + 48;
    units = units + 48;
} 

void mensaje (void){
    division(pot1);
    __delay_ms(250); //Tiempos para el despliegue de los caracteres
    printf("\r Valor del POT1:\r");
    __delay_ms(250);
    printf("  ");
    __delay_ms(250);
    TXREG = hundreds;
    __delay_ms(250);
    TXREG = 46;
    __delay_ms(250);
    TXREG = tens;
    __delay_ms(250);
    TXREG = units;
    __delay_ms(250);
    printf(" V");
    __delay_ms(250);
    printf("\r");
    
    // Se despliega el valor del pot 2
    division(pot2);
    __delay_ms(250); 
    printf("\r Valor del POT2: \r");
    __delay_ms(250);
    printf("  ");
    __delay_ms(250);
    TXREG = hundreds;
    __delay_ms(250);
    TXREG = 46;
    __delay_ms(250);
    TXREG = tens;
    __delay_ms(250);
    TXREG = units;
    __delay_ms(250);
    printf(" V");
    __delay_ms(250);
    printf("\r");
    
    printf("Ingresar Centena: Rango(0-2)\r");
      defensa1:  
       while(RCIF == 0);
        cen = RCREG -48;  

       while(RCREG > '2'){ 
           goto defensa1;
       }
    
    printf("Ingresar Decenas: \r");
      defensa2:
        while(RCIF == 0); 
         dec = RCREG -48; 

        if(cen == 2){
           while(RCREG > '5'){
               goto defensa2;
           }
       }

    printf("Ingresar Unidades: \r");
      defensa3:
       while(RCIF == 0); 
        uni = RCREG - 48;

       if(cen == 2 && dec == 5){
           while(RCREG > '5'){
               goto defensa3;
           }
       }
      con = concat(cen, dec);
      full = concat(con, uni);
      __delay_ms(250);
    printf("El numero elegido es: %d", full);
}

void putch(char data){      // Funcion especifica de libreria stdio.h
    while(TXIF == 0);
    TXREG = data; // lo que se muestra de la cadena
    return;
}   

int concat(int a, int b)
{
 
    char s1[20];
    char s2[20];

 
    // Convert both the integers to string
    sprintf(s1, "%d", a);
    sprintf(s2, "%d", b);

 
    // Concatenate both strings
    strcat(s1, s2);
 
    // Convert the concatenated string
    // to integer
    int c = atoi(s1);
 
    // return the formed integer
    return c;
}
