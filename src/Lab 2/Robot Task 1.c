#include "ATMEGA2560.h"	// Gives us access to the functions of the ATMEGA2560

int axisPin = 0;	// Which of the joystick axes are we currently showing

bool prevButtonState;	//
bool buttonState;

int main(void) {
	DDRA = 0xFF;
	PORTA = 0;
	
	adc_init();
	
	while (true) {
		
	uint16_t analogButton = adc_read(2);
	prevButtonState = buttonState;
	buttonState = analogButton < 6;
	
	if (buttonState == true && prevButtonState == false) {
		axisPin = axisPin == 0 ? 1 : 0;
	}
	
	uint16_t analogInput = adc_read(axisPin);
	int amnt = 8 * analogInput / 1023;		//amount of leds
	
	PORTA = 0;
	for (int i = 0; i < 8; i ++) {
		
		if (i >= amnt) {break;}
		PORTA |= (1 << i);
		
	}
	
	_delay_ms(16);
	
	
	}
	
	return 1;
	
}