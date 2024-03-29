#define F_CPU	16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "timer.h"
#include "ssd.h"

uint8_t ssd[2];

void ssd_init()
{
	SSD_DDR_Data = 0xFF;
}

void ssd_time(uint8_t n)
{
        switch(n)
        {
                case 0: ssd[0] = 0b11101110; break;
                case 1: ssd[0] = 0b00101000; break;
                case 2: ssd[0] = 0b11001101; break;
                case 3: ssd[0] = 0b01101101; break;
                case 4: ssd[0] = 0b00101011; break;
                case 5:	ssd[0] = 0b01100111; break;
                case 6:	ssd[0] = 0b11100111; break;
                case 7: ssd[0] = 0b00101100; break;
                case 8: ssd[0] = 0b11101111; break;
                case 9: ssd[0] = 0b01101111; break;
		case 10: ssd[0] = 0b10101111; break;		// a
		case 11: ssd[0] = 0b11100011; break;		// b
		case 12: ssd[0] = 0b11000110; break;		// c
		case 13: ssd[0] = 0b11101001; break;		// d
		case 14: ssd[0] = 0b11000111; break;		// e
		case 15: ssd[0] = 0b10000111; break;		// f
        }
}

void ssd_delay(uint8_t n)
{
        switch(n)
        {
                case 0: ssd[1] = 0b11101110; break;
                case 1: ssd[1] = 0b00101000; break;
                case 2: ssd[1] = 0b11001101; break;
                case 3: ssd[1] = 0b01101101; break;
                case 4: ssd[1] = 0b00101011; break;
                case 5: ssd[1] = 0b01100111; break;
                case 6: ssd[1] = 0b11100111; break;
                case 7: ssd[1] = 0b00101100; break;
                case 8: ssd[1] = 0b11101111; break;
                case 9: ssd[1] = 0b01101111; break;
		case 10: ssd[1] = 0b10101111; break;		// a
		case 11: ssd[1] = 0b11100011; break;		// b
		case 12: ssd[1] = 0b11000110; break;		// c
		case 13: ssd[1] = 0b11101001; break;		// d
		case 14: ssd[1] = 0b11000111; break;		// e
		case 15: ssd[1] = 0b10000111; break;		// f
        }
}


void ssd_timer_run()
{
	timer2_init();
}

void ssd_p_mode()
{
	// P
        SSD_PORT = 0b10001111;
        _delay_ms(3000);
}

void ssd_display_time()
{
        SSD_PORT = ssd[0];
}

void ssd_display_delay()
{
        SSD_PORT = ssd[1];
}

void ssd_t_mode()
{
	// t
        SSD_PORT = 0b11000011;
        _delay_ms(1000);
}

void ssd_d_mode()
{
        // d
	SSD_PORT = 0b11101001;
        _delay_ms(1000);
}

void ssd_fp_mode()
{
	// F
	SSD_PORT = 0b10000111;
	_delay_ms(1000);

	// P
        SSD_PORT = 0b10001111;
        _delay_ms(3000);
}
