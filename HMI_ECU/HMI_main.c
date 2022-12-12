/*
 * HMI_main.c
 *
 *  Created on: Oct 28, 2021
 *      Author: Youssef
 */

#include  <stdio.h>
#include "avr/io.h"
#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include "delay.h"

#define PASSWORD_SIZE 5
#define MCU1_READY 0x01
#define MCU2_READY 0x02
#define RIGHT_PASSWORD 0x03
#define WRONG_PASSWORD 0x04
#define OPEN_DOOR 0x05
#define CHANGE_PASS 0x06

/* ********************************************************************************** */
/* ********************************************************************************** */

uint8 password1[PASSWORD_SIZE];
uint8 password2[PASSWORD_SIZE];
uint8 key;
uint8 valid_flag=0;
uint8 pass_counter=0;
uint8 fail_counter=0;
uint8 start_again=0;



/* ********************************************************************************** */
/* ********************************************************************************** */

void Second_Password();
void Sending_Password();
void Main_Screen();


/* ********************************************************************************** */
/* ********************************************************************************** */


void Start_Screen(void){

	LCD_displayStringRowColumn(0,0,"Welcome To Door Lock System...");
	delay_ms(3000);



}
/* ********************************************************************************** */
/* ********************************************************************************** */


void First_Password(void){
	pass_counter=0;
	LCD_displayStringRowColumn(0,0,"Enter New Password:               ");
	LCD_moveCursor(1,0);

	while(1){


			 key = KEYPAD_getPressedKey();
			delay_ms(500);

			if( (key >= 0) && (key <= 9) ){


					password1[pass_counter]=key;
					LCD_displayCharacter('*');
					pass_counter++;

				}
			if (pass_counter == PASSWORD_SIZE){
				do{
				key = KEYPAD_getPressedKey();
				delay_ms(500);
				}while(key != '=');
				Second_Password();
				break;
			}
		}


}

/* ********************************************************************************** */
/* ********************************************************************************** */

void Second_Password(){
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Re-enter Password:            ");
	LCD_moveCursor(1,0);
	pass_counter=0;


	while(1){


			 key = KEYPAD_getPressedKey();
			delay_ms(500);

			if( (key >= 0) && (key <= 9) ){


					password2[pass_counter]=key;
					LCD_displayCharacter('*');
					pass_counter++;

				}
			if (pass_counter == PASSWORD_SIZE){
				do{
				key = KEYPAD_getPressedKey();
				delay_ms(500);
				}while(key != '=');
				Sending_Password();
				break;
			}
		}

}

/* ********************************************************************************** */
/* ********************************************************************************** */


void Sending_Password(){



		/* Send the required string to MC2 through UART */
		for(int i = 0;i<PASSWORD_SIZE;i++){
			UART_sendByte(password1[i]);
			UART_sendByte(password2[i]);
		}



}

/* **********************************************************************************
 *********************************************************************************** */

void ChangePassword(){


	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Enter Password:             ");
	LCD_moveCursor(1,0);
	pass_counter=0;


	while(1){

	 key = KEYPAD_getPressedKey();
	delay_ms(500);

	if( (key >= 0) && (key <= 9) ){


			password1[pass_counter]=key;
			LCD_displayCharacter('*');
			pass_counter++;

		}
	if (pass_counter == PASSWORD_SIZE){
		do{
		key = KEYPAD_getPressedKey();
		delay_ms(500);
		}while(key != '=');
		pass_counter = 0;
		for(int i = 0;i<PASSWORD_SIZE;i++){
			UART_sendByte(password1[i]);
		}
			if (UART_recieveByte() == RIGHT_PASSWORD ){
				LCD_clearScreen();
				fail_counter=0; //nsfr el fail counter
				LCD_displayStringRowColumn(0,0,"Right Password");
				delay_ms(3000);
				start_again=1;
				break;

			}else{


				fail_counter++;
				if (fail_counter == 3){
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"WARNING, 3 FAIL ATTEMPTS");
					delay_ms(60000);
					fail_counter =0;
					break;
				}else{
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"Wrong Password, Enter Again");
					LCD_moveCursor(1,0);
				continue;
				}

			}



		break;
	}

	}

}


/* **********************************************************************************
 *********************************************************************************** */

void OpenTheDoor(){

	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Enter Password:");
	LCD_moveCursor(1,0);
	pass_counter=0;


	while(1){

	 key = KEYPAD_getPressedKey();
	delay_ms(500);

	if( (key >= 0) && (key <= 9) ){


			password1[pass_counter]=key;
			LCD_displayCharacter('*');
			pass_counter++;

		}
	if (pass_counter == PASSWORD_SIZE){
		do{
		key = KEYPAD_getPressedKey();
		delay_ms(500);
		}while(key != '=');
		pass_counter = 0;
		for(int i = 0;i<PASSWORD_SIZE;i++){
			UART_sendByte(password1[i]);
		}
			if (UART_recieveByte() == RIGHT_PASSWORD ){
				LCD_clearScreen();
				fail_counter=0; //nsfr el fail counter
				LCD_displayStringRowColumn(0,0,"Door is Unlocking");
				delay_ms(33000);

			}else{


				fail_counter++;
				if (fail_counter == 3){
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"WARNING, 3 FAIL ATTEMPTS");
					delay_ms(60000);
					fail_counter=0;
					break;
				}else{
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"Wrong Password, Enter Again");
					LCD_moveCursor(1,0);
				continue;
				}

			}



		break;
	}

	}
}


/* **********************************************************************************
 *********************************************************************************** */

void Main_Screen(){

	LCD_clearScreen();
	while(1){
		if(start_again==1){
			start_again=0;
			break;
		}
	LCD_displayStringRowColumn(0,0,"'+':Open The Door         ");
	LCD_displayStringRowColumn(1,0,"'-':Change Password");


	do{
	 key = KEYPAD_getPressedKey();
	delay_ms(500);
	}while(key != '+' && key != '-');


	if(key == '+'){

		UART_sendByte(OPEN_DOOR);
		OpenTheDoor();
	}
	else if(key == '-'){
		UART_sendByte(CHANGE_PASS);
		ChangePassword();

	}


	}
}




int main(void){

	SREG=1<<7;

	LCD_init();


	UART_ConfigType uart1={BITS_8,DISABLED,BITS_1,9600};
	UART_init(&uart1);
	UART_sendByte(MCU1_READY);
	/* Wait until MC2 is ready to receive the string */
	while(UART_recieveByte() != MCU2_READY){}


	Start_Screen();




	while(1){


		First_Password();

		valid_flag=UART_recieveByte();
		if(valid_flag==RIGHT_PASSWORD){
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"VALID PASSWORD");
			delay_ms(5000);
			Main_Screen();
		}
		else if(valid_flag==WRONG_PASSWORD){
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"INVALID PASSWORD");
			delay_ms(5000);
		}


	}
}


