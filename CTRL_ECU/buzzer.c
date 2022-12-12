/*
 * buzzer.c
 *
 *  Created on: Oct 28, 2021
 *      Author: Youssef
 */


#include "buzzer.h"
#include "gpio.h"
#include <avr/io.h>



void Buzzer_init(){

	GPIO_setupPinDirection(BUZZER_PORT,BUZZER_PIN,PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN , LOGIC_LOW);
}


void Buzzer_ON(){

	GPIO_writePin(BUZZER_PORT, BUZZER_PIN , LOGIC_HIGH);

}

void Buzzer_OFF(){

	GPIO_writePin(BUZZER_PORT, BUZZER_PIN , LOGIC_LOW);

}
