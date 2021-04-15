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

class GPIO{

public:
	GPIO( GPIO_TypeDef* gpioPort_p, uint16_t gpioPin_p );

	void write( GPIO_PinState PinState );
	void write( int PinState );
	void write( bool PinState );

	void set();
	void reset();

	void on();
	void off();

	void toggle();

	GPIO_PinState read();

private:
	 GPIO_TypeDef* gpioPort = NULL;
	 uint16_t gpioPin = 0;
};



#endif /* STM32_CLASS_FACTORY_GPIO_GPIO_CLASS_HPP_ */
