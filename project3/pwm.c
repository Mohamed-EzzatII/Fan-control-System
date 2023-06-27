#include"pwm.h"
#include<avr/io.h>

void PWM_Timer0_Start(uint8 set_duty_cycle)
{

	/*Initialize timer(optional)*/
	TCNT0 = 0;

	/* Compare value*/
	OCR0  = set_duty_cycle;

	/* PB3(OC0) is output where we will get the PWM signal*/
	DDRB  = DDRB | (1<<PB3);

	/* TCCR0 register : -
	 * 1 - FOC0=0         : Fast PWM mode
	 * 2 - WGM 01:00=11   : Fast PWM Mode
	 * 3 - COM 01:00 = 10 : non inverted mode
	 * 4 - CS02:00 = 010  : Prescaler = 8
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}
