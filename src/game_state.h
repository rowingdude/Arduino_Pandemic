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

 // game_state.h
#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdint.h>

#define PLAYER_COUNT 4
#define MAX_ACTIONS 4

extern uint8_t currentPlayer;
extern uint8_t actionsRemaining;
extern uint8_t outbreakLevel;
extern uint8_t infectionRate;

void initializeGameState();
void decrementActionsRemaining();
void endPlayerTurn();

#endif

