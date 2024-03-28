#include "ATMEGA2560.h"

int time = 0;

int main(void) {
	
	
	TCCR0B = 0b00000101;
	TCCR0A = 0b00000000;
	
	TIMSK0 = 0b00000001;
	TIFR0 = 0b00000001;
	//lcd_init();
	

	serial0_init();
	
	while(1)  {
		
		/*
		char lcd_top_line[16];
		//char lcd_bottom_line[16];
		sprintf(lcd_top_line, "Time: %d", time); // The %04d is for printng as a 4 digit number
		//sprintf(lcd_bottom_line, "Range: %03d%s", rangeInt, "mm"); // The %03d if for printin a 3 digit number and the %s is for the mm unts
		
		lcd_goto(0); //Put cursor at position 0
    	lcd_home(); // same as lcd_goto(0);
		lcd_puts(lcd_top_line); //Print string to LCD first line
		//lcd_goto(0x40); //Put cursor to first character on second line
		//lcd_puts(lcd_bottom_line);
		*/
		

		TIFR0 = 1;
		
	}
	
	return 1;
}


ISR (TIMER0_OVF_vect) {
	
//	time += 1;
	debug_int("Time", TCNT0);
	
}