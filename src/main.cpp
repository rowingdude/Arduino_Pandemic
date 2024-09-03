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

#include <Arduino.h>
#include "game_state.h"
#include "city_map.h"
#include "player_actions.h"
#include "led_control.h"
#include "rng.h"
#include "ui.h"

void setup() {
  Serial.begin(9600);
  initializeRandomGenerator();
  initializeLEDs();
  initializeLCDs();
  initializeButtons();
  initializeGameState();
  shuffleCities();
  setInitialInfections();
  updateLCDDisplay();
}

void loop() {
  handleButtonInputs();
  // Add more stuff as we go... 
}