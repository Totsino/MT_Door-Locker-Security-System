/*
 * CTRL_main.c
 *
 *  Created on: Oct 28, 2021
 *      Author: Youssef
 */
#include  <stdio.h>
#include "avr/io.h"
#include "uart.h"
#include "dc_motor.h"
#include "external_eeprom.h"
#include "twi.h"
#include "buzzer.h"
#include "delay.h"


/* **********************************************************************************
 *********************************************************************************** */

#define MCU1_READY 0x01
#define MCU2_READY 0x02
#define RIGHT_PASSWORD 0x03
#define WRONG_PASSWORD 0x04
#define OPEN_DOOR 0x05
#define CHANGE_PASS 0x06
#define PASSWORD_SIZE 5

/* **********************************************************************************
 *********************************************************************************** */
uint8 key;
uint8 sent_pass[PASSWORD_SIZE];
uint8 valid=0;
uint8 valid_flag=0;
uint8 password1[PASSWORD_SIZE];
uint8 password2[PASSWORD_SIZE];
uint8 fail_counter=0;
uint8 start_again=0;


/* **********************************************************************************
 *********************************************************************************** */

void Password_Check(){
while(1){   //while 1 yfdl gwa el loop tol m awl 2 pass msh zy b3d , ytl3 lma yb2o zy b3d
	for(int i=0;i<PASSWORD_SIZE;i++){
		password1[i] = UART_recieveByte();
		password2[i] = UART_recieveByte();
	}

	for(int i=0;i<PASSWORD_SIZE;i++){
		if(password2[i]==password1[i]){
			valid++;
		}
	}
		if(valid==PASSWORD_SIZE){

		UART_sendByte(RIGHT_PASSWORD);


		for(int i=0;i<PASSWORD_SIZE;i++){
			EEPROM_writeByte(0x0002+i,password1[i]);
		}

		DcMotor_Rotate(STOP);
		valid=0;
		break;


		}
		else{
		UART_sendByte(WRONG_PASSWORD);
		valid=0;

	}
}
}


/* **********************************************************************************
 *********************************************************************************** */

void Password_EEPROM(){


	for(int i=0;i<PASSWORD_SIZE;i++){
		password1[i] = UART_recieveByte();
		EEPROM_readByte(0x0002+i,&password2[i]);

	}
	for(int i=0;i<PASSWORD_SIZE;i++){
			if(password2[i]==password1[i]){
				valid++;

			}
		}
			if(valid==PASSWORD_SIZE){
			UART_sendByte(RIGHT_PASSWORD);
			valid_flag=1;
			valid=0;
		}
		else{
			UART_sendByte(WRONG_PASSWORD);
			valid_flag=0;
			valid=0;
		}
	}


int main(){

	SREG = 1<<7;
	UART_ConfigType uart2={BITS_8,DISABLED,BITS_1,9600};
	UART_init(&uart2);

	TWI_ConfigType twi={FAST,0b0000001};
	TWI_init(&twi);

	DcMotor_Init();
	Buzzer_init();


	while(UART_recieveByte() != MCU1_READY){}
	UART_sendByte(MCU2_READY);



	while(1){


		Password_Check();

		while(1){

			key= UART_recieveByte(); // OPEN THE DOOR OR CHANGE PASS // AFTER THE LAST SENT WAS right or wrong pass from first and last recieved 2 passwords

			while(1){ //while 1 httkrr f 7alt door open  aw change pass bs pass ghalat
			if (key== OPEN_DOOR){

				Password_EEPROM();
				if (valid_flag == 1){
					DcMotor_Rotate(CW);
					delay_ms(15000);
					DcMotor_Rotate(STOP);
					delay_ms(3000);
					DcMotor_Rotate(A_CW);
					delay_ms(15000);
					DcMotor_Rotate(STOP);
					fail_counter=0;
					break; //bttl3 mn el loop el talta
				}
				else{
					fail_counter++;
					if (fail_counter==3){
						Buzzer_ON();
						delay_ms(60000);
						Buzzer_OFF();
						fail_counter=0;
						break;
					}else{
						continue;
					}
					//counter to 3 and at third make buzzer
				}

			}
			else{ //recieved is to change pass
				Password_EEPROM();
				if(valid_flag == 1){
					start_again=1;
					fail_counter=0;
					break;
				}else{
					fail_counter++;
					if (fail_counter==3){
						Buzzer_ON();
						delay_ms(60000);
						Buzzer_OFF();
						fail_counter=0;
						break;
							}else{
							continue;
							}
					//counter to 3 at third make buzzer
				}

			}

			}
			if(start_again==1){
				start_again=0;
				break;
			}
		}

	}




}
