#include "ATMEGA2560.h"
#include "Interrupt.h"

#define DEBOUNCE_PERIOD 100
uint32_t currentMs = 0;

volatile bool freeze = false;

uint32_t min = 0;
uint32_t sec = 0;
uint32_t ms = 0;



//bool readingRange = true;

void FreezeVal();
void Reset();

int main(void) {
	
	lcd_init();
	serial0_init();
	milliseconds_init();
	
	DDRD = 0b00000000;
	PORTD = 0b00000011;
	
	
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
	AttachInterrupt(INT1, FALLING, &Reset);


	while (true) {
		
		
		lcd_home();
		
		char lcd_string[32];
		
		int minutes = ms / 1000 / 60;
		int seconds = (ms / 1000) % 60;
		int milliseconds = ms % 1000;
		
		sprintf(lcd_string, "%d m %d.%03d s                     ", minutes, seconds, milliseconds);
		lcd_puts(lcd_string);
		lcd_goto(0x40);
		lcd_puts("                     ");
		
		_delay_ms(50);
		debug_int("Time", ms);
		
		
	}
	
	
return(0);
}

void FreezeVal() {
	if (milliseconds_now() - currentMs < DEBOUNCE_PERIOD) {return;}
	currentMs = milliseconds_now();
	freeze = !freeze;
}
void Reset() {
	if (milliseconds_now() - currentMs < DEBOUNCE_PERIOD) {return;}
	currentMs = milliseconds_now();
	ms = 0;
}

ISR(TIMER1_COMPA_vect) {
	if (freeze == false) {return;}
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
