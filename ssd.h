#ifndef _SSD_H_
#define _SSD_H_

#define SSD_DDR_Data	DDRC
#define SSD_PORT	PORTC

extern uint8_t ssd[2];

void ssd_init();
void ssd_run();
void ssd_time(uint8_t n);
void ssd_delay(uint8_t n);

#endif
