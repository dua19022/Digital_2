/* 
 * File:   Lib01.h
 * Author: marco
 *
 * Created on July 19, 2021, 7:31 PM
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef xc_USART //definir nuevo nombre que el otro header para que no lo llame
#define	xc_USART //dos veces

#include <xc.h> // include processor files - each processor file is guarded.  

void Usart_con(void);

#endif	/* XC_HEADER_TEMPLATE_H */