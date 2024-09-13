#include "player.h"
#include "city_connections.h"
#include "disease_management.h"
#include "card_management.h"

Player players[MAX_PLAYERS];
uint8_t currentPlayerIndex = 0;

void initializePlayers(uint8_t playerCount) {
    for (uint8_t i = 0; i < playerCount; i++) {
        players[i].location = ATLANTA;  // Assuming ATLANTA is defined as the starting city
        players[i].cardCount = 0;
        players[i].role = i;  // Simple role assignment, can be randomized later
    }
}

bool movePlayer(uint8_t playerIndex, uint8_t destination) {
    if (areCitiesConnected(players[playerIndex].location, destination)) {
        players[playerIndex].location = destination;
        return true;
    }
    return false;
}

bool treatDisease(uint8_t playerIndex, uint8_t cityIndex) {
    if (players[playerIndex].location == cityIndex) {
        return removeDiseasesCube(cityIndex);
    }
    return false;
}

bool buildResearchStation(uint8_t playerIndex) {
    uint8_t cityIndex = players[playerIndex].location;
    return addResearchCenter(cityIndex);
}

void drawPlayerCard(uint8_t playerIndex) {
    if (players[playerIndex].cardCount < MAX_CARDS_PER_PLAYER) {
        uint8_t newCard = drawCard();  // Implement this in card_management.cpp
        players[playerIndex].cards[players[playerIndex].cardCount++] = newCard;
    }
}

void discardPlayerCard(uint8_t playerIndex, uint8_t cardIndex) {
    if (cardIndex < players[playerIndex].cardCount) {
        discardCard(players[playerIndex].cards[cardIndex]);  // Implement this in card_management.cpp
        for (uint8_t i = cardIndex; i < players[playerIndex].cardCount - 1; i++) {
            players[playerIndex].cards[i] = players[playerIndex].cards[i + 1];
        }
        players[playerIndex].cardCount--;
    }
}