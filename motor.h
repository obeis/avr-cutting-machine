#ifndef _MOTOR_H_
#define _MOTOR_H_

#define MOTOR_DDR	DDRA
#define MOTOR_PORT	PORTA
#define PMA		PA1
#define PMB		PA2
#define PMC		PA3
#define PMD		PA4

void motor_init();
void motor_A_on();
void motor_A_off();
void motor_B_on();
void motor_B_off();
void motor_C_on();
void motor_C_off();
void motor_D_on();
void motor_D_off();

#endif
