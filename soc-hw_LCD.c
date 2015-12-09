#include "soc-hw.h"

uart_t   *uart0  = (uart_t *)   0xF0000000;
timer_t  *timer0 = (timer_t *)  0xF0010000;
gpio_t   *gpio0  = (gpio_t *)   0xF0020000;
lcd_t    *lcd0   = (lcd_t *)    0xF0030000;
ps2_t    *ps20   = (ps2_t *)    0xF0040000;
// uint32_t *sram0  = (uint32_t *) 0x40000000;

uint32_t msec = 0;




/***************************************************************************
 * LCD functions
 */
void init_lcd(void){

   	delay(750000); // Wait 15 ms or longer.
        lcd0->LCD_DB=0x30;    
	lcd0->LCD_E=1;
	lcd0->LCD_RS = 0;//wm
  	delay(12);
   	lcd0->LCD_E=0;
   
   	delay(205000); // Wait 4.1 ms or longer, which is 205,000 clock cycles at 50 MHz.
      	lcd0->LCD_DB=0x30;    
   	lcd0->LCD_E=1;
	lcd0->LCD_RS = 0;//wm
   	delay(2000);
   	lcd0->LCD_E=0;
   
	delay(5000); //Wait 100 μs or longer.
	lcd0->LCD_DB=0x30;    
	lcd0->LCD_E=1;
	lcd0->LCD_RS=0;
 	delay(2000);
  	lcd0->LCD_E=0;

   
	delay(2000); //Wait 40 μs.
	lcd_command(0x38);  // function set. 8-bit interface, 2 line mode, 5x8 dot format
	delay(1000);
	lcd_command(0xE);  // Display On/Off & Cursor. Display on, Cursor underline on, Cursor blink on
	delay(1000);
	
//--end init_lcd function.

}

void lcd_command (uint8_t inst){
  
	lcd0->LCD_DB = 0x01;        // erase data
	lcd0->LCD_DB = inst;        
    	lcd0->LCD_RS = 0;           // RS instruccion
    	lcd0->LCD_E=1;              // E up
	delay(12);              // Wait	240ns
	lcd0->LCD_E=0;          // E down
    	delay(100);                    // Wait 2us

    	lcd0->LCD_DB = 0x01;           // erase data
    	lcd0->LCD_DB = inst & 0xFF;    // Lower 4 bits
    	lcd0->LCD_RS = 0;              // RS down
    	lcd0->LCD_E=1;                 // E up
    	delay(12);                     // Wait 240ns
    	lcd0->LCD_E=0;                 // E down

    	if(inst==0x01) delay(82000);   // clear display 1640 micro segundos  (Execution Time: 82 μs – 1.64 ms)
    	else delay(2000);              // Wait 40 μs
//---END lcd_command function
}


void lcd_putchar (uint8_t dato, uint8_t addr){
        
	lcd_command(addr);
	lcd0->LCD_DB = 0x01;           // erase data
	lcd0->LCD_DB = dato;           
	lcd0->LCD_RS = 1;              // RS up Dato
	lcd0->LCD_E=1;                 // E up
	delay(12);                     // Wait 240ns
	lcd0->LCD_E=0;                 // E down

	delay(100);                    // Wait 2us

	lcd0->LCD_DB = 0x01;           // erase data
	lcd0->LCD_DB = dato & 0xFF;    
	lcd0->LCD_RS = 1;              // RS up
	lcd0->LCD_E=1;                 // E up
	delay(12);                     // Wait 240ns
	lcd0->LCD_E=0;                 // E down

	delay(2000);                   // Wait 40 μs
}

void lcd_putchar2 (uint8_t dato){
    //NOTA: los tiempos minimos E='1' 230ns, 4bit-4-bit 1us, dato-dato 40us

    lcd0->LCD_DB = 0x01;           // erase data
    lcd0->LCD_DB = dato;        // 
    lcd0->LCD_RS = 1;              // RS up
    lcd0->LCD_E=1;                 // E up
    delay(12);                     // Wait 240ns
    lcd0->LCD_E=0;                 // E down

    delay(100);                    // Wait 2us

    lcd0->LCD_DB = 0x01;           // erase data
    lcd0->LCD_DB = dato & 0xFF;    
    lcd0->LCD_RS = 1;              // RS up
    lcd0->LCD_E=1;                 // E up
    delay(12);                     // Wait 240ns
    lcd0->LCD_E=0;                 // E down

    delay(2000);                   // Wait 40 μs
}


void lcd_putstr(char *str, uint8_t addr)
{
  char *c = str;
  while(*c) {
    lcd_putchar2(*c);
    c++;
    addr++;
  }
}
