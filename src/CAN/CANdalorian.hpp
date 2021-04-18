/*
* Created on April 5 2020
*
* Copyright (c) 2020 - Daniel Hajnal
* hajnal.daniel96@gmail.com
*
* This file is part of the STM32 Class Factory project.
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<inttypes.h>
#include<stdint.h>

#include "stm32f4xx_hal.h"
#include "can.h"

#include "System.hpp"


#ifndef STM32_CLASS_FACTORY_CANDALORIAN_HPP_
#define STM32_CLASS_FACTORY_CANDALORIAN_HPP_

/// CANdalorian CAN driver class
///
/// CANdalorian is a CAN driver library.
/// You can access ST-s CAN peripherial easily with this library.
///
/// Example for master device:
/// \code{.cpp}
///
/// // Create the master object. It wil use CAN1
/// CANdalorian canMaster( &hcan1 );
/// uint8_t dt[] = { 'H', 'e', 'l', 'l', 'o' };
///
/// int main(){
///
/// // Set it to normal mode.
/// canMaster.normalMode();
//
/// // Initialize the CAN module.
/// canMaster.begin();
///
/// // Transmitt the data stored in dt to an address of 0x65D.
/// canMaster.transmitt( 0x65D, dt, 5 );
///
/// while( 1 ){
///
/// //Check if master node got a message
/// if( canMaster.available() > 0 ){
///
/// // Variables for message reading
/// uint8_t recv[8];
/// uint8_t recv_size;
/// uint32_t recv_addr;
///
/// // Read out the message
/// canMaster.read( recv, &recv_size, &recv_addr );
///
/// }
///
/// }
///
/// return 0;
///
/// }
///
/// \endcode
///
/// Example for sllave device:
/// \code{.cpp}
///
/// // Create the slave object. It wil use CAN2
/// CANdalorian canSlave( &hcan2 );
/// uint8_t ansv[] = { 'C', 'o', 'f', 'f', 'e', 'e' };
///
/// int main(){
///
/// // Set it to normal mode.
/// canSlave.normalMode();
//
/// // Initialize the CAN slave module with address of 0x65D.
/// canSlave.beginSlave( 0x65D );
///
/// while( 1 ){
///
/// //Check if slave node got a message
/// if( canSlave.available() > 0 ){
///
/// // Variables for message reading
/// uint8_t recv[8];
/// uint8_t recv_size;
/// uint32_t recv_addr;
///
/// // Read out the message
/// canSlave.read( recv, &recv_size, &recv_addr );
///
/// // Respond to the message
/// canSlave.transmitt( 0x00, ansv, 6 );
///
/// }
///
/// }
///
/// return 0;
///
/// }
///
/// \endcode
class CANdalorian{

public:

	/// CANdalorian object constructor
	///
	/// You can creat CANdalorian objects with this constructor.
	/// @param can_device_p  pointer to a CAN peripherial
	/// @note CAN1 usually good for master device, and CAN2 is usually good for slave.
	CANdalorian( CAN_HandleTypeDef *can_device_p );

	/// Initializtation function for master mode
	///
	/// If you want to use the CAN peripherial with master mode( usually CAN1 )
	/// you have to use this initialization function.
	void begin();

	/// Initializtation function for slave mode
	///
	/// If you want to use the CAN peripherial with slave mode( usually CAN2 )
	/// you have to use this initialization function.
	/// @param slave_address_p the address of the slave device.
	/// @warning This driver only works with 11-bit Standard ID-s.
	void beginSlave( uint32_t slave_address_p );

	/// Enable loop back mode
	///
	/// This function enables loop back mode
	/// @warning This function has to be called before begin or beginSlave functions.
	/// @note This can be useful in software development without an actual slave.
	void loopbackMode();

	/// Enable normal mode
	///
	/// This function enables normal mode
	/// @warning This function has to be called before begin or beginSlave functions.
	void normalMode();

	/// Returns the number of available messages
	///
	/// You can read the number of available messages in the FIFO.
	/// Each FIFO can store 3 CAN messages maximum.
	/// @returns the number of available messages in the FIFO
	uint32_t available();

	/// Read one message from the FIFO
	///
	/// With this function you can read one message from the FIFO.
	/// @warning Before using this function you have to check if there is any data with available function.
	/// @param data pointer to an array which will store the CAN message. This array has to be 8 byte long!
	/// @param size pointer to a 8-bit number. This number will tell you how much byte long is the CAN message.
	/// @param addr pointer to a 32-bit number. This number will tell you the address of the node that has to recive this message.
	HAL_StatusTypeDef read( uint8_t *data, uint8_t *size, uint32_t *addr );

	/// Transmitt a message to a node
	///
	/// With this function you can transmitt a message to a CAN node.
	/// The function has a timeout and this is 100ms by default.
	/// @param address the address of the node where the message has to arrive
	/// @param data pointer to the data that has to be sent. With one transfer you can only send 8 bytes maximum.
	/// @param size the number of bytes in the message. It can send maximum 8 bytes.
	HAL_StatusTypeDef transmitt( uint32_t address, uint8_t *data, uint8_t size );

	/// Transmitt a message to a node
	///
	/// With this function you can transmitt a message to a CAN node.
	/// The function has a timeout and this is 100ms by default.
	/// @param address the address of the node where the message has to arrive
	/// @param data pointer to the data that has to be sent. With one transfer you can only send 8 bytes maximum.
	/// @param size the number of bytes in the message. It can send maximum 8 bytes.
	HAL_StatusTypeDef transmitt( uint32_t address, uint8_t *data, uint8_t size, uint32_t timeout );

private:

	/// This pointer will store the device data
	CAN_HandleTypeDef *can_device = NULL;

	/// Slave address of the CAN node
	uint32_t slave_address = 0;

	/// Filter configuration
	CAN_FilterTypeDef filter;

};


#endif /* STM32_CLASS_FACTORY_CAN_CAN_LIB_HPP_ */
