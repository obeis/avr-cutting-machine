#include <avr/io.h>
#include <util/delay.h>
#include "int.h"
#include "timer.h"
#include "motor.h"

uint8_t mode = 0;
/*
	0 = manual mode
	1 = auto mode
*/

/*
	* programming mode swith
        PD6 = programming mode start switch
        PD7 = change time switch

	* manual control switch
        PD0 = motor A (PA1)
        PD1 = motor b (PA2)
        PD4 = motor c (PA3)
        PD5 = motor d (PA4)

        PB0 = output PA5
        PB1 = output PA6
        PB3 = auto start switch
	PA7 = auto mode LED
*/

void port_init()
{
	DDRA |= (1<<PA7) | (1<<PA6) | (1<<PA5);

	DDRB &= ~(1<<PB0);
	DDRB &= ~(1<<PB1);

	DDRD &=~ (1<<PD0);
	DDRD &=~ (1<<PD1);
	DDRD &=~ (1<<PD4);
	DDRD &=~ (1<<PD5);
	DDRD &=~ (1<<PD6);
	DDRD &=~ (1<<PD7);
}

void auto_mode_init()
{
	mode = 1;

	int_init();

	timer_0_1_enable();

	// led on
	PORTA |= (1<<PA7);

	motor_A_on();
}

void manual_mode_init()
{
	mode = 0;

	int_disable();

	timer_0_1_disble();

	motor_all_stop();

	// led off
        PORTA &= ~(1<<PA7);
}

void manual_mode()
{
	// manual control switch
	if(PIND & (1<<PD0))
	{
		motor_all_stop();
		motor_A_on();
        }
	else
		motor_A_off();

        if(PIND & (1<<PD1))
        {
		motor_all_stop();
		motor_B_on();
        }
	else
		motor_B_off();

        if(PIND & (1<<PD4))
        {
		motor_all_stop();
		motor_C_on();
        }
	else
		motor_C_off();

        if(PIND & (1<<PD5))
        {
		motor_all_stop();
		motor_D_on();
        }
	else
		motor_D_off();

/*
	if(PINB & (1<<PB0))
	{

	}

	if(PINB & (1<<PB1))
	{

	}
*/
}

void auto_mode()
{

}
