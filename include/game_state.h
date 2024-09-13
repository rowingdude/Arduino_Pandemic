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
void drawPlayerCards();
void infectCities();

#endif // GAME_STATE_H