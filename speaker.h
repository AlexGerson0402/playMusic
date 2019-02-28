#ifndef SPEAKER_H_
#define SPEAKER_H_

#include "gpio.h"
#include <inttypes.h>
#include <stdio.h>

//constants
#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830
#define RCC_APB1ENR (volatile uint32_t*) 0x40023840
#define GPIOB_EN 1<<1
#define GPIOA_EN 0b1
#define GPIOC_EN 0b100

//music notes
#define	C5	523
#define	Db5	554
#define	D5	587
#define	Eb5	622
#define	E5	659
#define	F5	698
#define	Gb5	739
#define	G5	783
#define	Ab5	830
#define	LA5	880
#define	Bb5	932
#define	B5	987
#define	C6	1046


typedef struct {
	int freq;
	int ms;
}noteTime;

typedef struct{
	uint32_t CR1;
	uint32_t CR2;
	uint32_t SMCR;
	uint32_t DIER;
	uint32_t SR;
	uint32_t EGR;
	uint32_t CCMR1;
	uint32_t CCMR2;
	uint32_t CCER;
	uint32_t CNT;
	uint32_t PSC;
	uint32_t ARR;
	uint32_t reserved0;
	uint32_t CCR1;
	uint32_t CCR2;
	uint32_t CCR3;
	uint32_t CCR4;
	uint32_t reserved1;
	uint32_t DCR;
	uint32_t DMAR;
	uint32_t tim2OR;
	uint32_t tim5OR;
}TIMx;

//function declarations

void speaker_init();
//Initialize the appropriate timer/counter to connect
//to the piezo speaker and configure in a mode to play tones.

//Create a structure that has at least two elements
//one element to represent the frequency of a note
//(could be frequency, could be a character ‘a’,’b’,’c’
//with another element for octave, etc.)
//and one element to represent duration.


//traverse noteTime array and play it
void play(noteTime* musicP, int numNotes);

void playNote(int freq);

void playReverse(noteTime* musicP, int numNotes);

void testSpeaker();

#endif
