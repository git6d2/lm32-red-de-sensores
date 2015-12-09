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


//********************************************************************************************
// Función de lectura de SPI, lectura de GPIO, y envío de información por UART
//********************************************************************************************

void midi(int cs)
{
	uint32_t b[80], max=0; 
	int i, sel_p, nota;
	uint8_t instr;
	
	for (i=0;i<=79;i++) // Captura de información proveniente de ADC en vector de 80 posiciones
	{
		b[i]=spi_readByte(cs);
	        nsleep(100); 
	}
	for (i=0;i<=79;i++) // Busqueda del valor maximo de la señal recibida, determina el velocity en el mensaje MIDI
	{
		if(b[i] > max)
		    
		max=b[i];
		 
	}
	instr = gpio_read(); // Lectura de GPIO para determinación de instrumento musical

// El controlador cuenta con dos modos: 1) Modo Bateria, 2) Modo General MIDI

// El Modo Bateria asigna el canal 10 para el envío de información y sonidos de bateria 
// El modo General MIDI asigna el canal 1 para el envío de información y notas musicales de la octava 3
// Para ambos modos se utiliza una funciónde corrección que permite ajustar la sensibilidad de los piezoelectricos (i.e. max=max*k)

	if (instr > 127) 
	{
		if (cs==1)
		{
		 sel_p = 35; // Bombo
		 max=max*4; 
		}
		if (cs==2)
		{
		 sel_p = 38; // Redoblante 
		max=max*4;
		}
		if (cs==4)
		{
		 sel_p = 49; // Hi-Hat 
		 max=max*4;
		}
		if (cs==8)
		{
		 sel_p = 42; // Crash 
		max=max*12;
		}
		if (max>127)
		{
		max=127;
		}

// El mensaje MIDI cuenta con dos partes: 1)Mensaje de activación de nota, 2) Mensaje de descativación de nota

		//Mensaje de activación de nota
		uart_putchar(153); //Activacion de nota por canal 10
		uart_putchar(sel_p); // Selección de sección de bateria (bombo, redoblante, platillo, etc)
		uart_putchar(max); //Velocity del golpe
		msleep(20);
		// Mensaje de desactivacion de nota
		uart_putchar(137); //Activacion de nota pr canal 10
		uart_putchar(sel_p); // Selección de sección de bateria
		uart_putchar(0); //Velocity del golpe
	}
	if (instr <= 127) // Indica que es un instrumento General MIDI (Envio por el canal 1) - Notas de la octava 3
	{	
		if (cs==1)
		{
		 nota = 72; // DO 
		 max=max*4;
		}
		if (cs==2)
		{
		 nota = 74; // RE 
		 max=max*4;
		}
		if (cs==4)
		{
		 nota = 76; // MI 
		max=max*4;
		}
		if (cs==8)
		{
		 nota = 77; // FA
		max=max*12; 
		}
		if (max>127)
		{
		max=127;
		}
		// Mensaje cambio de intrumento
		uart_putchar(192);
		uart_putchar(instr);
		// Mensaje Activación de Nota Musical
		uart_putchar(144);
		uart_putchar(nota);
		uart_putchar(max);
		msleep(250);
		// Mensaje de desactivacion de nota
		uart_putchar(128);
		uart_putchar(nota);
		uart_putchar(0);

	}
		
}

//**************************************************************************************************
// Función principal del codigo - Inicialización de SPI y lectura //
//**************************************************************************************************
int main()
{	
	uint32_t a1, a2, a3, a4; // Cuatro esclavos (ADC) son seleccionados
	int j; 
	
	spi_init(255); // Constante de división para generación de reloj del SPI - Freq(sclk)=192KHz
	for(;;)
	{	nsleep(100);
		//Ciclo de Lectura de SPI para los cuatro esclavos
		//Si el valor de lectura equivale a un valor decimal mayor a 5 (aproximadamente 65mV)
		//Se ingresa a la función MIDI para captura de información, analisis, y envío. 

		for (j=0;j<=3;j++)
		{
			if(j==0)
			{
				a1=spi_readByte(1);	
				if(a1>5) 
				midi(1);
			}
			if(j==1)
			{
				a2=spi_readByte(2);	
				if(a2>5) 
				midi(2);
			}

			if(j==2)
			{
				a3=spi_readByte(4);		
				if(a3>5) 
				midi(4);
			}

			if(j==3)
			{
				a4=spi_readByte(8);		
				if(a4>5) 
				midi(8);
			}


			
		}
                 	
}
	 











		
}
