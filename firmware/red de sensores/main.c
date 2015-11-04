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
// Función principal del codigo - obtener informacion del xbe, a traves del usuario
//**************************************************************************************************


int main()
{
                   
                   uint32_t  x,x1, infosensores; 
    
                   uart_putstr("0. modo sleep");         
                   uart_putstr("1. desea iniciar la comunicacion "); 
                  
                   x=uart_getchar();    
                   uar_putchar1(x);
                   uart_putstr("seleccion datos sensados"); 
                   uart_putstr("0. ninguno"); 
                   uart_putstr("1. temperatura");         
                   uart_putstr("2. humedad ");
                   uart_putstr("3.temperatura y humedad ");

                   x1=uart_getchar();    
                   uar_putchar1(x1);
                   uart_putstr("informacion tiempo real ");
 

              
                   infosensores=uart_getchar1() 
                  
                

      
	
  
     /*for(;;)
   {
      uart_putchar(uart_getchar1()); // prueva del ECHO  de funcionamiento de la UART 1 a la UART2

     }*/
	
}
