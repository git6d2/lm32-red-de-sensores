#include "soc-hw.h"

uart_t  *uart0  = (uart_t *)   0x20000000;
uart_t  *uart1 =  (uart_t *)   0x30000000;
gpio_t  *gpio0  = (gpio_t *)   0x40000000;
timer_t *timer0 = (timer_t *)  0x60000000;
// uint32_t *sram0  = (uint32_t *) 0x40000000;

isr_ptr_t isr_table[32];

uint32_t msec = 0;
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

/***************************************************************************
 * General utility functions
 */
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
/***************************************************************************
 * GPIO0 Functions
 */
void medir_flancopos()
{ 
	timer0->counter1 = 0;
	timer0->tcr1 = TIMER_EN;
}
uint32_t medir_flanconeg()
{ 
	timer0->tcr1 = 0;
	return timer0->counter1;
}
/*void tic_init()
{
	// Setup timer0.0
	timer0->compare0 = (FCPU/1000);
	timer0->counter0 = 0;
	timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;
}*/

/***************************************************************************
 * UART0 Functions
 */
void uart_init()
{
	//uart0->ier = 0x00;  // Interrupt Enable Register
	//uart0->lcr = 0x03;  // Line Control Register:    8N1
	//uart0->mcr = 0x00;  // Modem Control Register

	// Setup Divisor register (Fclk / Baud)
	//uart0->div = (FCPU/(57600*16));
}

void prueba()
{ 

		uint32_t out;
                uint32_t out1;
                uint32_t i;
                uint32_t entrada;
       
                   
                         entrada = gpio0->read;
                         uart_putstr(entrada);
                         gpio0->write=0x00;   
                        

                  if(entrada==0x40)
                      {
                        out1 = 0x01;
                       gpio0->write = out1;                     
                        msleep(100);
                       }


          
}
void prueba1()
{
                         gpio0->write=0x00;   
                         msleep(4);
                         gpio0->write=0x01;
                         msleep(4);

}
char uart_getchar()
{   
	while (! (uart0->ucr & UART_DR)) ;
	return uart0->rxtx;
}
int uart_getint()
{
 while (! (uart0->ucr & UART_DR)) ;
	return uart0->rxtx;

}

void uart_putchar1(char f) //obtener caracter de la variavle 
{
	while (uart1->ucr & UART_BUSY) ;
	uart1->rxtx = f;
}

char uart_getchar1()
{   
	while (! (uart1->ucr & UART_DR)) ;
	return uart1->rxtx;
}

void uart_putchar(char c)
{
	while (uart0->ucr & UART_BUSY) ;
	uart0->rxtx = c;
}
void uart_putint(int d)
{
	while (uart0->ucr & UART_BUSY) ;
	uart0->rxtx = d;
}

void uart_putstr(char *str)
{
	char *c = str;
	while(*c) {
		uart_putchar(*c);
		c++;
	}

/***************************************************************************
 * UART1 Functions
 */







}

