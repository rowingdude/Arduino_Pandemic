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
#include "disease_management.h"

static uint8_t diseaseCubes[DISEASE_COUNT] = {24, 24, 24, 24};
static uint8_t curedDiseases = 0;

void initializeDiseases() {
    for (uint8_t i = 0; i < CITY_COUNT; i++) {
        diseaseCubes[i] = 0;
    }
}  // Function initializes disease cube counts for all cities

bool addDiseaseCube(uint8_t cityIndex) {
    if (diseaseCubes[cityIndex] < MAX_CUBES_PER_CITY) {
        diseaseCubes[cityIndex]++;
        updateCityLEDs(cityIndex);
        return true;
    } else {
        spreadDisease(cityIndex);
        return false;
    }
}  // Function adds a disease cube to a city, triggers spread if at max

void removeDiseaseCube(uint8_t cityIndex) {
    if (diseaseCubes[cityIndex] > 0) {
        diseaseCubes[cityIndex]--;
        updateCityLEDs(cityIndex);
    }
}  // Function removes a disease cube from a city

void spreadDisease(uint8_t startCity) {
    for (uint8_t i = 0; i < CITY_COUNT; i++) {
        if (areCitiesConnected(startCity, i)) {
            addDiseaseCube(i);
        }
    }
}  // Function spreads disease to all connected cities

bool isDiseaseCured(uint8_t diseaseType) {
    return (curedDiseases >> diseaseType) & 1;
}  // Function checks if a disease is cured

void setDiseaseCured(uint8_t diseaseType) {
    curedDiseases |= (1 << diseaseType);
}  // Function sets a disease as cured