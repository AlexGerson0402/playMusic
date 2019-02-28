/*
 * main.c
 *
 *  Starter Code
 */
//Lab6 play a tune
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "uart_driver.h"
#include "led.h"
#include "lcd.h"
#include "delay.h"
#include "keypad.h"
#include "ADC.h"
#include "speaker.h"

#define F_CPU 16000000UL
//systick addr already defined in delay.h
#define SYSTICK_BASE 0XE000E010

//file static variables
static noteTime music[] = {{C5,200},{G5,200},
		{D5,300},{Ab5,250},{G5,400},{Eb5,500},
{B5,450},{LA5,600},{C6,700},{E5,300},{Db5,250},
{Gb5,500},{Bb5,400},{F5,400}};

//exit condition
static bool proceed = true;
static char message0[] = "A - play song";
static char message1[] = "B - play reverse";
static char message2[] = "C - menu";
static char message3[] = "D - exit";
//function declarations
//user selection
void menu();

// main
int main(){
	//init_usart2(19200,F_CPU);

	init_led();
	lcd_init();
	key_init();
	lcd_clear();
	lcd_home();
	speaker_init();

	//console application that will present
	//a menu to the user.
	menu();
	//testSpeaker();
	while(proceed){
		char sel = 'A';
		sel = key_noblock();
		switch(sel){
			case 'A':
			led_allOff();
			play(music, (int)sizeof(music));
			break;
			case 'B':
			led_allOn();
			playReverse(music, (int)sizeof(music));
			break;
			case 'C': led_allOff();
				menu();
			break;
			case 'D': proceed = false;
			break;
			default:
			led_allOff();
			play(music, (int)sizeof(music));
			break;
		}
	}//while

	return 0;
}//main

//access timer/counter registers via a struct
//created to match register layout.

//user selection
void menu(){
	lcd_clear();
	lcd_home();
	lcd_print_string(message0);
	lcd_set_position(1,0);
	lcd_print_string(message1);
	//wait half second
	delay_1ms(500);
	lcd_clear();
	lcd_home();
	lcd_print_string(message2);
	lcd_set_position(1,0);
	lcd_print_string(message3);
	//wait half second
	delay_1ms(500);
	lcd_clear();
}



