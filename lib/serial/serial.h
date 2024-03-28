/*
 * Serial.h
 *
 * Created: 2/03/2015 5:41:43 PM
 *  Author: Robert
 */ 


#ifndef SERIAL_H_
#define SERIAL_H_

//include libraries
# include <avr/io.h>

//macros
# define USART_BAUDRATE 9600
# define BAUD_PRESCALE ((((F_CPU/16)+(USART_BAUDRATE/2))/(USART_BAUDRATE))-1)

#define UART0 0
#define UART1 1
#define UART2 2
#define UART3 3

//function prototypes
void serial0_init(void);
void serial0_print_string(char * string_pointer);
void serial0_write_byte(uint8_t data_byte);

void serial1_init(void);
void serial1_print_string(char * string_pointer);
void serial1_write_byte(uint8_t data_byte);

void serial2_init(void);
void serial2_print_string(char * string_pointer);
void serial2_write_byte(uint8_t data_byte);

void serial3_init(void);
void serial3_print_string(char * string_pointer);
void serial3_write_byte(uint8_t data_byte);

void Serial_Init(int serial_pin);
void Serial_Print_String(char* string, int serial_pin);
void Serial_Write_Byte(uint8_t byte, int serial_pin);
_Bool Serial_Byte_Ready(int serial_pin);
uint8_t Serial_Read_Byte(int serial_pin);

_Bool serial0_byte_ready();
uint8_t serial0_read_byte();

_Bool serial1_byte_ready();
uint8_t serial1_read_byte();

_Bool serial2_byte_ready();
uint8_t serial2_read_byte();

_Bool serial3_byte_ready();
uint8_t serial3_read_byte();

void debug_string(char* string);
void debug_int(char* string, int data);
void debug_float(char* string, float data);

#endif /* SERIAL_H_ */
