/******************************************************************************
 * Laboratorio 2
 ******************************************************************************
 * File:   Lab02.c
 * Author: Marco
 */
#include <xc.h>
#include <stdint.h>
#include <stdio.h> //para que funcione el sprintf
#include <stdlib.h>
#include <pic16f887.h> 
#define _XTAL_FREQ 4000000

#define RS RE0
#define EN RE2
#define D0 RD0
#define D1 RD1
#define D2 RD2
#define D3 RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

#include "UART.h" //libreria para configurar ADC
#include "ADC.h"
#include "Lib_LCD.h" //libreria para controlar LCD

/*=============================================================================
                        BITS DE CONFIGURACION
 =============================================================================*/
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO 
//oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/
//CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and 
//can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR 
//pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code 
//protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code 
//protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal
///External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit 
//(Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit 
//(RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit 
//(Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits 
//(Write protection off)

/*==============================================================================
                               VARIABLES
 =============================================================================*/

char volt01, volt02;
char voltaje_b, voltaje_c;
char dividendo, centenas, residuo, decenas, unidades;
char dato1;
char dato; //el dato que deseo almacenar en un str
char contador = 0;



/*==============================================================================
                        INTERRUPCIONES Y PROTOTIPOS
 =============================================================================*/
void setup(void);
char division (char dividendo);
char voltajes (char voltajes_1);
void setup(void);   // Defino las funciones antes de crearlas
void putch(char data); //funcion para recibir el dato que se desea transmitir
void text(void);    // Donde se introduce las cadenas de texto

void __interrupt() isr(void){
    //interrupcion del ADC para los dos pot
    if (ADIF){
        if(ADCON0bits.CHS == 0){
            ADCON0bits.CHS = 1;
            volt01 = ADRESH;
        }
        else if(ADCON0bits.CHS == 1){
            ADCON0bits.CHS = 0;
            volt02 = ADRESH; 
        }
    }
    ADIF = 0;
}

/*==============================================================================
                             LOOP PRINCIPAL
 =============================================================================*/


/*==============================================================================
                             FUNCIONES
 =============================================================================*/
void main(void){
    setup();
    Lcd_Init(); //aqui la LCD aun esta apagada
    Lcd_Clear(); //limpio lo que tenga la LCD siempre llamandolo de la lib
    char buffer[20]; //esta variable almacenara mi voltaje en un string
    char buffer1[20];
    char dato1;
    char dato; //el dato que deseo almacenar en un str
    Lcd_Set_Cursor(1,1); //ir a la primera linea en la posicion 1
    Lcd_Write_String("S_1:  S_2:  S_3:"); //imprimir los indicadores de voltaje
    
    
    
    while(1){   
   
    dato = volt01*0.0196; 
    dato1 = volt02*0.0196;
    sprintf(buffer, "%d V   ", dato); 
    sprintf(buffer1, "%d V ", dato1);
    
    Lcd_Set_Cursor(2,2); //ahora ir a la segunda linea
    Lcd_Write_String(buffer); //mostrar lo que esta en mi string anterior
    Lcd_Write_String(buffer1);
    Lcd_Write_String('  ');
    
//    Lcd_Write_String(contador);
    
    
    __delay_ms(1000); //un delay para asegurar que la busy flag permita recibir
         
    if (ADCON0bits.GO == 0){ //se apaga automaticamente entonces hay que
            __delay_us(100);     //volver a encenderlo
            ADCON0bits.GO = 1;
        }
    // Se despliega el valor del pot 1
    division(volt01);
    __delay_ms(250); //Tiempos para el despliegue de los caracteres
    printf("Valor del POT1:\r");
    __delay_ms(250);
    TXREG = centenas;
    __delay_ms(250);
    TXREG = 46;
    __delay_ms(250);
    TXREG = decenas;
    __delay_ms(250);
    TXREG = unidades;
    __delay_ms(250);
    printf("\r");
    
    // Se despliega el valor del pot 2
    division(volt02);
    __delay_ms(250); //Tiempos para el despliegue de los caracteres
    printf("Valor del POT2:\r");
    __delay_ms(250);
    TXREG = centenas;
    __delay_ms(250);
    TXREG = 46;
    __delay_ms(250);
    TXREG = decenas;
    __delay_ms(250);
    TXREG = unidades;
    __delay_ms(250);
    printf("\r");
    
    division(contador);
    Lcd_Write_Char(centenas);
    Lcd_Write_Char(decenas);
    Lcd_Write_Char(unidades);
    
    // Se pregunta si se quiere aumentar o disminuir el contador
    __delay_ms(250);
    printf("\r Si desea aumentar contador, oprima +\r");
    __delay_ms(250);
    printf("\r Si desea disminuir contador, oprima -\r");
    __delay_ms(250);
    printf("\r Si no desea realizar nada oprima *\r");
    while(RCIF == 0);
    char answer = RCREG;
    if (answer == '+'){
        contador = contador + 1;
    }
    else if (answer == '-'){
        contador = contador - 1;
    }
    else if (answer == '*'){
        NULL;
    }
    }
        
    return;
}

void putch(char data){      // Funcion especifica de libreria stdio.h
    while(TXIF == 0);
    TXREG = data; // lo que se muestra de la cadena
    return;
}

char division (char valor){
    centenas = valor/100;//esto me divide entre 100 y se queda con el entero
    residuo = valor%100; //el residuo de lo que estoy operando
    decenas = residuo/10; 
    unidades = residuo%10; //se queda con las unidades de las decenas
    //las variables estan en todo el codigo entonces no necesito el return
//    return dividendo;
    centenas = centenas + 48;
    decenas = decenas + 48;
    unidades = unidades + 48;
} 

char voltajes(char voltaje_1){
    char voltaje_a;
    return voltaje_a = division(voltaje_1);
}

/*==============================================================================
                         CONFIGURACION DEL PIC
 =============================================================================*/
void setup(void){
    //configuracion de pines para potenciometros
    ANSEL = 0b00000011;
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    
    //salidas digitales para controlar LCD
    TRISD = 0x00;
    TRISE = 0x00;
    
    
    //Configurar reloj interno
    OSCCONbits.IRCF0 = 0;        //reloj interno de 4mhz
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.SCS = 1;  //internal oscillator is used for system clock
    
    //configuracion de interrupciones
    PIE1bits.ADIE = 1;      //enable de la int del ADC
    PIR1bits.ADIF = 0;      //limpiar la interrupcion del ADC
    INTCONbits.GIE = 1;     //habilita las interrupciones globales
    INTCONbits.PEIE = 1;    //periferical interrupts
    PIE1bits.RCIE = 0;      // Interrupcion rx
    PIE1bits.TXIE = 0;      // Interrupcion TX
    
    //limpiar puertos
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;
    
//    //configuracion de ADC
    config_ADC(1);
    
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
}