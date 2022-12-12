/*
 * dc_motor.c
 *
 *  Created on: Oct 9, 2021
 *      Author: Youssef
 */


#include "dc_motor.h"
#include "gpio.h"
#include <avr/io.h>


void DcMotor_Init(void){

	//setting up pin directions

	GPIO_setupPinDirection(PORTB_ID, PIN6_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID, PIN7_ID , PIN_OUTPUT);


	// initially DC motor at stop state
	GPIO_writePin(PORTB_ID, PIN6_ID, LOGIC_LOW);
	GPIO_writePin(PORTB_ID, PIN7_ID, LOGIC_LOW);


}

void DcMotor_Rotate(DcMotor_State state){

	switch(state){
	case STOP:
		GPIO_writePin(PORTB_ID, PIN6_ID, LOGIC_LOW);
		GPIO_writePin(PORTB_ID, PIN7_ID, LOGIC_LOW);
		break;
	case CW:
		GPIO_writePin(PORTB_ID, PIN6_ID, LOGIC_HIGH);
		GPIO_writePin(PORTB_ID, PIN7_ID, LOGIC_LOW);
		break;
	case A_CW:
		GPIO_writePin(PORTB_ID, PIN6_ID, LOGIC_LOW);
		GPIO_writePin(PORTB_ID, PIN7_ID, LOGIC_HIGH);
		break;
	}



}


