#include "ATMEGA2560.h"	// This used to be "Robot.h", changed it to "ATMEGA2560.h" because that header file is suitable for everything with the ATMEGA2560, not just robots
#include "Interrupt.h"	// Simplifies the interrupt code

#define DEBOUNCE_DELAY 100 // Debounce of 100ms


void ButtonPressed();	// C requires you to declare files before you refrence them, not a problem if you put void ButtonPressed() before int main() but here were not doing that

int main(void) {
	
	milliseconds_init();	// Start recording time
	
	DDRA = 0xFF;	// Set all the pins on Port A to output
	AttachInterrupt(INT0, RISING, &ButtonPressed);	// See Interrupt.h
	
	while (1) {}
	return 1;
	
}

uint32_t previousButtonTime = 0;
void ButtonPressed() {
	
	uint32_t currentButtonTime = milliseconds_now();	// Find current time
	if (currentButtonTime - previousButtonTime < DEBOUNCE_DELAY) {return;}	// If the last time the button was pressed was sooner than 100ms ago, ignore the button press (Ignores button bounce)
	previousButtonTime = currentButtonTime;
	
	PORTA ^= 1;	// Toggle the 1st pin on Port A
	
}