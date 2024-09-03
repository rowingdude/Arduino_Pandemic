
#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include "../include/constants.h"

#define MAX_PLAYERS 4

typedef struct {
    uint8_t location;
} Player;

extern Player players[MAX_PLAYERS];

void initializePlayers();
bool movePlayer(uint8_t playerIndex, uint8_t destination);
void displayPlayerLocation(uint8_t playerIndex);

#endif // PLAYER_H

