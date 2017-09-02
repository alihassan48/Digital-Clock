/*
 * timer.c
 *
 *  Created on: Mar 19, 2017
 *      Author: Ali
 */

#include "timer.h"

void Timer_Init(void)
{
	SET_BIT(TIMSK,OCIE1A);

	TCCR1A = (1<<COM1A1) | (1<<FOC1A) | (1<<WGM12);
	TCCR1B = (1<<CS11) ;
	OCR1AH = 0Xff;
	OCR1AL = 0xff;
}


