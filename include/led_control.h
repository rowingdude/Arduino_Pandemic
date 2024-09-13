/******************************************************************************
 * Author: Benjamin Cance
 * Game: Arduino Pandemic for the Mega2560
 * Date: 3-Sept-2024
 * Version: 1.0
 * 
 * This file is part of the Arduino Pandemic project, a faithful 
 * implementation of the Pandemic board game for the Mega2560 platform.
 * 
 * Copyright (c) 2024 Benjamin Cance
 * 
 * MIT License
 *****************************************************************************/

 
#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <stdint.h>
#include <Adafruit_NeoPixel.h>

void initializeLEDs();
void updateCityLEDs(uint8_t cityIndex);

#endif // LED_CONTROL_H