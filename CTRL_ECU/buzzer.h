/*
 * buzzer.h
 *
 *  Created on: Oct 28, 2021
 *      Author: Youssef
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#define BUZZER_PORT PORTA_ID
#define BUZZER_PIN PIN0_ID

void Buzzer_init();
void Buzzer_ON();
void Buzzer_OFF();


#endif /* BUZZER_H_ */
