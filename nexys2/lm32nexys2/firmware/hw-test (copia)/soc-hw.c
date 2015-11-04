//////////////////////////////////////////////////////////////////////
////                                                              ////
////  soc-hw.c                                                    ////
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

// Direcciones de los perifericos utilizados

uart_t  *uart0  = (uart_t *)   0x20000000;
timer_t *timer0 = (timer_t *)  0x30000000;
gpio_t  *gpio0  = (gpio_t *)   0x40000000;
spi_t   *spi0   = (spi_t *)    0x50000000;

isr_ptr_t isr_table[32];

void tic_isr();
/***************************************************************************
 * IRQ handling
 */
void isr_null()
{
}

void irq_handler(uint32_t pending)
{
	int i;

	for(i=0; i<32; i++) {
		if (pending & 0x01) (*isr_table[i])();
		pending >>= 1;
	}
}

void isr_init()
{
	int i;
	for(i=0; i<32; i++)
		isr_table[i] = &isr_null;
}

void isr_register(int irq, isr_ptr_t isr)
{
	isr_table[irq] = isr;
}

void isr_unregister(int irq)
{
	isr_table[irq] = &isr_null;
}

//**************************************************************************
// Estructura del periferico SPI
//**************************************************************************

void spi_init(uint32_t constdiv)
{

	spi0->DEVIDE = constdiv; // Definición de la frecuencia del reloj sclk
	
	// Parametros iniciales del registro de control
	spi0->CTRL |= 0x0A << CHAR_LEN; 
	spi0->CTRL |= 0x00 << GO_BSY;
	spi0->CTRL |= 0x00 << Rx_NEG;
	spi0->CTRL |= 0x00 << Tx_NEG;
	spi0->CTRL |= 0x00 << LSB;
	spi0->CTRL |= 0x00 << IE;
	spi0->CTRL |= 0x00 << ASS;
}

uint32_t spi_readByte(uint8_t cs){
	spi0->SS = cs; // Selección del esclavo al cual se le va a pedir información
	spi0->CTRL |= EN << GO_BSY; // Señal ENABLE para inicio de lectura
	while((spi0->CTRL >> GO_BSY) & EN);
	spi0->SS = 0;
	return spi0->RxTx0; //Retorno de información por el registro RXTX0
	
}

//*************************************************************************
// Estructura del periferico GPIO
//*************************************************************************

void gpio_init()
{
	gpio0->dir=0x0ff;
}

uint8_t gpio_read()
{
	return gpio0->read;
}


//***************************************************************************
// Estructura del periferico TIMER 
//**************************************************************************

void msleep(uint32_t msec)
{
	uint32_t tcr;

	// Use timer0.1
	timer0->compare1 = (FCPU/1000)*msec;
	timer0->counter1 = 0;
	timer0->tcr1 = TIMER_EN;

	do {
		//halt();
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
}

void nsleep(uint32_t nsec)
{
	uint32_t tcr;

	// Use timer0.1
	timer0->compare1 = (FCPU/1000000)*nsec;
	timer0->counter1 = 0;
	timer0->tcr1 = TIMER_EN;

	do {
		//halt();
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
}


uint32_t tic_msec;

void tic_isr()
{
	tic_msec++;
	timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;
}

void tic_init()
{
	tic_msec = 0;

	// Setup timer0.0
	timer0->compare0 = (FCPU/10000);
	timer0->counter0 = 0;
	timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;

	isr_register(1, &tic_isr);
}


//***************************************************************************
// Estructura del periferico UART 
//***************************************************************************
void uart_init(){}

char uart_getchar()
{   
	while (! (uart0->ucr & UART_DR)) ;
	return uart0->rxtx;
}

void uart_putchar(char c)
{
	while (uart0->ucr & UART_BUSY) ;
	uart0->rxtx = c;
}

void uart_putstr(char *str)
{
	char *c = str;
	while(*c) {
		uart_putchar(*c);
		c++;
	}
}

