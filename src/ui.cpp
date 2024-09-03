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
#include <avr/io.h>
#include <avr/interrupt.h>

#define BUTTON_PORT PORTA
#define BUTTON_PIN  PINA
#define BUTTON_DDR  DDRA

volatile uint8_t buttonStates = 0;

void initializeButtons() {
    BUTTON_DDR &= ~(_BV(PA0) | _BV(PA1) | _BV(PA2) | _BV(PA3));  // Set as inputs
    BUTTON_PORT |= (_BV(PA0) | _BV(PA1) | _BV(PA2) | _BV(PA3));  // Enable pull-ups
    
    PCICR |= _BV(PCIE0);  // Enable PCINT for PORTA
    PCMSK0 |= (_BV(PCINT0) | _BV(PCINT1) | _BV(PCINT2) | _BV(PCINT3));  // Enable individual pin interrupts
    
    sei();  // Enable global interrupts
}  // Function initializes buttons with interrupt-based handling

ISR(PCINT0_vect) {
    static uint32_t lastInterruptTime = 0;
    uint32_t interruptTime = millis();
    if (interruptTime - lastInterruptTime > 50) {  // Simple debounce
        buttonStates = ~BUTTON_PIN & 0x0F;  // Read and invert button states
    }
    lastInterruptTime = interruptTime;
}  // Interrupt Service Routine for button presses

void handleButtonInputs() {
    if (buttonStates) {
        for (uint8_t i = 0; i < 4; i++) {
            if (buttonStates & (1 << i)) {
                performAction(i);
                buttonStates &= ~(1 << i);  // Clear the button state
            }
        }
    }
}  // Function handles button inputs based on interrupt-set flags

void performAction(uint8_t actionIndex) {
    static const ActionFunction actions[] = {
        movePlayer,
        treatDisease,
        buildResearchStation,
        shareKnowledge
    };
    actions[actionIndex]();
}  // Function performs the action corresponding to the button pressed

// LCD control functions using optimized TWI (I2C)
#define TWI_FREQ 400000L

void initializeTWI() {
    TWSR = 0;
    TWBR = ((F_CPU / TWI_FREQ) - 16) / 2;
    TWCR = _BV(TWEN);
}  // Function initializes TWI (I2C) for LCD communication

void twiStart() {
    TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
    while (!(TWCR & _BV(TWINT)));
}  // Function sends TWI start condition

void twiStop() {
    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);
}  // Function sends TWI stop condition

void twiWrite(uint8_t data) {
    TWDR = data;
    TWCR = _BV(TWINT) | _BV(TWEN);
    while (!(TWCR & _BV(TWINT)));
}  // Function writes a byte to TWI

void updateLCDDisplay() {
    // Implement LCD update logic using twiWrite() function
}  // Function updates the LCD display (to be implemented)