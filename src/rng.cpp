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

#include "random_generator.h"
#include "city_map.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint32_t entropy = 0;
volatile uint8_t entropyReady = 0;

void initializeRandomGenerator() {
    // Set up ADC
    ADCSRA = _BV(ADEN) | _BV(ADATE) | _BV(ADIE) | 0x07;  // Enable ADC, auto-trigger, interrupt, and set prescaler to 128
    ADCSRB = 0x00;  // Free running mode
    ADMUX = 0x40;   // Use AVCC as reference and select ADC0
    
    // Set up Timer1 for periodic ADC triggering
    TCCR1A = 0;
    TCCR1B = _BV(WGM12) | _BV(CS10);  // CTC mode, no prescaling
    OCR1A = 1000;  // Set for approximately 16kHz interrupt rate
    TIMSK1 = _BV(OCIE1A);  // Enable compare match interrupt
    
    sei();  // Enable global interrupts
}

ISR(TIMER1_COMPA_vect) {
    ADCSRA |= _BV(ADSC);  // Start ADC conversion
}

ISR(ADC_vect) {
    static uint8_t count = 0;
    entropy = (entropy << 1) | (ADC & 1);
    if (++count == 32) {
        entropyReady = 1;
        count = 0;
    }
}

uint32_t getRandomNumber() {
    while (!entropyReady);
    entropyReady = 0;
    return entropy;
}

uint8_t getRandomCity() {
    return getRandomNumber() % CITY_COUNT;
}  // Function returns a random city index