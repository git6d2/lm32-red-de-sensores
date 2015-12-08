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
////      - Andrés Mondragón (afmondragonc@unal.edu.co)		  ////
////      - Sthefania Moreno (stmorenore@unal.edu.co)             ////
////      - Luis Antonio Rodriguez (luiarodriguezper@unal.edu.co) ////
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


#include "soc-hw.h"






//**************************************************************************************************
// Función principal del codigo - Inicialización de SPI y lectura //
//**************************************************************************************************
int main()
{
uint32_t out;

gpio0->dir=0x0F;
uart_putstr("inicia gpio");
//for(;;)
//prueba();
	

		
}
