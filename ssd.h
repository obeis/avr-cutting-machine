#ifndef _SSD_H_
#define _SSD_H_

#define SSD_DDR_Data	DDRC
#define SSD_PORT	PORTC
#define SSD_DDR_one	DDRA
#define SSD_DDR_two	DDRA
#define SSD_PORT_c	PORTA
#define P_SSD_one	PA7
#define P_SSD_two	PA6

extern uint8_t ssd[2];

void ssd_init();
void ssd_on_one();
void ssd_off_one();
void ssd_on_two();
void ssd_off_two();
void ssd_scanning();
void ssd_time(uint8_t n);
void ssd_delay(uint8_t n);

#endif
