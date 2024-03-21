#include "ATMEGA2560.h"
#include "Interrupt.h"

#define DEBOUNCE_DELAY 100	//100ms delay

uint32_t previousButtonTime = 0;	//Previous button time

void ButtonPressed();		//

int main(void) {			//main, runs all the time
	
	milliseconds_init();
	
	DDRA = 0xFF;
	AttachInterrupt(INT0, RISING, &ButtonPressed);		//Go to function AttachInterrupt with using PD0/INT0 as the analog pin Reader, RISING as the Interrupt Mode, 
	
	while (1) {}
	return 1;
	
}

void ButtonPressed() {		// Function ButtonPressed, runs all the time
	
	uint32_t currentButtonTime = milliseconds_now();
	if (currentButtonTime - previousButtonTime < DEBOUNCE_DELAY) {return;}		//Debouce Routine, 100ms delay needed. Otherwise Break and Exits Function
	previousButtonTime = currentButtonTime;										//Updates the previousButtonTime to current time ( milliseconds_now() )
	
	if (PORTA == 0) {
		PORTA = 1;
	}
	else {
		PORTA = 0;
	}
	
}