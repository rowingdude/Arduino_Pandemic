/******************************************************************************
 * Author: Benjamin Cance
 * Game: Arduino Pandemic for the Mega2560
 * Date: 3-Sept-2024
 * Version: 1.0
 * 
 * This file is part of the Arduino Pandemic project, a faithful 
 * implementation of the Pandemic board game for the Mega2560 platform.
 *
 * The LED_CONTROL.cpp file aims to access and direct the NeoPixels directly 
 * We're using a lot resources on tracking game states, so the hope here is to 
 *   cut down on a little overhead by eliminating libraries and external calls.
 * 
 * Copyright (c) 2024 Benjamin Cance
 * 
 * MIT License
 *****************************************************************************/

#define LED_PORT PORTF
#define LED_DDR  DDRF
#define LED_PIN  PF6

void initializeLEDs() {
    LED_DDR |= _BV(LED_PIN);  // Set LED pin as output
}

void sendBit(uint8_t bit) {
    LED_PORT |= _BV(LED_PIN);
    asm volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
    if (!bit) LED_PORT &= ~_BV(LED_PIN);
    asm volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n"
                 "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
    LED_PORT &= ~_BV(LED_PIN);
    asm volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
}

void sendColor(uint8_t r, uint8_t g, uint8_t b) {
    for(uint8_t i = 8; i; i--) sendBit(g & 0x80), g <<= 1;
    for(uint8_t i = 8; i; i--) sendBit(r & 0x80), r <<= 1;
    for(uint8_t i = 8; i; i--) sendBit(b & 0x80), b <<= 1;
}

void updateCityLEDs(uint8_t cityIndex) {
    uint8_t level = cityInfectionLevels[cityIndex];
    uint8_t r = level > 0 ? 255 : 0;
    uint8_t g = 0;
    uint8_t b = 0;
    
    uint16_t startLED = cityIndex * LEDS_PER_CITY;
    uint16_t endLED = startLED + level;
    
    cli();  // Disable interrupts
    for (uint16_t i = startLED; i < startLED + LEDS_PER_CITY; i++) {
        sendColor(i < endLED ? r : 0, g, b);
    }
    sei();  // Re-enable interrupts
}