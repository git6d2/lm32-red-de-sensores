#include "soc-hw.h"

uart_t  *uart0  = (uart_t *)   0x20000000;
uart_t  *uart1 =  (uart_t *)   0x30000000;
gpio_t  *gpio0  = (gpio_t *)   0x40000000;
timer_t *timer1 = (timer_t *)  0x50000000;
timer_t *timer0 = (timer_t *)  0x60000000;


// uint32_t *sram0  = (uint32_t *) 0x40000000;

isr_ptr_t isr_table[32];

uint32_t msec = 0;
int contador;
/***************************************************************************
 * IRQ handling
 */
void isr_null()
{
}

void irq_handler(uint32_t pending)
{
        uint32_t tcr;
          uint32_t gpio;  
         uint32_t entrada;  
      
        //timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;

        
         contador=contador + 1; 
                                 
    
        tem =  timer0->counter0;
 
        uart_putchar(data); 
  
                    gpio = ((tem <= 0xBB8)&&(tem >= 0x1f40))? 1:0;  
                     data = data  + gpio;
                
                 
                   if(contador< 0x21)
                     data  = data << 1;
                       else
                         uart_putchar(tem);

                         timer0->counter0 = 0;     
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
 *Sensor functions
 */

void sensor()
{

uint32_t l,t;




t=18;                                       //milisegundos señal low  
      
gpio0->write = 0x00;                        //señal de reset
msleep(18);
gpio0->write = 0x01; 
gpio0->dir=0x00;
 

timer0->tcr0 = TIMER_EN | TIMER_IRQEN | TIMER_pin;
nsleep(160);
irq_enable();   
irq_set_mask(0x04);


} 

/***************************************************************************
 * TIMER0 Functions
 */

void msleep(uint32_t msec)
{
	uint32_t tcr;
        uint32_t tcr1;
	// Use timer0.1
	timer0->compare1 = (FCPU/1000)*msec;
	timer0->counter1 = 0;
	timer0->tcr1 = TIMER_EN;
         tcr1 = timer0->compare1;
	do {
		//halt();
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
}

uint32_t nsleep(uint32_t nsec)
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

  return timer0->counter1;
}

/***************************************************************************
 * TIMER1 Functions
 */

void m1sleep(uint32_t msec)
{
	uint32_t tcr;

	// Use timer0.1
	timer1->compare1 = (FCPU/1000)*msec;
	timer1->counter1 = 0;
	timer1->tcr1 = TIMER_EN;

	do {
		//halt();
 		tcr = timer1->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
}

/***************************************************************************
 * medicion tiempo flancos
 */

void flancopos()                                // devuelve el valor del flanco negativo
{
	uint32_t tcr;
	// Use timer0.1
	timer0->counter1 = 0;                       // pone el contador en 0 
	timer0->tcr1 = TIMER_EN;                    // habilita el timer 0 
                 
   
}
uint32_t flanconeg()                                // devuelve el valor del flanco positivo
{
	uint32_t tiempo;
	// Use timer0.1
        timer0->tcr1 = 0;                           // pone tcrq del timer 0 en cero  
       	
	return timer0->counter1;                    // devuelve el contador1 del timer0    
	
}




void tic_init()
{
	// Setup timer0.0
	timer0->compare0 = (FCPU/1000)*500;
	timer0->counter0 = 0;
	timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;
}

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

/***************************************************************************
 * GPIO Funciones pruebas
 */

void prueba()                          // Si se activa el pin6 del GPIO prenda el led1
{ 
     uint32_t out1;
     uint32_t entrada;
                          
     entrada = gpio0->read;
     uart_putstr('a');
     gpio0->write=0x00;   
                        
      if(entrada==0x40)
         {
            out1 = 0x01;
            gpio0->write = out1;                     
            msleep(100);
         }          

}

void prueba1()                         // genera un tren de pulsos flanco positivo y negativo 4 ms
{
      gpio0->write=0x00;   
      msleep(19);
      gpio0->write=0x01;
      msleep(6);
}


/***************************************************************************
 * UART Functions
 */

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

void uart_putchar1(char f) //obtener caracter de la variable 
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
}
