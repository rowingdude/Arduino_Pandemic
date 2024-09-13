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

#ifndef UI_H
#define UI_H

#include <stdint.h>

void initializeButtons();
void handleButtonInputs();
void performAction(uint8_t actionIndex);
void updateLCDDisplay();

#endif // UI_H