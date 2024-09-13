#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include "city_map.h"

#define MAX_PLAYERS 4
#define MAX_CARDS_PER_PLAYER 7

typedef struct {
    uint8_t location;
    uint8_t cards[MAX_CARDS_PER_PLAYER];
    uint8_t cardCount;
    uint8_t role;  // You can define roles as constants
} Player;

extern Player players[MAX_PLAYERS];
extern uint8_t currentPlayerIndex;

void initializePlayers(uint8_t playerCount);
bool movePlayer(uint8_t playerIndex, uint8_t destination);
bool treatDisease(uint8_t playerIndex, uint8_t cityIndex);
bool buildResearchStation(uint8_t playerIndex);
void drawPlayerCard(uint8_t playerIndex);
void discardPlayerCard(uint8_t playerIndex, uint8_t cardIndex);

#endif // PLAYER_H