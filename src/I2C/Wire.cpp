/*
* Created on April 5 2020
*
* Copyright (c) 2020 - Daniel Hajnal
* hajnal.daniel96@gmail.com
*
* This file is part of the STM32 Class Factory project.
*/

#include "Wire.hpp"

Wire::Wire( I2C_HandleTypeDef *i2c_peripherial_p ){

	// We save the peripherial data to a local variable.
	i2c_peripherial = i2c_peripherial_p;

}

void Wire::begin(){

	// We have to validate that i2c_peripherial has set correctly.
	if( i2c_peripherial == NULL ){

		// If not we have to return
		return;

	}

	// This constructor is for master mode, so we set the type accordingly.
	mode = MASTER;

	// Firstly we have to deinitialise the periferial to modify its parameters.
	if (HAL_I2C_DeInit( i2c_peripherial ) != HAL_OK)
	{
		// If we can't deinitialise the peripherial we have to stop program execution.
		Error_Handler();
	}

	// We have to reset transmitt_buffer_counter variable to 0
	transmitt_buffer_counter = 0;

	// We have to reset recive_buffer_counter variable to 0
	recive_buffer_counter = 0;

	// We have to reset recive_buffer_top variable to 0
	recive_buffer_top = 0;

	// We finished the configuration of the peripherial, so we have to initialise it.
	if (HAL_I2C_Init( i2c_peripherial ) != HAL_OK)
	{
		// If we can't initialise the peripherial we have to stop program execution.
		Error_Handler();
	}

}

void Wire::begin( uint16_t address ){

	// We have to validate that i2c_peripherial has set correctly.
	if( i2c_peripherial == NULL ){

		// If not we have to return
		return;

	}

	// This constructor is for slave mode, so we set the type accordingly.
	mode = SLAVE;

	if (HAL_I2C_DeInit( i2c_peripherial ) != HAL_OK)
	{
		Error_Handler();
	}

	slave_address = address;

	i2c_peripherial -> Init.OwnAddress1 = slave_address;

	if (HAL_I2C_Init( i2c_peripherial ) != HAL_OK)
	{
		Error_Handler();
	}
}

void Wire::beginTransmission( uint16_t addr ){

	// We save the slave address.
	slave_address = addr;

	// We reset the transmitt_state variable.
	transmitt_state = 0;

}

uint8_t Wire::endTransmission(){

	// This variable will hold the result of the transaction.
	HAL_StatusTypeDef result;

	// We transmitt the data stored in the buffer and we save
	// the result of the transaction to the result variable.
	result = HAL_I2C_Master_Transmit( i2c_peripherial, ( slave_address << 1 ), transmitt_buffer, transmitt_buffer_counter, 100 );

	// We have to check the result of the transaction
	if( result != HAL_OK ){

		// If something wrong happened during the
		// transaction we have to set transmitt_state to 4.
		// This means something unexpected happened.
		transmitt_state = 4;

	}

	// Return the status of the transmission.
	// Iv everything went good it should be 0.
	return transmitt_state;


}

size_t Wire::write( uint8_t b ){


	// We have to chack that the pointer variable is in its range.
	if( transmitt_buffer_counter >= WIRE_TRANSMITT_BUFFER_LENGTH ){

		// And we have to notice with transmitt_state variable that a
		// buffer full event happened.
		transmitt_state = 1;

		return 0;

	}

	// We put the new data to the end of the transmitt_buffer.
	transmitt_buffer[ transmitt_buffer_counter ] = b;

	// We increment the variable that points to the next free slot in the buffer.
	transmitt_buffer_counter++;


	return 1;

}

size_t Wire::requestFrom( uint16_t address, uint16_t quantity ){


	// This variable will hold the result of the transaction.
	HAL_StatusTypeDef result;

	// We try to recive the data from the slave and we save
	// the result of the transaction to the result variable.
	result = HAL_I2C_Master_Receive( i2c_peripherial, ( ( address << 1 ) | 0x01 ), recive_buffer, quantity, 1000 );

	// We have to check the result of the transaction
	if( result == HAL_OK ){

		// If the transaction was succesful we define the top of the recive buffer.
		recive_buffer_top = quantity;

		// And return with the amunt of bytes that has been read
		return quantity;

	}

	else{

		// If there was a problem with the transaction we have to
		// reset recive_buffer_top and recive_buffer_counter variables.
		recive_buffer_top = 0;
		recive_buffer_counter = 0;

		// And we have to return with 0
		return 0;

	}

}

int Wire::available(){

	// Returns how much bytes are available for read in the buffer.
	return recive_buffer_top - recive_buffer_counter;

}

int Wire::read(){

	// This variable will hold the return value.
	int ret;

	// We have to check if the buffer is empty.
	if( available() == 0 ){

		// If the buffer is empty, return with an invalid number.
		return -1;

	}

	else{

		// If valid data is available we have to read and store it first.
		ret = recive_buffer[ recive_buffer_counter ];

		// We have to invcrement the recive_buffer_counter variable to
		// point to the next element in the recive buffer.
		recive_buffer_counter++;

		// We have to check that if we found the top of the buffer
		if( recive_buffer_counter >= recive_buffer_top ){

			// If we found the top then we have been read all data from recive buffer
			// So we have to reset recive_buffer_counter and recive_buffer_top variables.
			recive_buffer_counter = 0;
			recive_buffer_top = 0;

		}

		// Finally we return with the element that have been read from the buffer.
		return ret;
	}

}





