#include "ATMEGA2560.h"

// Im not sure why this one is a default Robot.c
int main(void) {
	
	DDRA = 0xFF;
	PORTA = 0; 
	while(1)  {

		PORTA ^= 1;
		_delay_ms(500);
	}
	
	return 1;
}