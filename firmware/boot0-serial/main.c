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
        uint32_t  flag;

	// Initialize UART

	c='u';






uint32_t pruebah=0;
uint32_t hbe=0;  //el enable ha sido activado
uint32_t x1=0;
uint32_t tiempo;

gpio0->dir=0x0F;
   
       // uart_putchar(0xFF);
        uint32_t  tiempos= nsleep(1); 
         uint32_t i=0;  

        x1=(tiempos*1000)/(FCPU);   

                
               
      /*  if(tiempo  == 0x186a0)
         { 
                   uart_putchar(tiempo);
                   uart_putchar(tiempo>>8);
                   uart_putchar(tiempo>>16);
                   uart_putchar(tiempo>>24); 
                   }*/

      uart_putchar(x1);
          
while(1)
{
 flag=gpio0->read;
 if(hbe==0 && (flag == 0x40)){
         uart_putchar('g');
       	flancopos();
	hbe=1;
        prueba();
  }
  if(hbe==1 && !(flag == 0x40)){
  	tiempo=flanconeg();
	hbe=0;

        uart_putchar(tiempo);
      
  }	
	
}


//for(;;)
//prueba();
	
  /*for(;;)
{
  uart_putchar(uart_getchar1());

}*/
	
}
