/*
 * timer.h
 *
 *  Created on: Oct 28, 2021
 *      Author: Youssef
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

typedef enum{
	DISABLE,TOGGLE,CLEAR,SET
}Compare_Output_Mode;

typedef enum{
	OVF,CTC
}Timer_Mode;


typedef enum{
	NO_CLOCK,FCPU,FCPU_8,FCPU_64,FCPU_256,FCPU_1024
}Timer_Prescaler;


typedef struct
{
	Compare_Output_Mode OCR_mode;
	Timer_Mode mode;
	uint8 initial;
	uint8 OCR_Value;
	Timer_Prescaler prescaler;

}Timer_ConfigType;

#endif /* TIMER_H_ */


void TIMER_Init(const Timer_ConfigType * Config_Ptr);
void TIMER_setCallBack(void(*a_ptr)(void));
void TIMER_DeInit();
