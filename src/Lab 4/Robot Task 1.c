#include "ATMEGA2560.h"
#include "Interrupt.h"

int32_t mm_min = 40; // What is the closest distance in mm we want to display
int32_t mm_max = 300; // What is the furthest distance in mm we want to display

int32_t range_min = 600; // What is the ADC 10 bit value corresponding to the closest distance
int32_t range_max = 78; // What is the ADC 10 bit value corresponding to the furthest distance
int32_t range_raw = 0; // What is the current ADC input, useful for freezing the readout

bool reading_range = true; // Are we currently updating the range from the ADC

void FreezeRangeVal(); // C wants you to do this

int main(void) {
	
	//initiation section, runs once
	adc_init();
	lcd_init();

	AttachInterrupt(INT0, FALLING, &FreezeRangeVal); // Adding the button interrupt
	
	_delay_ms(20); // Give the LCD some time to setup
	while (true) {
		
		// Only update the range we are displaying if reading_range is true
		if (reading_range == true) {
			range_raw = adc_read(PORTF0);
		}
		
		// Inverse linear interpolate, we want to find where range_raw falls between range_max and range_min
		// Start by taking range_raw and subtracting range_min, this will make the minimum value for range_raw fall exactly on 0
		// We then divide it by the total range, changing the range from 0-1023 or whatever to 0-1
		// Make sure to cast to float to avoid
		float range_val = (float)(range_raw - range_min) / (range_max - range_min);
		range_val = fmax(fmin(1.0, range_val), 0.0); // Clamping to the range 0-1
		
		int rangeInt = range_val * (mm_max - mm_min) + mm_min; // Representing the range in mm

		char lcd_top_line[16];
		char lcd_bottom_line[16];
		sprintf(lcd_top_line, "Range raw: %04d", range_raw); // The %04d is for printng as a 4 digit number
		sprintf(lcd_bottom_line, "Range: %03d%s", rangeInt, "mm"); // The %03d if for printin a 3 digit number and the %s is for the mm unts
		
		lcd_goto(0); //Put cursor at position 0
    	lcd_home(); // same as lcd_goto(0);
		lcd_puts(lcd_top_line); //Print string to LCD first line
		lcd_goto(0x40); //Put cursor to first character on second line
		lcd_puts(lcd_bottom_line);
		

	}
	return 1;
	
}

void FreezeRangeVal() {
	reading_range = !reading_range;
}