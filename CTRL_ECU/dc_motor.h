/*
 * dc_motor.h
 *
 *  Created on: Oct 9, 2021
 *      Author: Youssef
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_


#include "std_types.h"

typedef enum
{
	STOP,CW,A_CW
}DcMotor_State;


void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state);


#endif /* DC_MOTOR_H_ */
