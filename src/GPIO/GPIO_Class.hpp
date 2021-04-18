/*
* Created on April 5 2020
*
* Copyright (c) 2020 - Daniel Hajnal
* hajnal.daniel96@gmail.com
*
* This file is part of the STM32 Class Factory project.
*/

#ifndef STM32_CLASS_FACTORY_GPIO_GPIO_CLASS_HPP_
#define STM32_CLASS_FACTORY_GPIO_GPIO_CLASS_HPP_

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<inttypes.h>
#include<stdint.h>

#include "stm32f4xx_hal.h"
#include "gpio.h"

/// GPIO class layer
///
/// GPIO class is an object layer above HAL_GPIO drivers.
/// With this library you can handle real life things( like a relay, a motor etc... )
/// as a simple object.
///
/// Example code:
/// \code{.cpp}
///
/// // Constructor for a Relay that is connected to
/// // PA7 on the MCU
/// GPIO Relay( GPIOA, GPIO_PIN_7 );
///
/// int main(){
///
/// // Turn on the relay
/// Relay.on();
///
/// // Wait 1000ms
/// delay( 1000 );
///
/// // Turn of the relay
/// Relay.off();
///
/// return 0;
///
/// }
///
/// \endcode
class GPIO{

public:

	/// GPIO object constructor
	///
	/// You can creat GPIO objects with this constructor.
	/// @param gpioPort_p  pointer ti a GPIO port.
	/// @gpioPin_p pin number
	/// @note gor example to refer PA7 pin you have to call the constructor like this: GPIO relay( GPIOA, GPIO_PIN_7  );
	GPIO( GPIO_TypeDef* gpioPort_p, uint16_t gpioPin_p );

	/// Write the GPIO
	///
	/// With this function you can set the state of the pin
	/// associated with the GPIO object.
	/// @param PinState the desired output state.
	void write( GPIO_PinState PinState );

	/// Write the GPIO
	///
	/// With this function you can set the state of the pin
	/// associated with the GPIO object.
	/// @param PinState the desired output state.
	void write( int PinState );

	/// Write the GPIO
	///
	/// With this function you can set the state of the pin
	/// associated with the GPIO object.
	/// @param PinState the desired output state.
	void write( bool PinState );

	/// Set the GPIO
	///
	/// With this function you can set the pin
	/// associated with the GPIO object.
	void set();

	/// Reset the GPIO
	///
	/// With this function you can reset the pin
	/// associated with the GPIO object.
	void reset();

	/// Set the GPIO
	///
	/// With this function you can set the pin
	/// associated with the GPIO object.
	/// @note This is the same as set().
	void on();

	/// Reset the GPIO
	///
	/// With this function you can reset the pin
	/// associated with the GPIO object.
	/// @note This is the same as reset().
	void off();

	/// Toggle the GPIO
	///
	/// With this function you can toggle state of the pin
	/// associated with the GPIO object.
	void toggle();

	/// Read the GPIO
	///
	/// With this function you can read state of the pin
	/// associated with the GPIO object.
	GPIO_PinState read();

private:

	/// Local copy of the GPIO Port
	GPIO_TypeDef* gpioPort = NULL;

	/// Local copy of the GPIO Pin
	uint16_t gpioPin = 0;
};



#endif /* STM32_CLASS_FACTORY_GPIO_GPIO_CLASS_HPP_ */
