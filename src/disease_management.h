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

#ifndef DISEASE_MANAGEMENT_H
#define DISEASE_MANAGEMENT_H

#include <stdint.h>

#define DISEASE_COUNT 4

void initializeDiseases();
void addDiseaseCube(uint8_t cityIndex, uint8_t diseaseType);
void removeDiseaseCube(uint8_t cityIndex, uint8_t diseaseType);
bool isDiseaseCured(uint8_t diseaseType);
void setDiseaseCured(uint8_t diseaseType);

#endif // DISEASE_MANAGEMENT_H