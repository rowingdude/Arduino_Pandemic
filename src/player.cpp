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

bool medicTreatDisease(uint8_t playerIndex, uint8_t cityIndex) {
    if (players[playerIndex].role != ROLE_MEDIC || players[playerIndex].location != cityIndex) {
        return false;
    }
    
    uint8_t diseaseType = getCityDiseaseType(cityIndex);
    bool cured = isDiseaseCured(diseaseType);
    
    // Medic removes all cubes of a single disease
    while (getCityInfectionLevel(cityIndex) > 0) {
        removeDiseaseCube(cityIndex, diseaseType);
    }
    
    // If the disease is cured, automatically remove cubes in every city the Medic enters
    if (cured) {
        for (uint8_t i = 0; i < CITY_COUNT; i++) {
            if (areCitiesConnected(players[playerIndex].location, i)) {
                while (getCityInfectionLevel(i) > 0) {
                    removeDiseaseCube(i, diseaseType);
                }
            }
        }
    }
    
    return true;
}

bool scientistDiscoverCure(uint8_t playerIndex) {
    if (players[playerIndex].role != ROLE_SCIENTIST) {
        return false;
    }
    
    // Scientist needs only 4 cards to cure a disease instead of 5
    uint8_t requiredCards = 4;
    uint8_t cityCardsOfSameColor = 0;
    uint8_t diseaseType = 0xFF;
    
    for (uint8_t i = 0; i < players[playerIndex].cardCount; i++) {
        if (players[playerIndex].cards[i].type == CARD_CITY) {
            uint8_t cardDiseaseType = getCityDiseaseType(players[playerIndex].cards[i].value);
            if (diseaseType == 0xFF || diseaseType == cardDiseaseType) {
                diseaseType = cardDiseaseType;
                cityCardsOfSameColor++;
            }
        }
    }
    
    if (cityCardsOfSameColor >= requiredCards && hasResearchCenter(players[playerIndex].location)) {
        cureDisease(diseaseType);
        // Discard the used cards
        // (You'll need to implement a way to select which cards to discard if there are more than 4)
        return true;
    }
    
    return false;
}

bool researcherShareKnowledge(uint8_t playerIndex, uint8_t targetPlayerIndex, uint8_t cardIndex) {
    if (players[playerIndex].role != ROLE_RESEARCHER) {
        return false;
    }
    
    // Researcher can give any city card to another player in the same city
    if (players[playerIndex].location == players[targetPlayerIndex].location &&
        cardIndex < players[playerIndex].cardCount &&
        players[playerIndex].cards[cardIndex].type == CARD_CITY) {
        
        if (players[targetPlayerIndex].cardCount < MAX_CARDS_PER_PLAYER) {
            players[targetPlayerIndex].cards[players[targetPlayerIndex].cardCount++] = players[playerIndex].cards[cardIndex];
            discardPlayerCard(playerIndex, cardIndex);
            return true;
        }
    }
    
    return false;
}

bool operationsExpertBuildStation(uint8_t playerIndex) {
    if (players[playerIndex].role != ROLE_OPERATIONS_EXPERT) {
        return false;
    }
    
    // Operations Expert can build a research station without discarding a city card
    return addResearchCenter(players[playerIndex].location);
}

bool quarantineSpecialistPreventInfection(uint8_t cityIndex) {
    for (uint8_t i = 0; i < MAX_PLAYERS; i++) {
        if (players[i].role == ROLE_QUARANTINE_SPECIALIST) {
            if (players[i].location == cityIndex || areCitiesConnected(players[i].location, cityIndex)) {
                return true; // Prevent infection in this city
            }
        }
    }
    return false;
}

bool dispatcherMovePlayer(uint8_t playerIndex, uint8_t targetPlayerIndex, uint8_t destination) {
    if (players[playerIndex].role != ROLE_DISPATCHER) {
        return false;
    }
    
    // Dispatcher can move any player to any city containing another player
    bool destinationHasPlayer = false;
    for (uint8_t i = 0; i < MAX_PLAYERS; i++) {
        if (i != targetPlayerIndex && players[i].location == destination) {
            destinationHasPlayer = true;
            break;
        }
    }
    
    if (destinationHasPlayer) {
        players[targetPlayerIndex].location = destination;
        return true;
    }
    
    return false;
}

bool contingencyPlannerStoreEventCard(uint8_t playerIndex, uint8_t cardIndex) {
    if (players[playerIndex].role != ROLE_CONTINGENCY_PLANNER) {
        return false;
    }
    
    // Contingency Planner can store an event card from the discard pile
    if (cardIndex < getDiscardPileSize() && getDiscardedCard(cardIndex).type == CARD_EVENT) {
        // Implement a way to store this card separately for the Contingency Planner
        // For simplicity, we'll just add it to their hand, but you might want to create a separate storage
        if (players[playerIndex].cardCount < MAX_CARDS_PER_PLAYER) {
            players[playerIndex].cards[players[playerIndex].cardCount++] = getDiscardedCard(cardIndex);
            removeCardFromDiscardPile(cardIndex);
            return true;
        }
    }
    
    return false;
}

bool isQuarantineProtected(uint8_t cityIndex) {
    for (uint8_t i = 0; i < MAX_PLAYERS; i++) {
        if (players[i].role == ROLE_QUARANTINE_SPECIALIST) {
            if (players[i].location == cityIndex) {
                return true; // The city is protected if the Quarantine Specialist is there
            }
            
            // Check if the Quarantine Specialist is in an adjacent city
            if (areCitiesConnected(players[i].location, cityIndex)) {
                return true;
            }
        }
    }
    return false;
}