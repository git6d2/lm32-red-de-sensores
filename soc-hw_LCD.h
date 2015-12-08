typedef struct {
	volatile uint8_t LCD_DB;
	volatile uint8_t LCD_RS;
	volatile uint8_t LCD_E;
} lcd_t;
void init_lcd(void);
void lcd_putchar2 (uint8_t dato);
void lcd_putchar (uint8_t dato, uint8_t addr);
void lcd_command (uint8_t inst);
void lcd_putstr(char *str, uint8_t addr);
