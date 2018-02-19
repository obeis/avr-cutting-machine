#define F_CPU	16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "int.h"
#include "timer.h"
#include "ssd.h"
#include "eeprom.h"
#include "motor.h"

uint8_t time_ee  EEMEM = 7;
uint8_t delay_ee EEMEM = 4;

volatile uint8_t time;
volatile uint8_t delay;

int main()
{
	int_init();
	ssd_init();
	timer_init();
	motor_init();

	time  = eeprom_read_byte(&time_ee);
	delay = eeprom_read_byte(&delay_ee);

	back:

	ssd_time(time);
	ssd_delay(delay);

	while(1)
	{
		ssd_run();

		if(PIND & (1<<PD6))
			break;
	}

	ssd_p_mode();
	ssd_t_mode();

	while(1)
        {
		_delay_ms(250);

                if(PIND & (1<<PD7))
                {
                        if(time > 9 | time == 9)
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
                        if(delay > 9 | delay == 9)
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

}

ISR(INT1_vect)
{

}

ISR(INT2_vect)
{

}
