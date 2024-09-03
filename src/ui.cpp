/******************************************************************************
 * Author: Benjamin Cance
 * Game: Arduino Pandemic for the Mega2560
 * Date: 3-Sept-2024
 * Version: 1.0
 * 
 * This file is part of the Arduino Pandemic project, a faithful 
 * implementation of the Pandemic board game for the Mega2560 platform.
 * 
 * Copyright (c) 2024 Benjamin Cance
 * 
 * MIT License
 *****************************************************************************/

#include "ui.h"
#include "player_actions.h"

#define TWI_FREQ 400000L

const uint8_t buttonPins[] = {28, 29, 30, 31};
uint8_t lastButtonStates[4] = {HIGH, HIGH, HIGH, HIGH};
uint32_t lastDebounceTimes[4] = {0};
const uint32_t debounceDelay = 50;

ISR(PCINT0_vect) {
    static uint32_t lastInterruptTime = 0;
    uint32_t interruptTime = millis();
    if (interruptTime - lastInterruptTime > 50) { 
        buttonStates = ~BUTTON_PIN & 0x0F;  
    }
    lastInterruptTime = interruptTime;
} // This ISR is used for button inputs on the PCINT0 register

void initializeButtons() {
    BUTTON_DDR &= ~(_BV(PA0) | _BV(PA1) | _BV(PA2) | _BV(PA3));  // Set as inputs
    BUTTON_PORT |= (_BV(PA0) | _BV(PA1) | _BV(PA2) | _BV(PA3));  // Enable pull-ups
    
    PCICR |= _BV(PCIE0);  // Enable PCINT for PORTA
    PCMSK0 |= (_BV(PCINT0) | _BV(PCINT1) | _BV(PCINT2) | _BV(PCINT3));  // Enable individual pin interrupts
    
    sei();  // Enable global interrupts
}

void handleButtonInputs() {
    if (buttonStates) {
        for (uint8_t i = 0; i < 4; i++) {
            if (buttonStates & (1 << i)) {
                performAction(i);
                buttonStates &= ~(1 << i);  
            }
        }
    }
} // Using interrupts lets us call this less frequently

void performAction(uint8_t actionIndex) {
    static const ActionFunction actions[] = {
        movePlayer,
        treatDisease,
        buildResearchStation,
        shareKnowledge
    };
    actions[actionIndex]();
}  // Function performs the action corresponding to the button pressed


/* We're going to use the TWI register to write to the LCDs via I2C */

void initializeTWI() {
    TWSR = 0;
    TWBR = ((F_CPU / TWI_FREQ) - 16) / 2;
    TWCR = _BV(TWEN);
}

void twiStart() {
    TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
    while (!(TWCR & _BV(TWINT)));
}

void twiStop() {
    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);
}

void twiWrite(uint8_t data) {
    TWDR = data;
    TWCR = _BV(TWINT) | _BV(TWEN);
    while (!(TWCR & _BV(TWINT)));
}