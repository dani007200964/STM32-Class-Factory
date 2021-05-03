/*
* Created on April 5 2020
*
* Copyright (c) 2020 - Daniel Hajnal
* hajnal.daniel96@gmail.com
*
* This file is part of the STM32 Class Factory project.
*/

#include "Serial.hpp"

Serial::Serial( UART_HandleTypeDef *usart_device_p ){

	usart_device = usart_device_p;

}

void Serial::begin( uint32_t baudrate_p ){

	if (HAL_UART_DeInit( usart_device ) != HAL_OK)
	{
		Error_Handler();
	}

	usart_device -> Init.BaudRate = baudrate_p;


	if (HAL_UART_Init( usart_device ) != HAL_OK)
	{
		Error_Handler();
	}

	recive_buffer_counter = 0;

	if (HAL_UART_Receive_DMA( usart_device, recive_buffer, SERIAL_RECIVE_BUFFER_LENGTH ) != HAL_OK)
	{
		Error_Handler();
	}



}

int Serial::available(){

	uint32_t dma_ptr;

	dma_ptr = SERIAL_RECIVE_BUFFER_LENGTH - ( usart_device -> hdmarx -> Instance -> NDTR );

	if( dma_ptr == recive_buffer_counter ){

		return 0;

	}

	else if( dma_ptr > recive_buffer_counter ){

		return dma_ptr - recive_buffer_counter;

	}

	else{

		return SERIAL_RECIVE_BUFFER_LENGTH - recive_buffer_counter +  dma_ptr;

	}

}

int Serial::read(){

	uint32_t dma_ptr;
	uint8_t ret;

	dma_ptr = SERIAL_RECIVE_BUFFER_LENGTH - ( usart_device -> hdmarx -> Instance -> NDTR );

	if( dma_ptr == recive_buffer_counter ){

		return -1;

	}

	else{

		ret = (uint8_t)recive_buffer[ recive_buffer_counter ];

		recive_buffer_counter++;

		if( recive_buffer_counter >= SERIAL_RECIVE_BUFFER_LENGTH ){

			recive_buffer_counter = 0;

		}

		return ret;

	}

}

int Serial::peek(){

	uint32_t dma_ptr;

	dma_ptr = SERIAL_RECIVE_BUFFER_LENGTH - ( usart_device -> hdmarx -> Instance -> NDTR );

	if( dma_ptr == recive_buffer_counter ){

		return -1;

	}

	else{

		return (uint8_t)recive_buffer[ recive_buffer_counter ];

	}

}

size_t Serial::readBytes( uint8_t *buff, uint32_t size ){

	uint32_t i;

	for( i = 0; i < size; i++ ){

		while( available() == 0 ){};

		buff[ i ] = read();

	}

	return i;

}

void Serial::flush(){

}

size_t Serial::write( uint8_t b ){

	if( HAL_UART_Transmit( usart_device, &b, 1, 100 ) == HAL_OK ){

		return 1;

	}

	else{

		return 0;

	}

}

///
size_t Serial::print( char c ){

	if( HAL_UART_Transmit( usart_device, (uint8_t*)&c, 1, 100 ) == HAL_OK ){

		return 1;

	}

	else{

		return 0;

	}

}

size_t Serial::print( char *str ){

	uint32_t dataSize = strlen( str );

	if( HAL_UART_Transmit( usart_device, (uint8_t*)str, dataSize, 1000 ) == HAL_OK ){

		return dataSize;

	}

	else{

		return 0;

	}

}

size_t Serial::print( const char *str ){

	uint32_t dataSize = strlen( str );

	if( HAL_UART_Transmit( usart_device, (uint8_t*)str, dataSize, 1000 ) == HAL_OK ){

		return dataSize;

	}

	else{

		return 0;

	}

}

size_t Serial::print( int8_t b ){

	char outBuff[10];
	uint32_t dataSize;

	snprintf( outBuff, 10, "%d", (int)b );

	dataSize = strlen( outBuff );

	if( HAL_UART_Transmit( usart_device, (uint8_t*)&outBuff, dataSize, 100 ) == HAL_OK ){

		return dataSize;

	}

	else{

		return 0;

	}

}

size_t Serial::print( uint8_t b ){

	char outBuff[10];
	uint32_t dataSize;

	snprintf( outBuff, 10, "%u", (int)b );

	dataSize = strlen( outBuff );

	if( HAL_UART_Transmit( usart_device, (uint8_t*)&outBuff, dataSize, 100 ) == HAL_OK ){

		return dataSize;

	}

	else{

		return 0;

	}

}

size_t Serial::print( int16_t b ){

	char outBuff[10];
	uint32_t dataSize;

	snprintf( outBuff, 10, "%d", (int)b );

	dataSize = strlen( outBuff );

	if( HAL_UART_Transmit( usart_device, (uint8_t*)&outBuff, dataSize, 100 ) == HAL_OK ){

		return dataSize;

	}

	else{

		return 0;

	}

}

size_t Serial::print( uint16_t b ){

	char outBuff[10];
	uint32_t dataSize;

	snprintf( outBuff, 10, "%u", (int)b );

	dataSize = strlen( outBuff );

	if( HAL_UART_Transmit( usart_device, (uint8_t*)&outBuff, dataSize, 100 ) == HAL_OK ){

		return dataSize;

	}

	else{

		return 0;

	}

}

size_t Serial::print( int32_t b ){

	char outBuff[15];
	uint32_t dataSize;

	snprintf( outBuff, 15, "%d", (int)b );

	dataSize = strlen( outBuff );

	if( HAL_UART_Transmit( usart_device, (uint8_t*)&outBuff, dataSize, 100 ) == HAL_OK ){

		return dataSize;

	}

	else{

		return 0;

	}

}

size_t Serial::print( uint32_t b ){

	char outBuff[15];
	uint32_t dataSize;

	snprintf( outBuff, 15, "%u", (int)b );

	dataSize = strlen( outBuff );

	if( HAL_UART_Transmit( usart_device, (uint8_t*)&outBuff, dataSize, 100 ) == HAL_OK ){

		return dataSize;

	}

	else{

		return 0;

	}

}

size_t Serial::print( int64_t b ){

	char outBuff[25];
	uint32_t dataSize;

	snprintf( outBuff, 25, "%d", (int)b );

	dataSize = strlen( outBuff );

	if( HAL_UART_Transmit( usart_device, (uint8_t*)&outBuff, dataSize, 100 ) == HAL_OK ){

		return dataSize;

	}

	else{

		return 0;

	}

}

size_t Serial::print( uint64_t b ){

	char outBuff[25];
	uint32_t dataSize;

	snprintf( outBuff, 25, "%u", (int)b );

	dataSize = strlen( outBuff );

	if( HAL_UART_Transmit( usart_device, (uint8_t*)&outBuff, dataSize, 100 ) == HAL_OK ){

		return dataSize;

	}

	else{

		return 0;

	}

}

size_t Serial::print( int i ){

	char outBuff[25];
	uint32_t dataSize;

	snprintf( outBuff, 25, "%d", i );

	dataSize = strlen( outBuff );

	if( HAL_UART_Transmit( usart_device, (uint8_t*)&outBuff, dataSize, 100 ) == HAL_OK ){

		return dataSize;

	}

	else{

		return 0;

	}

}

size_t Serial::print( unsigned int i ){

	char outBuff[25];
	uint32_t dataSize;

	snprintf( outBuff, 25, "%u", i );

	dataSize = strlen( outBuff );

	if( HAL_UART_Transmit( usart_device, (uint8_t*)&outBuff, dataSize, 100 ) == HAL_OK ){

		return dataSize;

	}

	else{

		return 0;

	}

}

size_t Serial::print( float f ){

	char outBuff[25];
	uint32_t dataSize;

	snprintf( outBuff, 25, "%f", f );

	dataSize = strlen( outBuff );

	if( HAL_UART_Transmit( usart_device, (uint8_t*)&outBuff, dataSize, 100 ) == HAL_OK ){

		return dataSize;

	}

	else{

		return 0;

	}

}

size_t Serial::print( double d ){

	char outBuff[25];
	uint32_t dataSize;

	snprintf( outBuff, 25, "%lf", d );

	dataSize = strlen( outBuff );

	if( HAL_UART_Transmit( usart_device, (uint8_t*)&outBuff, dataSize, 100 ) == HAL_OK ){

		return dataSize;

	}

	else{

		return 0;

	}

}

size_t Serial::println(){

	size_t ret;

	ret = print( "\r\n" );

	return ret;

}

size_t Serial::println( char c ){

	size_t ret;

	ret = print( c );
	ret += print( "\r\n" );

	return ret;

}

size_t Serial::println( char *str ){

	size_t ret;

	ret = print( str );
	ret += print( "\r\n" );

	return ret;

}

size_t Serial::println( const char *str ){

	size_t ret;

	ret = print( str );
	ret += print( "\r\n" );

	return ret;

}

size_t Serial::println( int8_t b ){

	size_t ret;

	ret = print( b );
	ret += print( "\r\n" );

	return ret;

}

size_t Serial::println( uint8_t b ){

	size_t ret;

	ret = print( b );
	ret += print( "\r\n" );

	return ret;

}

size_t Serial::println( int16_t b ){

	size_t ret;

	ret = print( b );
	ret += print( "\r\n" );

	return ret;

}

size_t Serial::println( uint16_t b ){

	size_t ret;

	ret = print( b );
	ret += print( "\r\n" );

	return ret;

}

size_t Serial::println( int32_t b ){

	size_t ret;

	ret = print( b );
	ret += print( "\r\n" );

	return ret;

}

size_t Serial::println( uint32_t b ){

	size_t ret;

	ret = print( b );
	ret += print( "\r\n" );

	return ret;

}

size_t Serial::println( int64_t b ){

	size_t ret;

	ret = print( b );
	ret += print( "\r\n" );

	return ret;

}

size_t Serial::println( uint64_t b ){

	size_t ret;

	ret = print( b );
	ret += print( "\r\n" );

	return ret;

}

size_t Serial::println( int i ){

	size_t ret;

	ret = print( i );
	ret += print( "\r\n" );

	return ret;

}

size_t Serial::println( unsigned int i ){

	size_t ret;

	ret = print( i );
	ret += print( "\r\n" );

	return ret;

}

size_t Serial::println( float f ){

	size_t ret;

	ret = print( f );
	ret += print( "\r\n" );

	return ret;

}

size_t Serial::println( double d ){

	size_t ret;

	ret = print( d );
	ret += print( "\r\n" );

	return ret;

}

int Serial::printf( const char *fmt, ... ){

	int ret;

	char out_buff[ SERIAL_PRINTF_BUFFER_LENGTH ];

	va_list args;

	va_start( args, fmt );

	ret = vsnprintf( out_buff, SERIAL_PRINTF_BUFFER_LENGTH, fmt, args );

	va_end( args );

	if( HAL_UART_Transmit( usart_device, (uint8_t*)&out_buff, strlen( out_buff ), 100 ) == HAL_OK ){

		return ret;

	}

	else{

		return -1;

	}

}

int Serial::printf( char *fmt, ... ){

	int ret;

	char out_buff[ SERIAL_PRINTF_BUFFER_LENGTH ];

	va_list args;

	va_start( args, fmt );

	ret = vsnprintf( out_buff, SERIAL_PRINTF_BUFFER_LENGTH, (const char*)fmt, args );

	va_end( args );

	if( HAL_UART_Transmit( usart_device, (uint8_t*)&out_buff, strlen( out_buff ), 100 ) == HAL_OK ){

		return ret;

	}

	else{

		return -1;

	}

}

int Serial::dbgPrintf( const char *fmt, ... ){

	int ret;

	char out_buff[ SERIAL_PRINTF_BUFFER_LENGTH ];

	va_list args;

	va_start( args, fmt );

	ret = vsnprintf( out_buff, SERIAL_PRINTF_BUFFER_LENGTH, fmt, args );

	va_end( args );

	printf( "[ %d ] dbg: ", millis() );

	if( HAL_UART_Transmit( usart_device, (uint8_t*)&out_buff, strlen( out_buff ), 100 ) == HAL_OK ){

		return ret;

	}

	else{

		return -1;

	}

}
