#include "player.h"
#include "city_map.h"
#include "ui.h"

Player players[MAX_PLAYERS];

void initializePlayers() {
    for (uint8_t i = 0; i < MAX_PLAYERS; i++) {
        players[i].location = ATLANTA; 
    }
}  // Function initializes all players' starting locations

bool movePlayer(uint8_t playerIndex, uint8_t destination) {
    if (playerIndex >= MAX_PLAYERS) return false;
    
    if (areCitiesConnected(players[playerIndex].location, destination)) {
        players[playerIndex].location = destination;
        displayPlayerLocation(playerIndex);
        return true;
    }
    return false;
}  // Function moves a player to a connected city

void displayPlayerLocation(uint8_t playerIndex) {
    updatePlayerLocationDisplay(playerIndex, players[playerIndex].location);
}  // Function updates the display with the player's new location