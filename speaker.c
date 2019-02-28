#include <inttypes.h>
#include <stdio.h>
#include "gpio.h"
#include "keypad.h"
#include "lcd.h"
#include "string.h"
#include "delay.h"
#include "speaker.h"

static volatile GPIO* GPIOA = 0x40020000;
static volatile GPIO* GPIOB = 0x40020400;
static volatile GPIO* GPIOC = 0x40020800;
static volatile TIMx* TIM3 = 0x40000400;


void speaker_init(){
//Initialize the appropriate timer/counter to connect
//to the piezo speaker and configure in a mode to play tones.
	//PB4 RCC enable
	*RCC_AHB1ENR |= GPIOB_EN;
	//TIM3 clock enable
	*RCC_APB1ENR |= 0b10;
	//alternate function mode
	GPIOB->MODER &= ~(0b11)<<8;
	GPIOB->MODER |= (0b10)<<8;
	//AF2
	GPIOB->AFRL &= ~(0b1111)<<16;
	GPIOB->AFRL |= (0b0010)<<16;
}

void play(noteTime* musicP, int numNotes){
	//traverse noteTime array and play it
	for(int i=0; i<numNotes; i++){
		//dummy method for tone test;
		playNote(musicP[i].freq);
		delay_1ms(musicP[i].ms);
	}
}

void playNote(int freq){
	//1. SET CLOCK, default prescaler
	//2. write # of ticks to ARR CCR-CCR
	uint32_t ticks = (uint32_t) 8000000/freq;
	TIM3->ARR = ticks;
	TIM3->CCR1 = ticks;
	//3. set CCxIE and/or DE, no interrupt
	//4. select output mode - toggle
	//OCIM=011-TOGGLE ON MATCH
	TIM3->CCMR1 &= ~(0b111)<<4;
	TIM3->CCMR1 |= (0b011)<<4;
	//compare output enable CC1E=1
	TIM3->CCER = 1;
	//5. enable counter CEN=1
	TIM3->CR1 = 1;
}

void playReverse(noteTime* musicP, int numNotes){
	for(int i=numNotes; i>=0; i--){
			//dummy method for tone test;
			playNote(musicP[i].freq);
			delay_1ms(musicP[i].ms);
		}
}

void testSpeaker(){
	for(int i=200;i<2000;i+=200){
		playNote(i);
		delay_1ms(1500);
	}
}
