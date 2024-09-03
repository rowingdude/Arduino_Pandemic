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

#include "game_state.h"
#include "city_map.h"
#include "random_generator.h"

uint8_t currentPlayer = 0;
uint8_t actionsRemaining = MAX_ACTIONS;
uint8_t outbreakLevel = 0;
uint8_t infectionRate = 2;

void initializeGameState() {
  currentPlayer = 0;
  actionsRemaining = MAX_ACTIONS;
  outbreakLevel = 0;
  infectionRate = 2;
}

void decrementActionsRemaining() {
  actionsRemaining--;
  if (actionsRemaining == 0) {
    endPlayerTurn();
  }
}

void endPlayerTurn() {
  currentPlayer = (currentPlayer + 1) % PLAYER_COUNT;
  actionsRemaining = MAX_ACTIONS;
  drawPlayerCards();
  infectCities();
}

void drawPlayerCards() {
  // Implement player card drawing logic
}

void infectCities() {
  for (int i = 0; i < infectionRate; i++) {
    incrementCityInfection(getRandomCity());
  }
}