#include "disease_management.h"
#include "city_map.h"
#include "card_management.h"

uint8_t diseaseCubes[DISEASE_COUNT] = {24, 24, 24, 24};
uint8_t curedDiseases = 0;

void initializeDiseases() {
    for (uint8_t i = 0; i < DISEASE_COUNT; i++) {
        diseaseCubes[i] = MAX_CUBES_PER_DISEASE;
    }
    curedDiseases = 0;
}

bool addDiseaseCube(uint8_t cityIndex, uint8_t diseaseType) {
    if (diseaseCubes[diseaseType] > 0) {
        diseaseCubes[diseaseType]--;
        incrementCityInfection(cityIndex);
        return true;
    }
    return false; // No more cubes available, trigger loss condition
}

bool removeDiseaseCube(uint8_t cityIndex, uint8_t diseaseType) {
    if (getCityInfectionLevel(cityIndex) > 0) {
        diseaseCubes[diseaseType]++;
        decrementCityInfection(cityIndex);
        return true;
    }
    return false;
}

bool isDiseaseCured(uint8_t diseaseType) {
    return (curedDiseases >> diseaseType) & 1;
}

void cureDisease(uint8_t diseaseType) {
    curedDiseases |= (1 << diseaseType);
}

void eradicateDisease(uint8_t diseaseType) {
    cureDisease(diseaseType);
    // Remove all cubes of this disease type from the board
    for (uint8_t i = 0; i < CITY_COUNT; i++) {
        while (getCityInfectionLevel(i) > 0) {
            removeDiseaseCube(i, diseaseType);
        }
    }
}

void handleEpidemic() {
    // 1. Increase: Move the infection rate marker forward
    increaseInfectionRate();

    // 2. Infect: Draw the bottom card of the infection deck
    Card bottomCard = drawBottomInfectionCard();
    // Add 3 cubes to the drawn city
    for (int i = 0; i < 3; i++) {
        addDiseaseCube(bottomCard.value, getCityDiseaseType(bottomCard.value));
    }

    // 3. Intensify: Shuffle the infection discard pile and put it on top of the infection deck
    shuffleInfectionDiscardPile();
}