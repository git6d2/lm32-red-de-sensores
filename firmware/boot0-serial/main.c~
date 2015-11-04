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

       
	uint32_t x=1;
	uint8_t  c;
        uint32_t  flag;
        uint32_t pruebah=0;
        uint32_t hbe=0;                          //el enable ha sido activado
        uint32_t x1=0;                           // valor del contador en segundos flanco positivo
        uint32_t x2=0;                           // valor del contador en segundos flanco negativo
        uint32_t tiempo;                         // valor del contador
        uint32_t i=0;
 
	c='u';                                   // Initialize UART

	
        m1sleep(1);                              //prueba con el timer1 



        //gpio0->dir=0x0F;                       // dirección GPIO
        gpio0->dir=0xFF;                         
        gpio0->write = 0x40;                     // escritura GPIO    
        msleep(100);                             // milisegundos timer0
        sensor();                                // lectura del sensor   
   
       
for(;;)                                           // prueba lectura del tiempo de duracion flanco positivo
{
 flag=gpio0->read;
 if(hbe==0 && (flag == 0x80)){
        
        pruebah=flancopos();
        x2=(pruebah*1000)/(FCPU);                  // se convierte el valor del contador a milisegundos;     
	uart_putchar(x1);
	hbe=1;
       
  }
  if(hbe==1 && !(flag == 0x80)){
  

  	tiempo=flanconeg();
        x1=(tiempo*1000)/(FCPU);                  // se convierte el valor del contador a milisegundos;     
	uart_putchar(x1);
        hbe=0;
      
  }	
	
}
 
     //uint32_t  tiempos= nsleep(1); 
                            
               
      /*  if(tiempos  == 0x186a0)                  // Prueba devuelve el contador1 del timer0
         { 
                   uart_putchar(tiempos);          // mostrar por UART el valor del contador
                   uart_putchar(tiempos>>8);                     
                   uart_putchar(tiempos>>16);
                   uart_putchar(tiempos>>24); 
                   }*/


     /*for(;;)
      prueba(); // se usa para probar la lectura del GPIO */         
	
  
     /*for(;;)
   {
      uart_putchar(uart_getchar1()); // prueva del ECHO  de funcionamiento de la UART 1 a la UART2

     }*/
	
}
