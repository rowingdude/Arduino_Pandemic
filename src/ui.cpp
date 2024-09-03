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

#include "ui.h"
#include "player_actions.h"

const uint8_t buttonPins[] = {28, 29, 30, 31};
uint8_t lastButtonStates[4] = {HIGH, HIGH, HIGH, HIGH};
uint32_t lastDebounceTimes[4] = {0};
const uint32_t debounceDelay = 50;

void initializeButtons() {
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void handleButtonInputs() {
  uint32_t currentTime = millis();
  for (int i = 0; i < 4; i++) {
    uint8_t reading = digitalRead(buttonPins[i]);
    if (reading != lastButtonStates[i]) {
      lastDebounceTimes[i] = currentTime;
    }
    if ((currentTime - lastDebounceTimes[i]) > debounceDelay) {
      if (reading == LOW) {
        performAction(i);
      }
    }
    lastButtonStates[i] = reading;
  }
}

void performAction(uint8_t actionIndex) {
  static const ActionFunction actions[] = {
    movePlayer,
    treatDisease,
    buildResearchStation,
    shareKnowledge
  };
  actions[actionIndex]();
  decrementActionsRemaining();
}