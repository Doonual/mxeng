#include "ATMEGA2560.h"
#include "Interrupt.h"



volatile bool freeze = false;

int32_t min = 0;
int32_t sec = 0;
int32_t ms = 0;

//bool readingRange = true;

void FreezeVal();

int main(void) {
	
	lcd_init();
	char lcd_string[32] = {};
	//initiation section, runs once
	cli();
	TCCR1A = 0;
	TCCR1B = (1<<WGM12); //CTC mode 4
	TCNT1 = 0; //reset timer to 0
	
	TIMSK1 |= (1<<OCIE1A); //Output Compare Interrupt Enable 1 A
	TCCR1B |= (1<<CS10); //set prescaler to 1024, starting timer
	
	OCR1A = 15999; //generate an interrupt once per millisecond
	sei(); // enable global interrupts


	AttachInterrupt(INT0, FALLING, &FreezeVal);


	while (true) {
		lcd_home();
		sprintf(lcd_string, " %u", ms);
		lcd_puts(lcd_string);
	}
return(0);
}

void FreezeVal() {
	freeze = !freeze;


}

ISR(TIMER1_COMPA_vect)
	{
		ms++;
	}	
	


	/*Lab 4 codes
	_delay_ms(20);
	uint16_t range_raw;
	
	char lcd_top_line[16];
	char lcd_bottom_line[16];
	
	//AttachInterrupt(INT0, FALLING, &FreezeRangeVal);
	
	//main loop
	while (true) {
		

		if (readingRange == true) {
			range_raw = adc_read(PORTF0);
		}
		
		float rangeVal = (float)(range_raw - range_min) / (range_max - range_min);
		rangeVal = fmax(fmin(1.0, rangeVal), 0.0);
		
		int rangeInt = rangeVal * (mm_max - mm_min) + mm_min;

		
		
		sprintf(lcd_top_line, "Range raw: %04d", range_raw);
		sprintf(lcd_bottom_line, "Range: %03d%s", rangeInt, "mm");
		
		//code goes here
		lcd_goto(0);      //Put cursor at position 0
    	lcd_home();       // same as lcd_goto(0);
		lcd_puts(lcd_top_line); //Print string to LCD first line
		lcd_goto(0x40);     //Put cursor to first character on second line
		lcd_puts(lcd_bottom_line);
		

	}
	return 1;
	//end main
}

void FreezeRangeVal() {
	readingRange = !readingRange;
}*/
