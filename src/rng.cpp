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

#include "random_generator.h"

#define ENTROPY_PIN1 A8
#define ENTROPY_PIN2 A9
#define ENTROPY_PIN3 A10

static uint32_t state;

void initializeRandomGenerator() {
  state = generateRandomSeed();
}

uint32_t generateRandomSeed() {
  uint32_t seed = 0;
  for (int i = 0; i < 32; i++) {
    seed = (seed << 1) | (analogRead(ENTROPY_PIN1) & 1);
    seed ^= (analogRead(ENTROPY_PIN2) & 1) << 16;
    seed ^= (analogRead(ENTROPY_PIN3) & 1) << 8;
  }
  return seed;
}

uint32_t getRandomNumber() {
  state ^= state << 13;
  state ^= state >> 17;
  state ^= state << 5;
  return state;
}

uint8_t getRandomCity() {
  return getRandomNumber() % CITY_COUNT;
}