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

 #include "game_logic.h"
#include "player.h"
#include "disease.h"
#include "random_generator.h"

void initializeGame() {
    initializePlayers();
    initializeDiseases();
    
    for (uint8_t i = 0; i < 9; i++) {
        uint8_t city = getRandomCity();
        addDiseaseCube(city);
        if (i < 6) addDiseaseCube(city);
        if (i < 3) addDiseaseCube(city);
    }
}  // Function initializes the game state

void performPlayerTurn(uint8_t playerIndex) {
    uint8_t actionsLeft = 4;
    while (actionsLeft > 0) {
        uint8_t action = getPlayerAction();
        switch (action) {
            case MOVE:
                {
                    uint8_t destination = getDestinationCity();
                    if (movePlayer(playerIndex, destination)) {
                        actionsLeft--;
                    }
                }
                break;
            case TREAT:
                {
                    uint8_t currentCity = players[playerIndex].location;
                    removeDiseaseCube(currentCity);
                    actionsLeft--;
                }
            case RESEARCHCTR:
                {
                    uint8_t currentCity = players[playerIndex].location;
                    if (addResearchCenter(currentCity)) {
                        actionsLeft--;
                    }
                }
                break;
        }
    }
    drawPlayerCards();
    infectCities();
}  // Function handles a player's turn

void infectCities() {
    uint8_t infectionRate = getCurrentInfectionRate();
    for (uint8_t i = 0; i < infectionRate; i++) {
        uint8_t city = getRandomCity();
        addDiseaseCube(city);
    }
}  // Function infects cities at the end of a turn