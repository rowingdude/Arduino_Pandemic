#include "card_management.h"
#include "rng.h"

Card playerDeck[PLAYER_DECK_SIZE];
Card infectionDeck[INFECTION_DECK_SIZE];
uint8_t playerDeckTop = 0, infectionDeckTop = 0;

void initializeDecks() {
    // Initialize player deck with city cards
    for (uint8_t i = 0; i < CITY_COUNT; i++) {
        playerDeck[i].type = CARD_CITY;
        playerDeck[i].value = i;
    }
    playerDeckTop = CITY_COUNT;

    // Initialize infection deck
    for (uint8_t i = 0; i < CITY_COUNT; i++) {
        infectionDeck[i].type = CARD_CITY;
        infectionDeck[i].value = i;
    }
    infectionDeckTop = CITY_COUNT;

    shufflePlayerDeck();
    shuffleInfectionDeck();
}

Card drawPlayerCard() {
    if (playerDeckTop > 0) {
        return playerDeck[--playerDeckTop];
    }
    // Handle game over condition here
    Card emptyCard = {CARD_CITY, 0xFF};
    return emptyCard;
}

Card drawInfectionCard() {
    if (infectionDeckTop > 0) {
        return infectionDeck[--infectionDeckTop];
    }
    // Handle empty infection deck (reshuffle discard pile)
    Card emptyCard = {CARD_CITY, 0xFF};
    return emptyCard;
}

void shufflePlayerDeck() {
    for (int i = playerDeckTop - 1; i > 0; i--) {
        int j = getRandomNumber() % (i + 1);
        Card temp = playerDeck[i];
        playerDeck[i] = playerDeck[j];
        playerDeck[j] = temp;
    }
}

void shuffleInfectionDeck() {
    for (int i = infectionDeckTop - 1; i > 0; i--) {
        int j = getRandomNumber() % (i + 1);
        Card temp = infectionDeck[i];
        infectionDeck[i] = infectionDeck[j];
        infectionDeck[j] = temp;
    }
}

void addEpidemicCards(uint8_t numEpidemicCards) {
    uint8_t deckSize = playerDeckTop;
    uint8_t sectionSize = deckSize / numEpidemicCards;

    for (uint8_t i = 0; i < numEpidemicCards; i++) {
        Card epidemicCard = {CARD_EPIDEMIC, 0};
        uint8_t insertPosition = i * sectionSize + (getRandomNumber() % sectionSize);
        
        // Shift cards to make room for the epidemic card
        for (uint8_t j = playerDeckTop; j > insertPosition; j--) {
            playerDeck[j] = playerDeck[j-1];
        }
        playerDeck[insertPosition] = epidemicCard;
        playerDeckTop++;
    }
}