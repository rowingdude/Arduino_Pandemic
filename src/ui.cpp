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
}  // Function initializes button pins

void handleButtonInputs() {
    uint32_t currentTime = millis();
    for (int i = 0; i < 4; i++) {
        uint8_t reading = digitalRead(buttonPins[i]);
        uint8_t timeDiff = currentTime - lastDebounceTimes[i];
        lastDebounceTimes[i] += (reading != lastButtonStates[i]) * timeDiff;
        performAction(i * (reading == LOW && timeDiff > debounceDelay));
        lastButtonStates[i] = reading;
    }
}  // Function handles button inputs with debouncing

void performAction(uint8_t actionIndex) {
    static const ActionFunction actions[] = {
        movePlayer,
        treatDisease,
        buildResearchStation,
        shareKnowledge
    };
    actions[actionIndex]();
}  // Function performs the action corresponding to the button pressed

void updateLCDDisplay() {
    // Placeholder for LCD update logic
}  // Function updates the LCD display (to be implemented)