#include "ATMEGA2560.h"
//include this .c file's header file
//#include "Controller.h"

int main(void) {
	
	//variable declaration
	char lcd_string[33] = {0}; //declare and initiate string for LCD

	//initiation section, runs once
	adc_init();
	lcd_init();

	_delay_ms(20);
	uint16_t variableToPrint;
	
	//main loop
	while(1)
	{
		//code goes here



	}
	return 1;
	//end main
}