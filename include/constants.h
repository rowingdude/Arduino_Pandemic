// include/constants.h

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <avr/pgmspace.h>

#define CITY_COUNT 48

// City indices
enum CityIndex {
    SAN_FRANCISCO, CHICAGO, MONTREAL, NEW_YORK, WASHINGTON, ATLANTA, LONDON, MADRID,
    PARIS, MILAN, ST_PETERSBURG, ESSEN, MOSCOW, ISTANBUL, ALGIERS, CAIRO,
    BAGHDAD, RIYADH, KARACHI, MUMBAI, DELHI, CHENNAI, KOLKATA, BANGKOK,
    JAKARTA, HO_CHI_MINH_CITY, HONG_KONG, SHANGHAI, BEIJING, SEOUL, TOKYO, OSAKA,
    TAIPEI, MANILA, SYDNEY, LOS_ANGELES, MEXICO_CITY, MIAMI, BOGOTA, LIMA,
    SANTIAGO, BUENOS_AIRES, SAO_PAULO, LAGOS, KHARTOUM, KINSHASA, JOHANNESBURG, TEHRAN
};

// City connection matrix
// This uses a binary hash table to show all city connections.

const uint8_t PROGMEM cityConnections[CITY_COUNT][CITY_COUNT / 8] = {
    {0b01000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001, 0b00000001}, // San Francisco
    {0b10100100, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00100000}, // Chicago
    {0b00011000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000}, // Montreal
    {0b00001010, 0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00010000}, // New York
    {0b00000101, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00010000}, // Washington
    {0b00000010, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00110000}, // Atlanta
    {0b00000001, 0b01100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000}, // London
    {0b00000000, 0b10010000, 0b00000000, 0b00000000, 0b00000000, 0b00001000}, // Madrid
    {0b00000000, 0b01001100, 0b00000000, 0b00000000, 0b00000000, 0b00000000}, // Paris
    {0b00000000, 0b00100010, 0b00000000, 0b00000000, 0b00000000, 0b00000000}, // Milan
    {0b00000000, 0b00010001, 0b00000000, 0b00000000, 0b00000000, 0b00000000}, // St. Petersburg
    {0b00000000, 0b00001010, 0b00000000, 0b00000000, 0b00000000, 0b00000000}, // Essen
    {0b00000000, 0b00000101, 0b00000001, 0b00000000, 0b00000000, 0b00000000}, // Moscow
    {0b00000000, 0b00000000, 0b10001010, 0b00000000, 0b00000000, 0b00000000}, // Istanbul
    {0b00000000, 0b00000000, 0b01000001, 0b00000000, 0b00000000, 0b00001000}, // Algiers
    {0b00000000, 0b00000000, 0b00100100, 0b00000000, 0b00000000, 0b00001000}, // Cairo
    {0b00000000, 0b00000000, 0b00010010, 0b00000100, 0b00000000, 0b00000000}, // Baghdad
    {0b00000000, 0b00000000, 0b00001000, 0b00000010, 0b00000000, 0b00000000}, // Riyadh
    {0b00000000, 0b00000000, 0b00000001, 0b00011001, 0b00000000, 0b00000000}, // Karachi
    {0b00000000, 0b00000000, 0b00000000, 0b10000110, 0b00000000, 0b00000000}, // Mumbai
    {0b00000000, 0b00000000, 0b00000000, 0b01100010, 0b00000000, 0b00000000}, // Delhi
    {0b00000000, 0b00000000, 0b00000000, 0b00010001, 0b00110000, 0b00000000}, // Chennai
    {0b00000000, 0b00000000, 0b00000000, 0b00001000, 0b01001000, 0b00000000}, // Kolkata
    {0b00000000, 0b00000000, 0b00000000, 0b00000100, 0b10100100, 0b00000000}, // Bangkok
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00010010, 0b00000100}, // Jakarta
    {0b00000000, 0b00000000, 0b00000000, 0b00000010, 0b01000001, 0b00000000}, // Ho Chi Minh City
    {0b00000000, 0b00000000, 0b00000000, 0b00000001, 0b10101000, 0b00000000}, // Hong Kong
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00010100, 0b00000000}, // Shanghai
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001010, 0b00000000}, // Beijing
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000101, 0b00000000}, // Seoul
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000010, 0b10000000}, // Tokyo
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001, 0b01000000}, // Osaka
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11100000}, // Taipei
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00110000}, // Manila
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00001000}, // Sydney
    {0b10000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000110}, // Los Angeles
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000011}, // Mexico City
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01001000}, // Miami
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00110100}, // Bogota
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000110}, // Lima
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001}, // Santiago
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000010}, // Buenos Aires
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100}, // Sao Paulo
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000010}, // Lagos
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000101}, // Khartoum
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000010}, // Kinshasa
    {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000001}, // Johannesburg
    {0b00000000, 0b00000000, 0b00000000, 0b00000100, 0b00000000, 0b00000000}  // Tehran
};

// Function to check if two cities are connected
inline bool areCitiesConnected(uint8_t city1, uint8_t city2) {
    uint8_t byte = pgm_read_byte(&cityConnections[city1][city2 / 8]);
    return byte & (1 << (city2 % 8));
}

#endif // CONSTANTS_H