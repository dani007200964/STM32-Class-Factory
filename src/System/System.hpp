/*
* Created on April 5 2020
*
* Copyright (c) 2020 - Daniel Hajnal
* hajnal.daniel96@gmail.com
*
* This file is part of the STM32 Class Factory project.
*/

#ifndef STM32_CLASS_FACTORY_SYSTEM_SYSTEM_HPP_
#define STM32_CLASS_FACTORY_SYSTEM_SYSTEM_HPP_


#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<inttypes.h>
#include<stdint.h>

#include "stm32f4xx_hal.h"

/// Macro to emulate Arduino delay function
#define delay( x ) HAL_Delay( x )

/// Macro to emulate Arduino millis function
#define millis() HAL_GetTick()

#endif /* STM32_CLASS_FACTORY_SYSTEM_SYSTEM_HPP_ */
