/*
 *
 * Module: DELAY
 *
 * File Name: delay.c
 *
 * Description: Source file for delay module.
 *
 * Author: Youssef Hussien
 *
 */


/***********************************************************************
 *                      Include Module header file                      *
 ***********************************************************************/
#include "delay.h"



/***********************************************************************
 *              Include the other required header files                 *
 ***********************************************************************/
#include "common_macros.h"
#include "timer.h"


/***********************************************************************
 *                            Global Variables                          *
 ***********************************************************************/
static uint32 g_timerTick = 0;
static uint8 g_secTick =0;


/***********************************************************************
 *                      Local Functions Prototypes                      *
 ***********************************************************************/

static void timerTick( void );


/***********************************************************************
 *                          Functions Definitions                       *
 ***********************************************************************/

static void timerTick( void )
{
	g_secTick++;
	if(g_secTick== MS_FACTOR){
		g_timerTick++;
		g_secTick=0;
	}


}



void delay_ms( uint32 ms )
{
	g_timerTick = 0;


	Timer_ConfigType config = {DISABLE,CTC,0,250,FCPU_8};
	TIMER_Init(&config);
	TIMER_setCallBack(timerTick);
	/* Busy wait for n ms. */
	while( g_timerTick< ms );
	TIMER_DeInit();
}

