#ifndef CARD_MANAGEMENT_H
#define CARD_MANAGEMENT_H

#include <stdint.h>

#define PLAYER_DECK_SIZE 60
#define INFECTION_DECK_SIZE 48

typedef enum {
    CARD_CITY,
    CARD_EPIDEMIC,
    CARD_EVENT
} CardType;

typedef struct {
    CardType type;
    uint8_t value; // City index for city cards, event type for event cards
} Card;

extern Card playerDeck[PLAYER_DECK_SIZE];
extern Card infectionDeck[INFECTION_DECK_SIZE];
extern uint8_t playerDeckTop, infectionDeckTop;

void initializeDecks();
Card drawPlayerCard();
Card drawInfectionCard();
void shufflePlayerDeck();
void shuffleInfectionDeck();
void addEpidemicCards(uint8_t numEpidemicCards);

#endif // CARD_MANAGEMENT_H