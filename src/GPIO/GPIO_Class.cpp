/*
* Created on April 5 2020
*
* Copyright (c) 2020 - Daniel Hajnal
* hajnal.daniel96@gmail.com
*
* This file is part of the STM32 Class Factory project.
*/

#include "GPIO_Class.hpp"

GPIO::GPIO( GPIO_TypeDef* gpioPort_p, uint16_t gpioPin_p ){

	gpioPort = gpioPort_p;
	gpioPin = gpioPin_p;

}

void GPIO::write( GPIO_PinState PinState ){

	if( gpioPort == NULL ){

		return;

	}

	HAL_GPIO_WritePin( gpioPort, gpioPin, PinState );

}

void GPIO::write( int PinState ){

	if( gpioPort == NULL ){

		return;

	}

	if( PinState ){

		HAL_GPIO_WritePin( gpioPort, gpioPin, GPIO_PIN_SET );

	}

	else{

		HAL_GPIO_WritePin( gpioPort, gpioPin, GPIO_PIN_RESET );

	}


}

void GPIO::write( bool PinState ){

	if( gpioPort == NULL ){

		return;

	}

	if( PinState ){

		HAL_GPIO_WritePin( gpioPort, gpioPin, GPIO_PIN_SET );

	}

	else{

		HAL_GPIO_WritePin( gpioPort, gpioPin, GPIO_PIN_RESET );

	}


}

void GPIO::toggle(){

	if( gpioPort == NULL ){

		return;

	}

	HAL_GPIO_TogglePin( gpioPort, gpioPin );

}

GPIO_PinState GPIO::read(){

	if( gpioPort == NULL ){

		return GPIO_PIN_RESET;

	}

	return HAL_GPIO_ReadPin( gpioPort, gpioPin );

}

void GPIO::set(){

	if( gpioPort == NULL ){

		return;

	}

	HAL_GPIO_WritePin( gpioPort, gpioPin, GPIO_PIN_SET );

}

void GPIO::reset(){

	if( gpioPort == NULL ){

		return;

	}

	HAL_GPIO_WritePin( gpioPort, gpioPin, GPIO_PIN_RESET );

}

void GPIO::on(){

		if( gpioPort == NULL ){

			return;

		}

		HAL_GPIO_WritePin( gpioPort, gpioPin, GPIO_PIN_SET );

}
void GPIO::off(){

		if( gpioPort == NULL ){

			return;

		}

		HAL_GPIO_WritePin( gpioPort, gpioPin, GPIO_PIN_RESET );

}
