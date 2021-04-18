/*
* Created on April 5 2020
*
* Copyright (c) 2020 - Daniel Hajnal
* hajnal.daniel96@gmail.com
*
* This file is part of the STM32 Class Factory project.
*/

#include "CANdalorian.hpp"

CANdalorian::CANdalorian( CAN_HandleTypeDef *can_device_p ){

	// We save the peripheral data to a local variable.
	can_device = can_device_p;

}

void CANdalorian::beginSlave( uint32_t slave_address_p ){

	// We have to validate that can_device has set correctly.
	if( can_device == NULL ){

		// If not we have to return.
		return;

	}

	// We have to check that the address is in boundaries.
	if( ( slave_address > 2047 ) || ( slave_address == 0 ) ){

		// If not we have to enter to the Error_Handler.
		Error_Handler();

	}

	// Save the addres to a local variable.
	slave_address = slave_address_p;

	// Firstly we have to deinitialise the periferal to modify its parameters.
	if ( HAL_CAN_DeInit( can_device ) != HAL_OK )
	{
		// If we can't deinitialise the peripheral we have to stop program execution.
		Error_Handler();
	}

	// We finished the configuration of the peripheral, so we have to initialise it.
	if ( HAL_CAN_Init( can_device ) != HAL_OK )
	{
		// If we can't initialise the peripheral we have to stop program execution.
		Error_Handler();
	}

	// In slave mode we enable the Auto Bus Off management.
	can_device -> Init.AutoBusOff = ENABLE;

	// Slave devices filter bank is configured to 14.
	filter.FilterBank = 14;

	// Slave device filter is configured to mask mode.
	filter.FilterMode = CAN_FILTERMODE_IDMASK;

	// Slave device filter is configured to 32-bit long mode.
	filter.FilterScale = CAN_FILTERSCALE_32BIT;

	// Add the slave_address to the filter.
	filter.FilterIdHigh =  ( slave_address << 5 );

	// Filter ID low has to be 0.
	filter.FilterIdLow = 0x0000;

	// Filter mask high has to be 0b1111111111100000.
	filter.FilterMaskIdHigh = 0xFFE0;

	// Filter mask low has to be 0.
	filter.FilterMaskIdLow = 0x0000;

	// Slave device is using FIFO1.
	filter.FilterFIFOAssignment = CAN_RX_FIFO1;

	// Enable the filter
	filter.FilterActivation = CAN_FILTER_ENABLE;

	// Slave device start filter bank is 14.
	filter.SlaveStartFilterBank = 14;

	// Enabling the filter configuration on the hardware.
	// We have to check if it is successful
	if( HAL_CAN_ConfigFilter( can_device, &filter ) != HAL_OK ){

		// If not we have to enter to the Error_Handler.
		Error_Handler();

	}

	// Finally start the peripheral.
	HAL_CAN_Start( can_device );

}

void CANdalorian::begin(){

	// We have to validate that can_device has set correctly.
	if( can_device == NULL ){

		// If not we have to return.
		return;

	}

	// Master node's id is 0
	slave_address = 0;

	// Firstly we have to deinitialise the periferal to modify its parameters.
	if ( HAL_CAN_DeInit( can_device ) != HAL_OK )
	{

		// If we can't deinitialise the peripheral we have to stop program execution.
		Error_Handler();

		// If we can't deinitialise the peripheral we have to stop program execution.
	}

	// We finished the configuration of the peripheral, so we have to initialise it.
	if ( HAL_CAN_Init( can_device ) != HAL_OK )
	{

		// If we can't initialise the peripheral we have to stop program execution.
		Error_Handler();

	}

	// Automatic Bus Off management is Disabled on the master device.
	can_device -> Init.AutoBusOff = DISABLE;

	// Master devices filter bank is configured to 0.
	filter.FilterBank = 0;

	// Master device filter is configured to mask mode.
	filter.FilterMode = CAN_FILTERMODE_IDMASK;

	// Master device filter is configured to 32-bit long mode.
	filter.FilterScale = CAN_FILTERSCALE_32BIT;

	// Add the master address to the filter.
	// In result this will allow every message to be redirected to the FIFO.
	filter.FilterIdHigh = 0x0000;

	// Filter ID low has to be 0.
	filter.FilterIdLow = 0x0000;

	// Filter mask high has to be 0.
	filter.FilterMaskIdHigh = 0x0000;

	// Filter mask high has to be 0.
	filter.FilterMaskIdLow = 0x0000;

	// Master device is using FIFO0.
	filter.FilterFIFOAssignment = CAN_RX_FIFO0;

	// Enable the filter
	filter.FilterActivation = CAN_FILTER_ENABLE;

	// Maskter device start filter bank is 0.
	filter.SlaveStartFilterBank = 0;

	// Enabling the filter configuration on the hardware.
	// We have to check if it is successful
	if( HAL_CAN_ConfigFilter( can_device, &filter ) != HAL_OK ){

		// If not we have to enter to the Error_Handler.
		Error_Handler();

	}

	// Finally start the peripheral.
	HAL_CAN_Start( can_device );


}

void CANdalorian::loopbackMode(){

	// Enable loop back mode.
	can_device -> Init.Mode = CAN_MODE_LOOPBACK;

}

void CANdalorian::normalMode(){

	// Enable normal mode.
	can_device -> Init.Mode = CAN_MODE_NORMAL;

}

HAL_StatusTypeDef CANdalorian::transmitt( uint32_t address, uint8_t *data, uint8_t size ){

	// This variable will hold the message header.
	CAN_TxHeaderTypeDef canTxHeader;

	// This variable will hold the mailbox ID.
	uint32_t canTxMailbox;

	// This variable will hold pending status of the massage.
	uint32_t pending;

	// This variable will hold the number of trys in case of failed transmission.
	uint32_t try_count = 0;

	// We have to check if the address is valid.
	if( address > 2047 ){

		// If not return with error.
		return HAL_ERROR;

	}

	// We have to check how many bytes we have to send.
	// We can send 8 bytes with one transfer maximum.
	if( size > 8 ){

		// If more than 8 bytes desired to send, we don't send the remaining bytes.
		size = 8;

	}

	// Configure the header.
	canTxHeader.DLC = size;			// size config
	canTxHeader.StdId = address;	// address config
	canTxHeader.IDE = CAN_ID_STD;	// Standard ID config
	canTxHeader.RTR = CAN_RTR_DATA;	// Data type config

	// Trying to add the message to the output queue.
	if( HAL_CAN_AddTxMessage( can_device, &canTxHeader, data, &canTxMailbox ) != HAL_OK ){

		// If it fails return with error.
		return HAL_ERROR;

	}

	// Check the status of the message.
	pending = HAL_CAN_IsTxMessagePending( can_device, canTxMailbox );

	// Wait until it gets sent out or timeout occurs.
	while( pending ){

		// Increment the try_count variable.
		try_count++;

		// Check if timeout happened.
		// In this case 100ms.
		if( try_count >= 100 ){

			// If timeout happened abort the request.
			HAL_CAN_AbortTxRequest( can_device, canTxMailbox );

			// Return with timeout error.
			return HAL_TIMEOUT;

		}

		// Delay 1ms.
		delay( 1 );

		// Check the status of the message again.
		pending = HAL_CAN_IsTxMessagePending( can_device, canTxMailbox );

	}

	// If the message is sent and timeout not occurred return with HAL_OK.
	return HAL_OK;

}

HAL_StatusTypeDef CANdalorian::transmitt( uint32_t address, uint8_t *data, uint8_t size, uint32_t timeout  ){

	// This variable will hold the message header.
	CAN_TxHeaderTypeDef canTxHeader;

	// This variable will hold the mailbox ID.
	uint32_t canTxMailbox;

	// This variable will hold pending status of the massage.
	uint32_t pending;

	// This variable will hold the number of trys in case of failed transmission.
	uint32_t try_count = 0;

	// We have to check if the address is valid.
	if( address > 2047 ){

		// If not return with error.
		return HAL_ERROR;

	}

	// We have to check how many bytes we have to send.
	// We can send 8 bytes with one transfer maximum.
	if( size > 8 ){

		// If more than 8 bytes desired to send, we don't send the remaining bytes.
		size = 8;

	}

	// Configure the header.
	canTxHeader.DLC = size;			// size config
	canTxHeader.StdId = address;	// address config
	canTxHeader.IDE = CAN_ID_STD;	// Standard ID config
	canTxHeader.RTR = CAN_RTR_DATA;	// Data type config

	// Trying to add the message to the output queue.
	if( HAL_CAN_AddTxMessage( can_device, &canTxHeader, data, &canTxMailbox ) != HAL_OK ){

		// If it fails return with error.
		return HAL_ERROR;

	}

	// Check the status of the message.
	pending = HAL_CAN_IsTxMessagePending( can_device, canTxMailbox );

	// Wait until it gets sent out or timeout occurs.
	while( pending ){

		// Increment the try_count variable.
		try_count++;

		// Check if timeout happened.
		if( try_count >= timeout ){

			// If timeout happened abort the request.
			HAL_CAN_AbortTxRequest( can_device, canTxMailbox );

			// Return with timeout error.
			return HAL_TIMEOUT;

		}

		// Delay 1ms.
		delay( 1 );

		// Check the status of the message again.
		pending = HAL_CAN_IsTxMessagePending( can_device, canTxMailbox );

	}

	// If the message is sent and timeout not occurred return with HAL_OK.
	return HAL_OK;

}

uint32_t CANdalorian::available(){

	// This variable will store the result.
	uint32_t res;

	// Check if peripheral is in master or slave mode.
	if( slave_address == 0 ){

		// In master mode we have to read from FIFO0
		res = HAL_CAN_GetRxFifoFillLevel( can_device, CAN_RX_FIFO0 );

	}

	else{

		// In slave mode we have to read from FIFO1
		res = HAL_CAN_GetRxFifoFillLevel( can_device, CAN_RX_FIFO1 );

	}

	// Return the result.
	return res;
}

HAL_StatusTypeDef CANdalorian::read( uint8_t *data, uint8_t *size, uint32_t *addr ){

	// This variable will store the message header
	CAN_RxHeaderTypeDef canRxHeader;

	// Check if peripheral is in master or slave mode.
	if( slave_address == 0 ){

		// Try to read out the message from the FIFO. In master mode we have to read from FIFO0.
		if( HAL_CAN_GetRxMessage( can_device, CAN_RX_FIFO0, &canRxHeader, data ) != HAL_OK ){

			// If there was a problem while reading out the data we have to zero out the size, and the address.
			*size = 0;
			*addr = 0;

			// We have to return with an error.
			return HAL_ERROR;

		}

	}

	else{

		// Try to read out the message from the FIFO. In slave mode we have to read from FIFO1.
		if( HAL_CAN_GetRxMessage( can_device, CAN_RX_FIFO1, &canRxHeader, data ) != HAL_OK ){

			// If there was a problem while reading out the data we have to zero out the size, and the address.
			*size = 0;
			*addr = 0;

			// We have to return with an error.
			return HAL_ERROR;

		}

	}

	// If the reading was successful we have to return the size of the message.
	*size = canRxHeader.DLC;

	// We also have to return the address of the destination node.
	*addr = canRxHeader.StdId;

	// Return with HAL_OK.
	return HAL_OK;

}
