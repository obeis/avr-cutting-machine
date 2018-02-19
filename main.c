#define F_CPU	16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "timer.h"
#include "ssd.h"
#include "eeprom.h"

uint8_t time_ee  EEMEM = 5;
uint8_t delay_ee EEMEM = 7;

volatile uint8_t time;
volatile uint8_t delay;

int main()
{
	ssd_init();

	time  = eeprom_read_byte(&time_ee);
	delay = eeprom_read_byte(&delay_ee);

	ssd_time(time);
	ssd_delay(delay);

	while(1)
	{
		//ssd_scanning();

		PORTC = ssd[1];
	}
}
