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

#include "city_map.h"
#include "led_control.h"
#include "random_generator.h"
#include "disease_management.h"

const char* cityNames[CITY_COUNT] = {/* ... city names ... */};
uint8_t cityInfectionLevels[CITY_COUNT] = {0};

void shuffleCities() {
    for (int i = CITY_COUNT - 1; i > 0; i--) {
        int j = getRandomNumber() % (i + 1);
        const char* temp = cityNames[i];
        cityNames[i] = cityNames[j];
        cityNames[j] = temp;
    }
}  // Function shuffles the city names array

void setInitialInfections() {
    static const uint8_t initialInfections[] = {3, 3, 3, 2, 2, 2, 1, 1, 1};
    for (int i = 0; i < 9; i++) {
        setCityInfectionLevel(i, initialInfections[i]);
    }
}  // Function sets initial infection levels for 9 cities

void setCityInfectionLevel(uint8_t cityIndex, uint8_t level) {
    cityInfectionLevels[cityIndex] = level & 0x03;  // Limit to 0-3
    updateCityLEDs(cityIndex);
}  // Function sets infection level and updates LEDs

void incrementCityInfection(uint8_t cityIndex) {
    uint8_t newLevel = (cityInfectionLevels[cityIndex] + 1) & 0x03;
    setCityInfectionLevel(cityIndex, newLevel);
    triggerOutbreak(cityIndex * (newLevel == 0));
}  // Function increments infection level and potentially triggers outbreak

void triggerOutbreak(uint8_t cityIndex) {
    // Placeholder for outbreak logic
}  // Function handles city outbreak (to be implemented)