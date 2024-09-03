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
    for (int i = 0; i < DISEASE_COUNT; i++) {
        diseaseCubes[i] = 24;
    }
    curedDiseases = 0;
}  // Function initializes disease cubes and cure status

void addDiseaseCube(uint8_t cityIndex, uint8_t diseaseType) {
    diseaseCubes[diseaseType] = (diseaseCubes[diseaseType] > 0) * (diseaseCubes[diseaseType] - 1);
    // City infection logic to be implemented
}  // Function adds a disease cube to a city

void removeDiseaseCube(uint8_t cityIndex, uint8_t diseaseType) {
    diseaseCubes[diseaseType] = (diseaseCubes[diseaseType] < 24) * (diseaseCubes[diseaseType] + 1);
    // City disinfection logic to be implemented
}  // Function removes a disease cube from a city

bool isDiseaseCured(uint8_t diseaseType) {
    return (curedDiseases >> diseaseType) & 1;
}  // Function checks if a disease is cured

void setDiseaseCured(uint8_t diseaseType) {
    curedDiseases |= (1 << diseaseType);
}  // Function sets a disease as cured