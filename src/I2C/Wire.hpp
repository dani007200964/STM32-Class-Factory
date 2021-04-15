/*
* Created on April 5 2020
*
* Copyright (c) 2020 - Daniel Hajnal
* hajnal.daniel96@gmail.com
*
* This file is part of the STM32 Class Factory project.
*/

#ifndef STM32_CLASS_FACTORY_I2C_WIRE_HPP_
#define STM32_CLASS_FACTORY_I2C_WIRE_HPP_

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<inttypes.h>
#include<stdint.h>

#include "stm32f4xx_hal.h"
#include "i2c.h"

/// Length of the transmitt buffer
///
/// You can specify how much bytes you want to transmitt maximum.
/// If this buffer is to large, then it will waste your RAM.
/// If this buffer is to short, then you can't send your data properly.
#define WIRE_TRANSMITT_BUFFER_LENGTH 10

/// Length of the recive buffer
///
/// You can specify how much bytes you want to recive maximum.
/// If this buffer is to large, then it will waste your RAM.
/// If this buffer is to short, then you can't send your data properly.
#define WIRE_RECIVE_BUFFER_LENGTH 20


/// Wire I2C Class
///
/// Wire is an I2C library. This is an Arduino Wire like object, the
/// functionality is ment to be the same.
/// @warning Slave code is not implemented yet!
class Wire{

public:

	/// Enumeration for peripherial modes
	enum i2c_mode{
		MASTER,
		SLAVE
	};

	/// Wire object constructor
	///
	/// @param i2c_peripherial_p pointer to an i2c peripherial
	Wire( I2C_HandleTypeDef *i2c_peripherial_p );

	/// Begin function for master mode
	///
	/// When you want to use Wire as an I2C master you should
	/// use begin like this.
	void begin();

	/// Begin function for slave mode
	///
	/// When you want to use Wire as an I2C master you should
	/// use begin like this.
	/// @warning Slave mode is not implemented yet! Please do not use it!
	/// @param address slave address of the device
	void begin( uint16_t address );

	/// Begins a transaction from master
	///
	/// When you use master mode and you want to send date to an I2c slave
	/// you have to use this function first.
	/// @param addr the address of the slave that you want to communicate with
	void beginTransmission( uint16_t addr );

	/// Ends a transaction from master
	///
	/// When you have finished the data sending to the slave you have to end
	/// the transaction with this function. In practice this function will
	/// send all of the data, the write function just puts it in to a buffer.
	uint8_t endTransmission();

	/// Write data to a slave
	///
	/// If you want to write a byte to a slave you should use this function.
	/// In practice this function just puts the data in a buffer, and the
	/// \link endTransmission \endlink function will send it.
	/// @warning before using this function you have to specify the slave with \link beginTransmission \endlink function
	/// @param b the byte you want to send
	size_t write( uint8_t b );

	/// Read data from slave
	///
	/// If you want to read a known number of bytes from a slave device
	/// you should use this function.
	/// @param address the address of the slave that you want to communicate with
	/// @param quantity the number of bytes that you want to recive
	size_t requestFrom( uint16_t address, uint16_t quantity );

	/// Returns the number of bytes in the recive buffer
	///
	/// With this function you can read that how many bytes arrived into the
	/// recive buffer. If the buffer is empty, the result will be 0.
	int available();

	/// Read one byte from buffer
	///
	/// This function returns the next data from the recive buffer if there are
	/// any data to read. If the buffer is empty then this function will return -1.
	int read();

private:
	I2C_HandleTypeDef *i2c_peripherial = NULL;
	i2c_mode mode;
	uint16_t slave_address;

	uint8_t transmitt_buffer[ WIRE_TRANSMITT_BUFFER_LENGTH ];
	uint32_t transmitt_buffer_counter = 0;
	uint8_t transmitt_state;

	uint8_t recive_buffer[ WIRE_RECIVE_BUFFER_LENGTH ];
	uint32_t recive_buffer_top = 0;
	uint32_t recive_buffer_counter = 0;
};



#endif /* STM32_CLASS_FACTORY_I2C_WIRE_HPP_ */
