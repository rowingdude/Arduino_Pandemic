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
#include "rng.h"
#include "card_management.h"

uint8_t currentPlayer = 0;
uint8_t actionsRemaining = MAX_ACTIONS;
uint8_t outbreakLevel = 0;
uint8_t infectionRate = 2;

void initializeGameState() {
    currentPlayer = 0;
    actionsRemaining = MAX_ACTIONS;
    outbreakLevel = 0;
    infectionRate = 2;
}  // Function initializes the game state variables

void decrementActionsRemaining() {
    actionsRemaining = (actionsRemaining - 1) & 0x03;  // Wrap around to 3 if it becomes -1
    endPlayerTurn();
}  // Function decrements actions and potentially ends turn

void endPlayerTurn() {
    currentPlayer = (currentPlayer + 1) & 0x03;  // Wrap around to 0-3
    actionsRemaining = MAX_ACTIONS;
    drawPlayerCards();
    infectCities();
}  // Function ends current player's turn and sets up next player

void drawPlayerCards() {
    drawPlayerCard();
    drawPlayerCard();
}  // Function draws two player cards

void infectCities() {
    for (uint8_t i = 0; i < infectionRate; i++) {
        incrementCityInfection(getRandomCity());
    }
}  // Function infects cities based on current infection rate