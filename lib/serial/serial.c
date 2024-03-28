//Example ATmega2560 Project
//File: serial.h
//Author: Robert Howie
//Created: 2 March 2015
//V1.0 Basic serial setup for printing to the serial terminal

//Derived from: http://www.github.com/abcminiuser/avr-tutorials/blob/master/USART/Output/USART.pdf?raw=true by Dean Camera
//See http://www.fourwalledcubicle.com/AVRArticles.php for more

#include "serial.h"
#include <string.h>

void serial0_init(void) {
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); //turn on the transmission and reception circuitry
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01); //use 8- bit character sizes
	UBRR0 = BAUD_PRESCALE; //load baud rate prescaler into register
} //end serial2_init

void serial1_init(void) {
	UCSR1B = (1<<RXEN1)|(1<<TXEN1); //turn on the transmission and reception circuitry
	UCSR1C = (1<<UCSZ10)|(1<<UCSZ11); //use 8- bit character sizes
	UBRR1 = BAUD_PRESCALE; //load baud rate prescaler into register
} //end serial2_init

void serial2_init(void) {
	UCSR2B = (1<<RXEN2)|(1<<TXEN2); //turn on the transmission and reception circuitry
	UCSR2C = (1<<UCSZ20)|(1<<UCSZ21); //use 8- bit character sizes
	UBRR2 = BAUD_PRESCALE; //load baud rate prescaler into register
} //end serial2_init

void serial3_init(void) {
	UCSR3B = (1<<RXEN3)|(1<<TXEN3); //turn on the transmission and reception circuitry
	UCSR3C = (1<<UCSZ30)|(1<<UCSZ31); //use 8- bit character sizes
	UBRR3 = BAUD_PRESCALE; //load baud rate prescaler into register
} //end serial3_init

//function to print a string via serial 
void serial0_print_string(char * string_pointer) { 
	while(*string_pointer) {//while not null character (end of string)
		while((UCSR0A&(1<<UDRE0))==0){} //wait until data register is ready
		UDR0 = *string_pointer; //send what's at the string pointer to serial data register
		string_pointer++; //increment string pointer to go to next letter in string
	}
} //end serial0_print_string
void serial0_write_byte(uint8_t data_byte) {
	while((UCSR0A&(1<<UDRE0))==0){} //wait until data register is ready
	UDR0 = data_byte; // 
}

void serial1_print_string(char * string_pointer) { //function to print a string via serial
	while(*string_pointer) { //while not null character (end of string)
		while((UCSR1A&(1<<UDRE1))==0){} //wait until data register is ready
		UDR1 = *string_pointer; //send what's at the string pointer to serial data register
		string_pointer++; //increment string pointer to go to next letter in string
	}
} //end serial1_print_string
void serial1_write_byte(uint8_t data_byte) {
	while((UCSR1A&(1<<UDRE1))==0){} //wait until data register is ready
	UDR1 = data_byte;
}

void serial2_print_string(char * string_pointer) { //function to print a string via serial
	while(*string_pointer) {//while not null character (end of string)
		while((UCSR2A&(1<<UDRE2))==0){} //wait until data register is ready
		UDR2 = *string_pointer; //send what's at the string pointer to serial data register
		string_pointer++; //increment string pointer to go to next letter in string
	}
} //end serial2_print_string
void serial2_write_byte(uint8_t data_byte) {
	while((UCSR2A&(1<<UDRE2))==0){} //wait until data register is ready
	UDR2 = data_byte;
}

void serial3_print_string(char * string_pointer) {//function to print a string via serial
	while(*string_pointer) {//while not null character (end of string)
		while((UCSR3A&(1<<UDRE3))==0){} //wait until data register is ready
		UDR3 = *string_pointer; //send what's at the string pointer to serial data register
		string_pointer++; //increment string pointer to go to next letter in string
	}
} //end serial3_print_string

void serial3_write_byte(uint8_t data_byte) {
	while((UCSR3A&(1<<UDRE3))==0){} //wait until data register is ready
	UDR3 = data_byte;
}

// Author: Daniel Denison
// Date: 22nd March 2024

// switch statement wrappers
void Serial_Init(int serial_pin) {
	switch (serial_pin) {
		case UART0:
		serial0_init();
		break;
		
		case UART1:
		serial1_init();
		break;
		
		case UART2:
		serial2_init();
		break;
		
		case UART3:
		serial3_init();
		break;
	}
}
void Serial_Print_String(char* string, int serial_pin) {
	switch (serial_pin) {
		case UART0:
		serial0_print_string(string);
		break;
		
		case UART1:
		serial1_print_string(string);
		break;
		
		case UART2:
		serial2_print_string(string);
		break;
		
		case UART3:
		serial3_print_string(string);
		break;
	}
}
void Serial_Write_Byte(uint8_t byte, int serial_pin) {
	switch (serial_pin) {
		case UART0:
		serial0_write_byte(byte);
		break;
		
		case UART1:
		serial1_write_byte(byte);
		break;
		
		case UART2:
		serial2_write_byte(byte);
		break;
		
		case UART3:
		serial3_write_byte(byte);
		break;
	}
}
_Bool Serial_Byte_Ready(int serial_pin) {
	switch (serial_pin) {
		case UART0:
		return serial0_byte_ready();
		
		case UART1:
		return serial1_byte_ready();
		
		case UART2:
		return serial2_byte_ready();
		
		case UART3:
		return serial3_byte_ready();
	}
}
uint8_t Serial_Read_Byte(int serial_pin) {
	switch (serial_pin) {
		case UART0:
		return serial0_read_byte();
		
		case UART1:
		return serial1_read_byte();
		
		case UART2:
		return serial2_read_byte();
		
		case UART3:
		return serial3_read_byte();
	}
}

// Checking whether any data has been sent over the Rx0 pin
_Bool serial0_byte_ready() {
	return ((UCSR0A & (1 << RXC0)) != 0); // Just returning whether the data register is ready
}
// Grabbing the data from the Rx0 pin
// This will halt the ATMEGA2560 until there is data to read, not a problem if there is already data there. Check with serial0_byte_ready()!!
uint8_t serial0_read_byte() {
	while(((UCSR0A & (1 << RXC0)) == 0)) {} // Wait until the data register is ready
	return UDR0; // Return value of data register
}

// Checking whether any data has been sent over the Rx1 pin
_Bool serial1_byte_ready() {
	return ((UCSR1A & (1 << RXC1)) != 0); // Just returning whether the data register is ready
}
// Grabbing the data from the Rx1 pin
// This will halt the ATMEGA2560 until there is data to read, not a problem if there is already data there. Check with serial1_byte_ready()!!
uint8_t serial1_read_byte() {
	while(((UCSR1A & (1 << RXC1)) == 0)) {} // Wait until the data register is ready
	return UDR1; // Return value of data register
}

// Checking whether any data has been sent over the Rx2 pin
_Bool serial2_byte_ready() {
	return ((UCSR2A & (1 << RXC2)) != 0); // Just returning whether the data register is ready
}
// Grabbing the data from the Rx2 pin
// This will halt the ATMEGA2560 until there is data to read, not a problem if there is already data there. Check with serial2_byte_ready()!!
uint8_t serial2_read_byte() {
	while(((UCSR2A & (1 << RXC2)) == 0)) {} // Wait until the data register is ready
	return UDR2; // Return value of data register
}

// Checking whether any data has been sent over the Rx3 pin
_Bool serial3_byte_ready() {
	return ((UCSR3A & (1 << RXC3)) != 0); // Just returning whether the data register is ready
}
// Grabbing the data from the Rx2 pin
// This will halt the ATMEGA2560 until there is data to read, not a problem if there is already data there. Check with serial2_byte_ready()!!
uint8_t serial3_read_byte() {
	while(((UCSR3A & (1 << RXC3)) == 0)) {} // Wait until the data register is ready
	return UDR3; // Return value of data register
}


// The Tx and Rx lines of the USB cable used to program the ATMEGA2560 are the Tx0 and Rx0 pins. So by sending data over the Tx0 pin, you are sending data back to the computer programming it,
// Same with Rx where you are reading data that was sent over from the computer
// Basically Serial.print from arduino but expert mode

// Shortcut for adding a new line character and then sending that string over serial0
// Havent tested this without specifying the length of the string yet.
void debug_string(char* string) {
	
	char* printStr[256];
	sprintf(printStr, "%s%c", string, '\n');
	serial0_print_string(printStr);
	
}

// Shortcut for adding the int data and then a new line character, then sending that over serial0
// Havent tested this without specifying the length of the string yet
void debug_int(char* label, int data) {
	
	char* printStr[256];
	sprintf(printStr, "%s: %d%c", label, data, '\n');
	serial0_print_string(printStr);
	
}

// Shortcut for adding the float data and then a new line character, then sending that over serial0
// Havent tested this without specifying the length of the string yet
void debug_float(char* label, float data) {
	
	char* printStr[256];
	sprintf(printStr, "%s: %f%c", data, data, '\n');
	serial0_print_string(printStr);
	
}