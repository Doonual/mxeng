#include "ATMEGA2560.h"
#include "Interrupt.h"

int32_t mm_min = 40;
int32_t mm_max = 300;

int32_t range_min = 600;
int32_t range_max = 78;
int32_t range_raw = 0;

bool readingRange = true;

void FreezeRangeVal();

int main(void) {
	
	//initiation section, runs once
	adc_init();
	lcd_init();

	_delay_ms(20);
	uint16_t range_raw;
	
	char lcd_top_line[16];
	char lcd_bottom_line[16];
	
	AttachInterrupt(INT0, FALLING, &FreezeRangeVal);
	
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
}