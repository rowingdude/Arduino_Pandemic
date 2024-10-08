#include "game_logic.h"
#include "player.h"
#include "disease_management.h"
#include "card_management.h"
#include "city_map.h"
#include "ui.h"

GameState gameState;

void initializeGame(uint8_t numPlayers, uint8_t difficulty) {
    initializeCityMap();
    initializeDiseases();
    initializeDecks();
    initializePlayers(numPlayers);
    
    setInitialInfections();
    dealInitialPlayerCards();
    addEpidemicCards(difficulty);
}

void runGameLoop() {
    while (!isGameOver()) {
        // Player actions phase
        for (uint8_t i = 0; i < 4; i++) {
            performPlayerAction(currentPlayerIndex);
        }
        
        // Draw cards phase
        drawPlayerCards(currentPlayerIndex, 2);
        
        // Infect cities phase
        infectCities();
        
        // Move to next player
        currentPlayerIndex = (currentPlayerIndex + 1) % MAX_PLAYERS;
    }
    
    displayGameResult();
}

void performPlayerAction(uint8_t playerIndex) {
    uint8_t action = getUserAction();
    switch (action) {
        case ACTION_MOVE:
            handlePlayerMove(playerIndex);
            break;
        case ACTION_TREAT:
            if (players[playerIndex].role == ROLE_MEDIC) {
                medicTreatDisease(playerIndex, players[playerIndex].location);
            } else {
                handleTreatDisease(playerIndex);
            }
            break;
        case ACTION_BUILD:
            if (players[playerIndex].role == ROLE_OPERATIONS_EXPERT) {
                operationsExpertBuildStation(playerIndex);
            } else {
                handleBuildResearchStation(playerIndex);
            }
            break;
        case ACTION_CURE:
            if (players[playerIndex].role == ROLE_SCIENTIST) {
                scientistDiscoverCure(playerIndex);
            } else {
                handleDiscoverCure(playerIndex);
            }
            break;
        case ACTION_SHARE_KNOWLEDGE:
            if (players[playerIndex].role == ROLE_RESEARCHER) {
                uint8_t targetPlayer = getTargetPlayer();
                uint8_t cardIndex = getCardToShare();
                researcherShareKnowledge(playerIndex, targetPlayer, cardIndex);
            } else {
                handleShareKnowledge(playerIndex);
            }
            break;
        case ACTION_DISPATCHER_MOVE:
            if (players[playerIndex].role == ROLE_DISPATCHER) {
                uint8_t targetPlayer = getTargetPlayer();
                uint8_t destination = getDestinationCity();
                dispatcherMovePlayer(playerIndex, targetPlayer, destination);
            }
            break;
        case ACTION_CONTINGENCY_PLANNER_STORE:
            if (players[playerIndex].role == ROLE_CONTINGENCY_PLANNER) {
                uint8_t cardIndex = getEventCardFromDiscard();
                contingencyPlannerStoreEventCard(playerIndex, cardIndex);
            }
            break;
    }
}


void drawPlayerCards(uint8_t playerIndex, uint8_t numCards) {
    for (uint8_t i = 0; i < numCards; i++) {
        Card drawnCard = drawPlayerCard();
        if (drawnCard.type == CARD_EPIDEMIC) {
            handleEpidemic();
        } else {
            addCardToPlayer(playerIndex, drawnCard);
        }
    }
}


void infectCities() {
    uint8_t infectionRate = getInfectionRate();
    for (uint8_t i = 0; i < infectionRate; i++) {
        Card infectionCard = drawInfectionCard();
        if (!isQuarantineProtected(infectionCard.value)) {
            addDiseaseCube(infectionCard.value, getCityDiseaseType(infectionCard.value));
        }
    }
}

bool isGameOver() {
    // Check win conditions
    if (areAllDiseasesCured()) {
        gameState.result = GAME_WIN;
        return true;
    }
    
    // Check lose conditions
    if (isOutbreakLimitReached() || arePlayerCardsExhausted() || areDiseaseCubesExhausted()) {
        gameState.result = GAME_LOSE;
        return true;
    }
    
    return false;
}