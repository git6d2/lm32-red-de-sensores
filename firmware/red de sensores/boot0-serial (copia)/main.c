/**
 * Primitive first stage bootloader 
 *
 *
 */
#include "soc-hw.h"

int main()
{
	//uint32_t x=1;
	//uint8_t  c;
        //uint8_t  flag;

	// Initialize UART

	//c='u';
uart_putchar('i');

//gpio0->dir=0x0F;

uint32_t tiempo;
uint32_t hbe=0;  //el enable ha sido activado
gpio0->dir=0x0F;


uint32_t flag;

while(1)
{
uart_putstr("Entró al while");
 flag=gpio0->read;
 if(hbe==0 && (flag & 0x40)){
	medir_flancopos();
	hbe=1;
	uart_putstr("Entró al primer if");
  }
  if(hbe==1 && !(flag & 0x40)){
  	tiempo=medir_flanconeg();
	hbe=0;
	uart_putstr("Entró al segundo if");
  }	
uart_putstr("La duración del pulso es" + tiempo);	
}




	
}
