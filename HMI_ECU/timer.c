/*
 * timer.c
 *
 *  Created on: Oct 28, 2021
 *      Author: Youssef
 */


#include "timer.h"
#include "avr/io.h"
#include "common_macros.h"
#include <avr/interrupt.h>
#include "std_types.h"


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

static volatile void (*g_callBackPtr)(void) = NULL_PTR;



/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}


ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


void TIMER_Init(const Timer_ConfigType * Config_Ptr){

	TCNT0 = Config_Ptr->initial;
	OCR0 = Config_Ptr->OCR_Value;

	TCCR0 = (1<<FOC0) | ((Config_Ptr->mode)<<WGM01) | (Config_Ptr->OCR_mode<<COM00) | (Config_Ptr->prescaler<<CS00);

	TIMSK |= (1<<OCIE0) | (1<<TOIE0);
}


void TIMER_setCallBack(void(*a_ptr)(void)){

	g_callBackPtr = a_ptr;

}



void TIMER_DeInit(){
	TCNT0 =0;
	TCCR0 =0;
	OCR0=0;
	TIMSK &= ~(1<<OCIE0) & ~(1<<TOIE0);


}
