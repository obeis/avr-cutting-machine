#include <avr/io.h>
#include "int.h"

void int_init()
{
	// INT0 (PD2), INT1(PD3), INT(PB2) input
	DDRD |= (1<<PD2) | (1<<PD3);
	DDRB |= (1<<PB2);

	// rising edge of INT0,1,2
	MCUCR |= (1<<ISC11) | (1<<ISC10) | (1<<ISC01) | (1<<ISC00);
	MCUCSR |= (1<<ISC2);

	// INT1 INT0 INT2 interrupt enable
	GICR |= (1<<INT1) | (1<<INT0) | (1<<INT2);
}

void int_disable()
{
	// INT1 INT0 INT2 interrupt disable
	GICR &= ~(1<<INT0);
	GICR &= ~(1<<INT1);
	GICR &= ~(1<<INT2);
}
