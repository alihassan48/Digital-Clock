/*
 * main.c
 *
 *  Created on: Mar 18, 2017
 *      Author: Ali
 */
#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"
#include "keypad.h"
#include "lcd.h"
#include "timer.h"

volatile static uint8 hour=0;
volatile static uint8 minute=0;
volatile static uint8 second=0;
volatile uint8 p1;
volatile uint8 p2;

/*
 * ISR(TIMER) EVERY 1 SECOND
 * if second <59 second ++
 * else if(minute<59)minute ++
 * else if(hour<23)hour++
 *
 *
 * */
void display_time(void)
{
	LCD_clearScreen();
	LCD_sendCommand(CURSOR_OFF);
	if(hour<10)LCD_displayCharacter('0');
	LCD_intgerToString(hour);
	LCD_displayCharacter(':');
	if(minute<10)LCD_displayCharacter('0');
	LCD_intgerToString(minute);
	LCD_displayCharacter(':');
	if(second<10)LCD_displayCharacter('0');
	LCD_intgerToString(second);
}
void set_hour(void)
{
	p1=KeyPad_getPressedKey();
	_delay_ms(200);
	if(p1>=3)p1=0;
	LCD_sendCommand(CURSOR_ON);
	LCD_intgerToString(p1);
	p2=KeyPad_getPressedKey();
	if(p2>=4)p2=0;
	LCD_sendCommand(CURSOR_ON);
	LCD_intgerToString(p2);
	_delay_ms(200);
	hour=p1*10+p2;
}
void set_minute(void)
{
	p1=KeyPad_getPressedKey();
	_delay_ms(200);
	if(p1>=6)p1=0;
	LCD_intgerToString(p1);
	LCD_sendCommand(CURSOR_ON);
	p2=KeyPad_getPressedKey();
	if(p2>=10)p2=0;
	LCD_sendCommand(CURSOR_ON);
	LCD_intgerToString(p2);
	_delay_ms(200);
	minute=p1*10+p2;
}
void set_second(void)
{
	p1=KeyPad_getPressedKey();
	_delay_ms(200);
	if(p1>=6)p1=0;
	LCD_intgerToString(p1);
	LCD_sendCommand(CURSOR_ON);
	p2=KeyPad_getPressedKey();
	if(p2>=10)p2=0;
	LCD_sendCommand(CURSOR_ON);
	LCD_intgerToString(p2);
	_delay_ms(200);
	second=p1*10+p2;
}
void set_time(void)
{
	cli();
	//LCD_clearScreen();
	LCD_goToRowColumn(1,0);
	LCD_displayString("00:00:00");
	LCD_goToRowColumn(1,0);
	LCD_sendCommand(CURSOR_ON);
	set_hour();
	LCD_goToRowColumn(1,3);
	set_minute();
	LCD_goToRowColumn(1,6);
	set_second();
	display_time();
	sei();
}
void adjust_time(void)
{
	if(second<59)
	{
		second++;
	}
	else if(minute<59)
	{
		if(second==59)second=0;
		minute++;
	}
	else if(hour<23)
	{
		if(minute==59)minute=0;
		hour++;
	}
	display_time();
}
ISR(TIMER1_COMPA_vect)
{
	cli();
	adjust_time();
	sei();
}

int main()
{
	LCD_init();
	Timer_Init();
	sei();
	uint8 pressed;
	//sei();
	//LCD_displayString("1:set time");
	//LCD_displayStringRowColumn(1,0,"2:display time");
	display_time();
	while(1)
	{
		pressed=KeyPad_getPressedKey();
		_delay_ms(200);
		if(pressed == 1)
		{
			set_time();
		}


	}
	return 0;
}

