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

 // led_control.cpp
#include "led_control.h"

#define LED_PIN 6
#define LED_COUNT 144

Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void initializeLEDs() {
  pixels.begin();
  pixels.clear();
  pixels.show();
}

void updateCityLEDs(uint8_t cityIndex) {
  uint8_t level = cityInfectionLevels[cityIndex];
  uint32_t color = level > 0 ? pixels.Color(255, 0, 0) : 0; // Red if infected, off otherwise
  
  uint16_t startLED = cityIndex * LEDS_PER_CITY;
  uint16_t endLED = startLED + level;
  
  for (uint16_t i = startLED; i < startLED + LEDS_PER_CITY; i++) {
    pixels.setPixelColor(i, i < endLED ? color : 0);
  }
  
  pixels.show();
}