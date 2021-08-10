#define _XTAL_FREQ 4000000


#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pic16f887.h> 
#include "ADC.h" //esta es la libreria que estamos utilizando
#define _XTAL_FREQ 4000000

void ADC_config(char frec) { //en este caso para seleccionar la frecuencia ADC
    switch(frec){
        case 0: //FOSC/2
            ADCON0bits.CHS = 0;     //canal 0
            __delay_us(100);
    
            ADCON0bits.ADCS0 = 0;   //para que el clock select sea FOSC/
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

/*******************************************************************************
 * Funciones para conversión del ADC 
 ******************************************************************************/
void ADC_convert(char *data,float a, int place) 
{
     int temp=a;
     float x=0.0;
     int digits=0;
     int i=0,mu=1;
     int j=0;
     if(a<0)
     {
            a=a*-1;
            data[i]='-';
            i++;
      }
     //exponent component
     while(temp!=0)
     {
         temp=temp/10;
         digits++;          
     }
     while(digits!=0)
     {
         if(digits==1)mu=1;
         else  for(j=2;j<=digits;j++)mu=mu*10;
         
         x=a/mu;
         a=a-((int)x*mu);
         data[i]=0x30+((int)x);
         i++;
         digits--;
         mu=1;
     }
     //mantissa component
     data[i]='.';
     i++;
     digits=0;
     for(j=1;j<=place;j++)mu=mu*10;
     x=(a-(int)a)*mu; //shift places
     a=x;
     temp=a;
     x=0.0;
     mu=1;
     digits=place;
     while(digits!=0)
     {
         if(digits==1)mu=1;
         else  for(j=2;j<=digits;j++)mu=mu*10;
         
         x=a/mu;
         a=a-((int)x*mu);
         data[i]=0x30+((int)x);
         i++;
         digits--;
         mu=1;
     }   
     
    data[i]='\n';
}

