/*
* Created on April 5 2020
*
* Copyright (c) 2020 - Daniel Hajnal
* hajnal.daniel96@gmail.com
*
* This file is part of the STM32 Class Factory project.
*/

#ifndef SERIAL_H_
#define SERIAL_H_

#include<stdlib.h>
#include<stdio.h>
#include<stdarg.h>
#include<string.h>
#include<inttypes.h>
#include<stdint.h>

#include "stm32f4xx_hal.h"
#include "usart.h"

#include "System.hpp"

/// Length of the recive buffer
///
/// You can specify how much bytes you want to recive maximum.
/// If this buffer is to large, then it will waste your RAM.
/// If this buffer is to short, then you can't send your data properly.
#define SERIAL_RECIVE_BUFFER_LENGTH 10

/// Length of the printf buffer
///
/// You can specify how much bytes you want to put in a formatted string maximum.
/// If this buffer is to large, then it will waste your RAM.
/// If this buffer is to short, then you can't send your data properly.
#define SERIAL_PRINTF_BUFFER_LENGTH 100

/// Serial RS232 Class
///
/// Serial is an RS232 library. This is an Arduino Serial like object, the
/// functionality is ment to be the same.
class Serial{

public:
  /// Serial object constructor
  ///
  /// @param usart_device_p pointer to an RS232 peripherial.
  Serial( UART_HandleTypeDef *usart_device_p );

  /// Begin function
  ///
  /// It initalises the peripherial and starts the reception with DMA.
  /// @param baudrate_p You can specify the baudrate with this argument.
  void begin( uint32_t baudrate_p );

  /// Returns the number of bytes in the recive buffer
	///
	/// With this function you can read that how many bytes arrived into the
	/// recive buffer. If the buffer is empty, the result will be 0.
  int available();

  /// Read one byte from buffer
	///
	/// This function returns the next data from the recive buffer if there are
	/// any data to read. If the buffer is empty then this function will return -1.
  /// After reading this data it will be removed from the buffer.
  int read();

  /// Read one byte from buffer without removeing it
	///
	/// This function returns the next data from the recive buffer if there are
  /// After reading this data it won't be cleared from the buffer.
	/// any data to read. If the buffer is empty then this function will return -1.
  int peek();

  /// Read bytes to a buffer
  ///
  /// This command reads a predefined amount of bytes to a buffer.
  /// @param buff the pointer to the buffer.
  /// @param size the size of the buffer.
  size_t readBytes( uint8_t *buff, uint32_t size );

  /// Flush the transmitt buffer
  ///
  /// Actually this is not needed because the transmitt function is a blocked
  /// implementation. It is implemented only because compatibility reasons.
  void flush();

  /// Transmitt a byte
  ///
  /// Transmitt a byte. It is using blockint code!
  /// @param b the byte that you want to transmitt
  size_t write( uint8_t b );

  /// Transmitt a character
  ///
  /// Transmitt a character. It is using blockint code!
  /// @param c the character that you want to transmitt
  size_t print( char c );

  /// Transmitt a string
  ///
  /// Transmitt a string. It is using blockint code!
  /// The string has to be a c/c++ like '\0' terminated data.
  /// @param str the string that you want to transmitt
  size_t print( char *str );

  /// Transmitt a string
  ///
  /// Transmitt a string. It is using blockint code!
  /// The string has to be a c/c++ like '\0' terminated data.
  /// @param str the string that you want to transmitt
  size_t print( const char *str );

  /// Transmitt a int8_t
  ///
  /// Transmitt a int8_t. It is using blockint code!
  /// @param b the data that you want to transmitt
  size_t print( int8_t b );

  /// Transmitt an uint8_t
  ///
  /// Transmitt an uint8_t. It is using blockint code!
  /// @param b the data that you want to transmitt
  size_t print( uint8_t b );

  /// Transmitt a int16_t
  ///
  /// Transmitt a int16_t. It is using blockint code!
  /// @param b the data that you want to transmitt
  size_t print( int16_t b );

  /// Transmitt an uint16_t
  ///
  /// Transmitt an uint16_t. It is using blockint code!
  /// @param b the data that you want to transmitt
  size_t print( uint16_t b );

  /// Transmitt a int32_t
  ///
  /// Transmitt a int32_t. It is using blockint code!
  /// @param b the data that you want to transmitt
  size_t print( int32_t b );

  /// Transmitt an uint32_t
  ///
  /// Transmitt an uint32_t. It is using blockint code!
  /// @param b the data that you want to transmitt
  size_t print( uint32_t b );

  /// Transmitt a int64_t
  ///
  /// Transmitt a int64_t. It is using blockint code!
  /// @param b the data that you want to transmitt
  size_t print( int64_t b );

  /// Transmitt an uint64_t
  ///
  /// Transmitt an uint64_t. It is using blockint code!
  /// @param b the data that you want to transmitt
  size_t print( uint64_t b );

  /// Transmitt an int
  ///
  /// Transmitt an int. It is using blockint code!
  /// @param b the data that you want to transmitt
  size_t print( int i );

  /// Transmitt an unsigned int
  ///
  /// Transmitt an unsigned int. It is using blockint code!
  /// @param b the data that you want to transmitt
  size_t print( unsigned int i );

  /// Transmitt a float
  ///
  /// Transmitt a float. It is using blockint code!
  /// @param f the float that you want to transmitt
  size_t print( float f );

  /// Transmitt a double
  ///
  /// Transmitt a double. It is using blockint code!
  /// @param d the float that you want to transmitt
  size_t print( double d );





  /// Transmitt a character with a new line
  ///
  /// Transmitt a character  with a new line. It is using blockint code!
  /// The new line consist of a "\r\n" combo.
  /// @param c the character that you want to transmitt
  size_t println( char c );

  /// Transmitt a string with a new line
  ///
  /// Transmitt a string with a new line. It is using blockint code!
  /// The string has to be a c/c++ like '\0' terminated data.
  /// The new line consist of a "\r\n" combo.
  /// @param str the string that you want to transmitt
  size_t println( char *str );

  /// Transmitt a string with a new line
  ///
  /// Transmitt a string with a new line. It is using blockint code!
  /// The string has to be a c/c++ like '\0' terminated data.
  /// The new line consist of a "\r\n" combo.
  /// @param str the string that you want to transmitt
  size_t println( const char *str );

  /// Transmitt a int8_t with a new line
  ///
  /// Transmitt a int8_t. It is using blockint code!
  /// The new line consist of a "\r\n" combo.
  /// @param b the data that you want to transmitt
  size_t println( int8_t b );

  /// Transmitt an uint8_t with a new line
  ///
  /// Transmitt an uint8_t. It is using blockint code!
  /// The new line consist of a "\r\n" combo.
  /// @param b the data that you want to transmitt
  size_t println( uint8_t b );

  /// Transmitt a int16_t with a new line
  ///
  /// Transmitt a int16_t. It is using blockint code!
  /// The new line consist of a "\r\n" combo.
  /// @param b the data that you want to transmitt
  size_t println( int16_t b );

  /// Transmitt an uint16_t with a new line
  ///
  /// Transmitt an uint16_t. It is using blockint code!
  /// The new line consist of a "\r\n" combo.
  /// @param b the data that you want to transmitt
  size_t println( uint16_t b );

  /// Transmitt a int32_t with a new line
  ///
  /// Transmitt a int32_t. It is using blockint code!
  /// The new line consist of a "\r\n" combo.
  /// @param b the data that you want to transmitt
  size_t println( int32_t b );

  /// Transmitt an uint32_t with a new line
  ///
  /// Transmitt an uint32_t. It is using blockint code!
  /// The new line consist of a "\r\n" combo.
  /// @param b the data that you want to transmitt
  size_t println( uint32_t b );

  /// Transmitt a int64_t with a new line
  ///
  /// Transmitt a int64_t. It is using blockint code!
  /// The new line consist of a "\r\n" combo.
  /// @param b the data that you want to transmitt
  size_t println( int64_t b );

  /// Transmitt an uint64_t with a new line
  ///
  /// Transmitt an uint64_t. It is using blockint code!
  /// The new line consist of a "\r\n" combo.
  /// @param b the data that you want to transmitt
  size_t println( uint64_t b );

  /// Transmitt an int with a new line
  ///
  /// Transmitt an int. It is using blockint code!
  /// The new line consist of a "\r\n" combo.
  /// @param b the data that you want to transmitt
  size_t println( int i );

  /// Transmitt an unsigned int with a new line
  ///
  /// Transmitt an unsigned int. It is using blockint code!
  /// The new line consist of a "\r\n" combo.
  /// @param b the data that you want to transmitt
  size_t println( unsigned int i );

  /// Transmitt a float with a new line
  ///
  /// Transmitt a float. It is using blockint code!
  /// The new line consist of a "\r\n" combo.
  /// @param f the float that you want to transmitt
  size_t println( float f );

  /// Transmitt a double with a new line
  ///
  /// Transmitt a double. It is using blockint code!
  /// The new line consist of a "\r\n" combo.
  /// @param d the float that you want to transmitt
  size_t println( double d );

  /// Transmit a formatted string
  ///
  /// This is a printf like function. The usage is exactly the same.
  /// It can transmitt a formatted string. The length of the formatted
  /// string is limited to a size of the \link SERIAL_PRINTF_BUFFER_LENGTH \endlink
  /// buffer size.
  /// @param fmt formatt string
  /// @param ... arguments
  int printf( const char *fmt, ... );

  /// Transmit a formatted string
  ///
  /// This is a printf like function. The usage is exactly the same.
  /// It can transmitt a formatted string. The length of the formatted
  /// string is limited to a size of the \link SERIAL_PRINTF_BUFFER_LENGTH \endlink
  /// buffer size.
  /// @param fmt formatt string
  /// @param ... arguments
  int printf( char *fmt, ... );

  /// Transmit a debug message as a formatted string
  ///
  /// This is a printf like function. The usage is exactly the same.
  /// It can transmitt a formatted string. The length of the formatted
  /// string is limited to a size of the \link SERIAL_PRINTF_BUFFER_LENGTH \endlink
  /// buffer size.
  /// @param fmt formatt string
  /// @param ... arguments
  int dbgPrintf( const char *fmt, ... );

  /// Transmit a debug message as a formatted string
  ///
  /// This is a printf like function. The usage is exactly the same.
  /// It can transmitt a formatted string. The length of the formatted
  /// string is limited to a size of the \link SERIAL_PRINTF_BUFFER_LENGTH \endlink
  /// buffer size.
  /// @param fmt formatt string
  /// @param ... arguments
  int dbgPrintf( char *fmt, ... );





private:
  /// Uart peripherial address
  UART_HandleTypeDef *usart_device = NULL;

  /// Baudrate setting
  uint32_t baudrate = 0;

  /// Recive buffer
  uint8_t recive_buffer[ SERIAL_RECIVE_BUFFER_LENGTH ];

  /// Points to the next free element in the recive buffer
  uint32_t recive_buffer_counter = 0;
};


#endif
