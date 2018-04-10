#include <avr/io.h>

void timer1_init()
{
	/*
		time = ((2^16) * 64(prescaler)) / 16M = 0.262144 sec
		from 0.262144 to 3.93216 (0.262144 * 15) sec
	*/

	// CTC Mode
	TCCR1B |= (1<<WGM12);
}

void timer1_A_start()
{
	OCR1A = 0xFFFF;

	// clkI/O/64 (From prescaler)
        TCCR1B |= (1<<CS11) | (1<<CS10);

	TIMSK |= (1<<OCIE1A);
}

void timer1_B_start()
{
	OCR1B = 0xFFFF;

        // clkI/O/256 (From prescaler)
        TCCR1B |= (1<<CS11) | (1<<CS10);

        TIMSK |= (1<<OCIE1B);
}

void timer1_stop()
{
        // clkI/O/256 (From prescaler)
        TCCR1B &= ~(1<<CS12);

        TIMSK &= ~(1<<OCIE1A);
	TIMSK &= ~(1<<OCIE1B);
}

void timer0_init()
{
/*
	time = ((2^8) * 1024) / 16M = 0.016384 sec
*/
	//
	TCCR0 = 0x00;
}

void timer0_start()
{
	// clk I/O /1024 (From prescaler)
	TCCR0 |= (1<<CS02) | (1<<CS00);

	// Overflow Interrupt Enable
	TIMSK |= (1<<TOIE0);
}

void timer0_stop()
{
	// clk I/O /1024 (From prescaler)
        TCCR0 &= ~(1<<CS02);
	TCCR0 &= ~(1<<CS00);

        // Overflow Interrupt disenable
        TIMSK &= ~(1<<TOIE0);
}

void timer_init()
{
	timer1_init();
	timer0_init();
}
