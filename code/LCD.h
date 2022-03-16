/*
 * LCD.h
 *
 * Created: 14-03-2022 17:33:21
 *  Author: kunal Avghade
 */ 


#ifndef LCD_H_
#define LCD_H_

void lcd_cmd(unsigned char cmd)
{
	PORTC = 0b10000000;
	PORTD = cmd;
	_delay_ms(10);
	PORTC = 0b00000000;
}

void lcd_data(unsigned char msg)
{
	PORTC = 0b10100000;
	PORTD = msg;
	_delay_ms(10);
	PORTC = 0b00100000;
}

void lcd_init()
{
	DDRC = 0xFF;
	DDRD = 0xFF;
	lcd_cmd(0x38);
	lcd_cmd(0x0E);
	lcd_cmd(0x06);
	lcd_cmd(0x01);
	lcd_cmd(0x80);
}

void lcd_clear()
{
	lcd_cmd(0x01);
}

void lcd_print(unsigned char row, unsigned char col, char *msg)
{
	if(row == 1)
		row = 0x80;
	else
		row = 0xC0;
	
	lcd_cmd(row|col);
	
	while (*msg)
	{
		lcd_data(*msg);
		msg++;
	}
		
}

#endif /* LCD_H_ */