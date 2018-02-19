#define F_CPU	16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "ssd.h"

uint8_t ssd[2];

void ssd_init()
{
	SSD_DDR_Data = 0xFF;
}

void ssd_run()
{
	// t
	SSD_PORT = 0b11000011;
	_delay_ms(1000);
	SSD_PORT = ssd[0];
        _delay_ms(1000);
	// d
	SSD_PORT = 0b11101001;
	_delay_ms(1000);
	SSD_PORT = ssd[1];
        _delay_ms(1000);
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
                case 5: ssd[0] = 0b01100111; break;
                case 6: ssd[0] = 0b11100111; break;
                case 7: ssd[0] = 0b00101100; break;
                case 8: ssd[0] = 0b11101111; break;
                case 9: ssd[0] = 0b01101111; break;
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
        }
}
