//////////////////////////////////////////////////////////////////////
////                                                              ////
////  main.c                                                      ////
////                                                              ////
////  Este archivo hace parte del trabajo realizado para el       ////
////  proyecto de curso de Electronica Digital II		  ////
////  Universidad Nacional de Colombia - 2015    		  ////
////  					                          ////
////                                                              ////
////  Autores:                                                    ////
////      - Miguel Beltran                          		  ////
////      - Wilson Rojas                                          ////
////      - Camilo Cortez                                         ////
////                                                              ////
////  Información adicional en: 				  ////
////  https://sites.google.com/site/edigital2unal/proyectos/      ////
////  	                                                          ////
////                                                              ////
//////////////////////////////////////////////////////////////////////
////                                                              ////
//// Copyright (C) 2015 Authors                                   ////
////                                                              ////
//// This source file may be used and distributed without         ////
//// restriction provided that this copyright statement is not    ////
//// removed from the file and that any derivative work contains  ////
//// the original copyright notice and the associated disclaimer. ////
////                                                              ////
//// This source file is free software; you can redistribute it   ////
//// and/or modify it under the terms of the GNU Lesser General   ////
//// Public License as published by the Free Software Foundation; ////
//// either version 2.1 of the License, or (at your option) any   ////
//// later version.                                               ////
////                                                              ////
//// This source is distributed in the hope that it will be       ////
//// useful, but WITHOUT ANY WARRANTY; without even the implied   ////
//// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR      ////
//// PURPOSE.  See the GNU Lesser General Public License for more ////
//// details.                                                     ////
////                                                              ////
//////////////////////////////////////////////////////////////////////


/**
 * Primitive first stage bootloader 
 *
 *
 */
#include "soc-hw.h"

//**************************************************************************************************
// Función principal del codigo - se obtiene el valor del tiempo, del flanco positivo
//**************************************************************************************************



int main()
{

        
	uint32_t gpio=0;
	uint8_t  c;
        uint32_t  flag;
        uint32_t pruebah=0;
        uint32_t hbe=0;                          //el enable ha sido activado
        uint32_t x1=0;                           // valor del contador en segundos flanco positivo
        uint32_t x2=0;                           // valor del contador en segundos flanco negativo
        uint32_t tiempo;                         // valor del contador
        uint32_t i=0;
 
	c='u';                                   // Initialize UART
        gpio0->dir=0x00; 
    

	//for(;;)
        //prueba();
      
	
        irq_enable();
        irq_set_mask(0x02);
       
    /*    if (1800 < tem <2100)
          gpio=1;
         else
          gpio=0;
      
        data = data<<1 + gpio;

        uart_putchar(data);    */  
}
