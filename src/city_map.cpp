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
uint8_t researchCenters = 0;
uint8_t cityHasResearchCenter[CITY_COUNT / 8 + 1] = {0};

void setupCityMap() {
    initializeCityMap();
    setupCityConnections();
    shuffleCities();
    setInitialInfections();
}

void initializeCityMap() {
    researchCenters = 0;
    for (uint8_t i = 0; i < (CITY_COUNT / 8 + 1); i++) {
        cityHasResearchCenter[i] = 0;
    }
    addResearchCenter(ATLANTA); // Default placement
}  // Function initializes the city map and places initial research center

bool addResearchCenter(uint8_t cityIndex) {
    if (researchCenters >= MAX_RESEARCH_CENTERS || hasResearchCenter(cityIndex)) {
        return false;
    }
    
    cityHasResearchCenter[cityIndex / 8] |= (1 << (cityIndex % 8));
    researchCenters++;
    updateCityLEDs(cityIndex);  // Update LED to show research center
    return true;
}  // Function adds a research center to a city if possible

bool hasResearchCenter(uint8_t cityIndex) {
    return cityHasResearchCenter[cityIndex / 8] & (1 << (cityIndex % 8));
}  // Function checks if a city has a research center

void removeResearchCenter(uint8_t cityIndex) {
    if (hasResearchCenter(cityIndex)) {
        cityHasResearchCenter[cityIndex / 8] &= ~(1 << (cityIndex % 8));
        researchCenters--;
        updateCityLEDs(cityIndex);  // Update LED to show removal of research center
    }
}  // Function removes a research center from a city
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
    for (uint8_t i = 0; i < CITY_COUNT; i++) {
        if (areCitiesConnected(cityIndex, i)) {
            incrementCityInfection(i);
        }
    }
}