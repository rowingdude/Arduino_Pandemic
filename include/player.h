#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include "city_map.h"

#define MAX_PLAYERS 4
#define MAX_CARDS_PER_PLAYER 7

typedef enum {
    ROLE_MEDIC,
    ROLE_SCIENTIST,
    ROLE_RESEARCHER,
    ROLE_OPERATIONS_EXPERT,
    ROLE_QUARANTINE_SPECIALIST,
    ROLE_DISPATCHER,
    ROLE_CONTINGENCY_PLANNER
} PlayerRole;

typedef struct {
    uint8_t location;
    uint8_t cards[MAX_CARDS_PER_PLAYER];
    uint8_t cardCount;
    PlayerRole role;
} Player;

extern Player players[MAX_PLAYERS];
extern uint8_t currentPlayerIndex;

void initializePlayers(uint8_t playerCount);
bool movePlayer(uint8_t playerIndex, uint8_t destination);
bool treatDisease(uint8_t playerIndex, uint8_t cityIndex);
bool buildResearchStation(uint8_t playerIndex);
void drawPlayerCard(uint8_t playerIndex);
void discardPlayerCard(uint8_t playerIndex, uint8_t cardIndex);

// New role-specific function declarations
bool medicTreatDisease(uint8_t playerIndex, uint8_t cityIndex);
bool scientistDiscoverCure(uint8_t playerIndex);
bool researcherShareKnowledge(uint8_t playerIndex, uint8_t targetPlayerIndex, uint8_t cardIndex);
bool operationsExpertBuildStation(uint8_t playerIndex);
bool quarantineSpecialistPreventInfection(uint8_t cityIndex);
bool dispatcherMovePlayer(uint8_t playerIndex, uint8_t targetPlayerIndex, uint8_t destination);
bool contingencyPlannerStoreEventCard(uint8_t playerIndex, uint8_t cardIndex);
bool isQuarantineProtected(uint8_t cityIndex);
#endif // PLAYER_H