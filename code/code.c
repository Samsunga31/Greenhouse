/*
 * code.c
 *
 * Created: 14-03-2022 17:31:04
 *  Author: kunal Avghade
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include "LCD.h"
#include "ADC.h"

#define TEMP 0
#define MOSIT 1

#define MOTOR 5
#define FAN 6
#define BUZZ 7
#define MODE PINB0
#define WATER_SW PINB1
#define LCD_SW PINB2
#define FAN_SW PINB3


int main(void)
{
	char Msg[10];
	DDRB = 0xf0;
	//DDRB &= ~((1<<MODE)|(1<<WATER_SW)|(1<<LCD_SW)|(1<<FAN_SW));
	lcd_init();
	lcd_print(1,0,"INITIALIZING..");
	acd_init();
    while(1)
    {
		if ((PINB & (1 << PINB0))==(1 << PINB0))
		{
			if ((PINB & (1 << WATER_SW))==(1 << WATER_SW))
			{
				PORTB|=(1<<MOTOR);
				_delay_ms(200);
				PORTB &= ~(1<<MOTOR);
			}
			
			if ((PINB & (1 << FAN_SW))==(1 << FAN_SW))
			{
				PORTB |=(1<<FAN);
				_delay_ms(200);
				PORTB &= ~(1<<FAN);
			}
			
			if ((PINB & (1 << LCD_SW))==(1 << LCD_SW))
			{
				lcd_clear();
				sprintf(Msg,"MOISTURE: %d",getMoisture(MOSIT));
				lcd_print(1,0,Msg);
				sprintf(Msg,"TEMPERATURE: %d",getTemp(TEMP));
				lcd_print(2,0,Msg);
				_delay_ms(100);
			}
			
			if (getMoisture(MOSIT) < 50)
			{
				PORTB |=(1<<BUZZ);
				_delay_ms(1000);
				PORTB &= ~(1<<BUZZ);
			}
			
			if (getTemp(TEMP) > 40)
			{
				PORTB |=(1<<BUZZ);
				_delay_ms(1000);
				PORTB &= ~(1<<BUZZ);
			}
			lcd_clear();
		}
		if ((PINB & (1 << PINB0))!=(1 << PINB0))
		{
			if (getMoisture(MOSIT) < 50)
			{
				PORTB |=(1<<MOTOR);
			}
			
			if (getMoisture(MOSIT) > 80)
			{
				PORTB &= ~(1<<MOTOR);
			}
			
			if (getTemp(TEMP) > 40)
			{
				PORTB |=(1<<FAN);
			}
			
			if (getTemp(TEMP) < 20)
			{
				PORTB &= ~(1<<FAN);
			}
			lcd_clear();
			sprintf(Msg,"MOISTURE: %d",getMoisture(MOSIT));
			lcd_print(1,0,Msg);
			sprintf(Msg,"TEMPERATURE: %d",getTemp(TEMP));
			lcd_print(2,0,Msg);
			_delay_ms(50);
		}	
    }
}