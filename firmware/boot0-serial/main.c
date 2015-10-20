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

	// Initialize UART

	c='u';
          x= uart_getchar();

           uart_putchar1(x);

	for(;;) {
		uint32_t start, size; 
	       c = uart_getchar();

		switch (c) {
    		case 'u': // upload 
    			uart_putstr("**tengo sueño** > \r\n");
    			break;
		case 'o': // enviar una cadena 
    			
                       uart_putstr("jajaja \r\n");
                         break;

		case 'd': // enviar un caracter
    			
				   uart_putchar('o');
    			break;
    		
                case 's' ://echo int
                           
                        uart_putchar(c);
                         break; 
              
   
		default:
			uart_putstr("**SAKC/bootloader** > \r\n");
			break;
				
		};
               
                
             
		
	}
}

