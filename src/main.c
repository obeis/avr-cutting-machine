#define F_CPU	16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "int.h"
#include "timer.h"
#include "ssd.h"
#include "motor.h"
#include "mode.h"

uint8_t time_ee  EEMEM = 3;
uint8_t delay_ee EEMEM = 2;

volatile uint8_t time;
volatile uint8_t delay;

/*
	F,B
	F = front vector
	B = behind vector
*/
volatile char motor_vector_C_D = 'F';

uint8_t tca = 0, tcb = 0, t0 = 0, tssd = 0, mssd = 0;

int main()
{
	int_init();
	ssd_init();
	timer_init();
	motor_init();
	port_init();

	time  = eeprom_read_byte(&time_ee);
	delay = eeprom_read_byte(&delay_ee);

	back:

	ssd_time(time);
	ssd_delay(delay);

	sei();

	ssd_timer_run();


	if(mode == 0)
		goto manual_mode;
	else if(mode == 1)
		goto auto_mode;


	manual_mode:

	manual_mode_init();

	sei();

	// manual loop
        while(1)
        {
		manual_mode();

		scan_switch();

		if(PINB & (1<<PB3))
		{
			cli();
			motor_all_stop();
			_delay_ms(350);
                	goto auto_mode;
		}

		if(PIND & (1<<PD6))
        	{
                	cli();
                	motor_all_stop();
                	goto programming_mode;
        	}
        }

	auto_mode:

	auto_mode_init();

	sei();

	// auto loop
	while(1)
	{
		auto_mode();

		scan_switch();

		if(PINB & (1<<PB3))
		{
			cli();
                        motor_all_stop();
			_delay_ms(350);
			goto manual_mode;
		}

		if(PIND & (1<<PD6))
                {
                        cli();
                        motor_all_stop();
                        goto programming_mode;
                }
	}

	// Programming Mode
	programming_mode:

	ssd_p_mode();
	ssd_t_mode();

	while(1)
        {
		_delay_ms(250);

                if(PIND & (1<<PD7))
                {
                        if(time > 15 | time == 15)
                                time = 0;
                        else
                                time++;
                }

		ssd_time(time);
                ssd_display_time();

                if(PIND & (1<<PD6))
                        break;
        }

	ssd_d_mode();

	while(1)
        {
		 _delay_ms(250);

                if(PIND & (1<<PD7))
                {
                        if(delay > 15 | delay == 15)
                                delay = 0;
                        else
                                delay++;
                }

		ssd_delay(delay);
                ssd_display_delay();

                if(PIND & (1<<PD6))
                        break;
        }

	eeprom_write_byte(&time_ee, time);
        eeprom_write_byte(&delay_ee, delay);

	ssd_fp_mode();

	goto back;
}

ISR(INT0_vect)
{
	motor_B_off();

	if(motor_vector_C_D == 'F')
		motor_C_on();
	else if(motor_vector_C_D == 'B')
		motor_D_on();

	timer1_A_start();

	timer0_start();
}

ISR(INT1_vect)
{
	motor_A_off();

	if(motor_vector_C_D == 'F')
                motor_C_on();
        else if(motor_vector_C_D == 'B')
                motor_D_on();

	timer1_B_start();

	timer0_start();
}

ISR(INT2_vect)
{
	if(motor_vector_C_D == 'F')
		motor_vector_C_D = 'B';
	else if(motor_vector_C_D == 'B')
		motor_vector_C_D = 'F';

	motor_C_off();
        motor_D_off();
}

/*
	INT0
*/
ISR(TIMER1_COMPA_vect)
{
	if(tca == delay || tca > delay)
	{
		motor_A_on();

		timer1_stop();

		tca = 0;
	}
	else
		tca++;
}

/*
	INT1
*/
ISR(TIMER1_COMPB_vect)
{
	if(tcb == delay || tcb > delay)
        {
		motor_B_on();

		timer1_stop();

		tcb = 0;
	}
	else
		tcb++;
}

ISR(TIMER0_OVF_vect)
{
	/*
		time = ((2^8) * 1024) / 16M = 0.016384 sec
		0.016384 * 15 = 0.24576 sec
		from 0.24576 to 3.6864 (0.24576 * 15) sec
	*/
	if(t0 == (time*15) || t0 > (time*15))
	{
		motor_C_off();
		motor_D_off();

		timer0_stop();

		t0 = 0;
	}
	else
		t0++;
}

ISR(TIMER2_OVF_vect)
{
	/*
		time = ((2^8) * 1024) / 16M = 0.016384 sec
                0.016384 * 65 = 1.06496 sec
	*/
	if(tssd == 65 || tssd > 65)
	{
		mssd++;

		if(mssd == 1)
		{
			// t
        		SSD_PORT = 0b11000011;
		}
		else if(mssd == 2)
		{
			SSD_PORT = ssd[0];
		}
		else if(mssd == 3)
		{
			// d
        		SSD_PORT = 0b11101001;
		}
		else if(mssd == 4)
		{
			SSD_PORT = ssd[1];
		}

			tssd = 0;

		if(mssd == 4 || mssd > 4)
			mssd = 0;
	}
	else
		tssd++;
}
