#ifndef CITY_CONNECTIONS_H
#define CITY_CONNECTIONS_H

#include <stdint.h>
#include "city_map.h"

#define HASH_TABLE_SIZE 64  // Adjust based on your needs and available memory

typedef struct {
    uint8_t city1;
    uint8_t city2;
} CityPair;

typedef struct {
    CityPair pair;
    struct HashNode* next;
} HashNode;

void initializeCityConnections();
void addCityConnection(uint8_t city1, uint8_t city2);
bool areCitiesConnected(uint8_t city1, uint8_t city2);

#endif // CITY_CONNECTIONS_H