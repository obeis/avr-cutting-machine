#include <avr/io.h>
#include "motor.h"

void motor_init()
{
	MOTOR_DDR |= (1<<PMA) | (1<<PMB) | (1<<PMC) | (1<<PMD);
}

void motor_A_on()
{
	MOTOR_PORT |= (1<<PMA);
}

void motor_A_off()
{
	MOTOR_PORT &= ~(1<<PMA);
}

void motor_B_on()
{
	MOTOR_PORT |= (1<<PMB);
}

void motor_B_off()
{
	MOTOR_PORT &= ~(1<<PMB);
}

void motor_C_on()
{
	MOTOR_PORT |= (1<<PMC);
}

void motor_C_off()
{
	MOTOR_PORT &= ~(1<<PMC);
}

void motor_D_on()
{
	MOTOR_PORT |= (1<<PMD);
}

void motor_D_off()
{
	MOTOR_PORT &= ~(1<<PMD);
}

void motor_all_stop()
{
	MOTOR_PORT &= ~(1<<PMA);
	MOTOR_PORT &= ~(1<<PMB);
	MOTOR_PORT &= ~(1<<PMC);
	MOTOR_PORT &= ~(1<<PMD);
}
