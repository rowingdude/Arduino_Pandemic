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

uint8_t cityInfectionLevels[CITY_COUNT] = {0};

void shuffleCities() {
  for (int i = CITY_COUNT - 1; i > 0; i--) {
    int j = getRandomNumber() % (i + 1);
    const char* temp = cityNames[i];
    cityNames[i] = cityNames[j];
    cityNames[j] = temp;
  }
}

void setInitialInfections() {
  static const uint8_t initialInfections[] = {3, 3, 3, 2, 2, 2, 1, 1, 1};
  for (int i = 0; i < 9; i++) {
    setCityInfectionLevel(i, initialInfections[i]);
  }
}

void setCityInfectionLevel(uint8_t cityIndex, uint8_t level) {
  cityInfectionLevels[cityIndex] = level & 0x03; 
  updateCityLEDs(cityIndex);
}

void incrementCityInfection(uint8_t cityIndex) {
  uint8_t newLevel = (cityInfectionLevels[cityIndex] + 1) & 0x03; 
  setCityInfectionLevel(cityIndex, newLevel);
  
  if (newLevel == 0) {
    triggerOutbreak(cityIndex);
  }
}

void triggerOutbreak(uint8_t cityIndex) {
  // add an outbreak, triggering neighbors and future outbreaks.
}