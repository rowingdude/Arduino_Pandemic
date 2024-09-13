#include "city_connections.h"
#include <avr/pgmspace.h>

static HashNode* hashTable[HASH_TABLE_SIZE];

// Simple hash function
static uint8_t hash(uint8_t city1, uint8_t city2) {
    return ((city1 * 31) ^ city2) % HASH_TABLE_SIZE;
}

void initializeCityConnections() {
    for (uint8_t i = 0; i < HASH_TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

void addCityConnection(uint8_t city1, uint8_t city2) {
    uint8_t index = hash(city1, city2);
    
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->pair.city1 = city1 < city2 ? city1 : city2;
    newNode->pair.city2 = city1 < city2 ? city2 : city1;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

bool areCitiesConnected(uint8_t city1, uint8_t city2) {
    uint8_t index = hash(city1, city2);
    HashNode* current = hashTable[index];
    
    uint8_t minCity = city1 < city2 ? city1 : city2;
    uint8_t maxCity = city1 < city2 ? city2 : city1;
    
    while (current != NULL) {
        if (current->pair.city1 == minCity && current->pair.city2 == maxCity) {
            return true;
        }
        current = current->next;
    }
    
    return false;
}

// City connections data (stored in PROGMEM to save RAM)
const uint8_t PROGMEM cityConnectionsData[] = {
    // Add your city connections here, e.g.:
    0, 1,  // City 0 connected to City 1
    0, 2,  // City 0 connected to City 2
    1, 3,  // City 1 connected to City 3
    // ... add all connections
};

void setupCityConnections() {
    initializeCityConnections();
    
    uint8_t connectionsCount = sizeof(cityConnectionsData) / (2 * sizeof(uint8_t));
    for (uint8_t i = 0; i < connectionsCount; i++) {
        uint8_t city1 = pgm_read_byte(&cityConnectionsData[i * 2]);
        uint8_t city2 = pgm_read_byte(&cityConnectionsData[i * 2 + 1]);
        addCityConnection(city1, city2);
    }
}