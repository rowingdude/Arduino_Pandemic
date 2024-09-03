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

 
#ifndef CITY_MAP_H
#define CITY_MAP_H

#include <stdint.h>

#define CITY_COUNT 48
#define LEDS_PER_CITY 3

#define MAX_RESEARCH_CENTERS 6

extern uint8_t researchCenters;
extern uint8_t cityHasResearchCenter[CITY_COUNT / 8 + 1];
extern const char* cityNames[CITY_COUNT];
extern uint8_t cityInfectionLevels[CITY_COUNT];


void initializeCityMap();
bool addResearchCenter(uint8_t cityIndex);
bool hasResearchCenter(uint8_t cityIndex);
void removeResearchCenter(uint8_t cityIndex);
void shuffleCities();
void setInitialInfections();
void setCityInfectionLevel(uint8_t cityIndex, uint8_t level);
void incrementCityInfection(uint8_t cityIndex);
void triggerOutbreak(uint8_t cityIndex);

#endif // CITY_MAP_H