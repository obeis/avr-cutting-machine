#ifndef _MODE_H_
#define _MODE_H_

extern volatile uint8_t mode;

void auto_mode_init();
void manual_mode_init();
void auto_mode();
void manual_mode();
void port_init();

#endif
