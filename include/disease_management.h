#ifndef DISEASE_MANAGEMENT_H
#define DISEASE_MANAGEMENT_H

#include <stdint.h>

#define DISEASE_COUNT 4
#define MAX_CUBES_PER_DISEASE 24

extern uint8_t diseaseCubes[DISEASE_COUNT];
extern uint8_t curedDiseases;

void initializeDiseases();
bool addDiseaseCube(uint8_t cityIndex, uint8_t diseaseType);
bool removeDiseaseCube(uint8_t cityIndex, uint8_t diseaseType);
bool isDiseaseCured(uint8_t diseaseType);
void cureDisease(uint8_t diseaseType);
void eradicateDisease(uint8_t diseaseType);
void handleEpidemic();

#endif // DISEASE_MANAGEMENT_H