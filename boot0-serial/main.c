/**
 * Primitive first stage bootloader 
 *
 *
 */
#include "soc-hw.h"

int main()
{
	uint32_t x=1;
	uint8_t  c;
        uint8_t  flag;

	// Initialize UART

	c='u';
uart_putchar('i');

gpio0->dir=0x0F;



uint32_t tiempo;
uint32_t hbe=0;  //el enable ha sido activado
gpio0->dir=0x0F;

while(1)
{
 flag=gpio0->read;
 if(hbe==0 && (flag & 0x80)){
        uart_putchar('b');
	flancopos();
	hbe=1;
  }
  if(hbe==1 && !(flag & 0x80)){
  	tiempo=flanconeg();
	hbe=0;
        uart_putchar('a');
        uart_putchar(tiempo & 0xFF);
        uart_putchar(tiempo >> 8 & 0xFF);
        uart_putchar(tiempo >> 16 & 0xFF); 
        uart_putchar(tiempo >> 24 & 0xFF); 

  }	
 uart_putchar('c');	
}



//for(;;)
//prueba();
	
  /*for(;;)
{
  uart_putchar(uart_getchar1());

}*/
	
}
