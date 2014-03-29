#pragma once

#include <avr/sfr_defs.h>
#include <avr/io.h>

static constexpr long CLOCK = 16000000L;

bool constexpr isValidDigitalPin(uint8_t pin) { return pin < 70; }
bool constexpr isValidAnalogPin(uint8_t pin) { return pin >= 54 && pin < 70; }

static constexpr uint8_t NUM_DIGITAL_PINS = 70;

static constexpr uint8_t SS   = 53;
static constexpr uint8_t MOSI = 51;
static constexpr uint8_t MISO = 50;
static constexpr uint8_t SCK  = 52;

static constexpr uint8_t SDA = 20;
static constexpr uint8_t SCL = 21;
static constexpr uint8_t LED_BUILTIN = 13;

enum
{
    A0 = 54,
    A1, A2, A3, A4, A5, A6, A7, A8,
    A9, A10, A11, A12, A13, A14, A15
};

static constexpr uint8_t _PinToBit[] = {
    _BV(0), _BV(1), _BV(4), _BV(5), _BV(5), _BV(3), _BV(3), _BV(4), _BV(5), _BV(6),
    _BV(4), _BV(5), _BV(6), _BV(7), _BV(1), _BV(0), _BV(1), _BV(0), _BV(3), _BV(2),
    _BV(1), _BV(0), _BV(0), _BV(1), _BV(2), _BV(3), _BV(4), _BV(5), _BV(6), _BV(7),
    _BV(7), _BV(6), _BV(5), _BV(4), _BV(3), _BV(2), _BV(1), _BV(0), _BV(7), _BV(2),
    _BV(1), _BV(0), _BV(7), _BV(6), _BV(5), _BV(4), _BV(3), _BV(2), _BV(1), _BV(0),
    _BV(3), _BV(2), _BV(1), _BV(0), _BV(0), _BV(1), _BV(2), _BV(3), _BV(4), _BV(5),
    _BV(6), _BV(7), _BV(0), _BV(1), _BV(2), _BV(3), _BV(4), _BV(5), _BV(6), _BV(7)
};

static constexpr uint8_t _PinToPort[] = {
    5, 5, 5, 5, 7, 5, 8, 8, 8, 8, 2, 2, 2, 2, 10, 10, 8, 8, 4, 4, 4, 4, 1, 1, 1, 1,
    1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 4, 7, 7, 7, 12, 12, 12, 12, 12, 12, 12, 12,
    2, 2, 2, 2, 6, 6, 6, 6, 6, 6, 6, 6, 11, 11, 11, 11, 11, 11, 11, 11
};

static constexpr volatile uint8_t* _PortToMode[] = {
    0, &DDRA, &DDRB, &DDRC, &DDRD, &DDRE, &DDRF,
    &DDRG, &DDRH, 0, &DDRJ, &DDRK, &DDRL
};

static constexpr volatile uint8_t* _PortToOutput[] = {
    0, &PORTA, &PORTB, &PORTC, &PORTD, &PORTE, &PORTF,
    &PORTG, &PORTH, 0, &PORTJ, &PORTK, &PORTL
};
