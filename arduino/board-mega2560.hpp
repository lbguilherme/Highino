#pragma once
#include "avr.hpp"
#include <avr/sfr_defs.h>
#include <avr/io.h>

static constexpr unsigned long CLOCK = 16000000;

enum // Digital Pins
{
    // SPI
    SS   = 53,
    MOSI = 51,
    MISO = 50,
    SCK  = 52,

    // I2C/TWI
    SDA = 20,
    SCL = 21,

    // Serial
    TX0 = 0,
    RX0 = 1,
    TX1 = 18,
    RX1 = 19,
    TX2 = 16,
    RX2 = 17,
    TX3 = 14,
    RX3 = 15,

    // Onboard LED
    LED_BUILTIN = 13
};

enum // Analog Input Pins
{
    A0 = 54,
    A1, A2, A3, A4, A5, A6, A7, A8,
    A9, A10, A11, A12, A13, A14, A15
};

enum // Analog Output Pins
{
    PWM2 = 2,
    PWM3, PWM4, PWM5, PWM6, PWM7, PWM8,
    PWM9, PWM10, PWM11, PWM12, PWM13,
    PWM44 = 44, PWM45, PWM46
};

enum AnalogReference
{
    External = 0,
    Default = 1,
    Internal1V1 = 2,
    Internal2V56 = 3
};

namespace detail {

constexpr bool isValidDigitalPin(uint8_t pin) { return pin < 70; }
constexpr bool isValidAnalogInputPin(uint8_t pin) { return pin >= 54 && pin < 70; }
constexpr bool isValidAnalogOutputPin(uint8_t pin) { return (pin >= 2 && pin <= 13) || (pin >= 44 && pin <= 46); }

static constexpr uint8_t PinToBit[] = {
    1<<0, 1<<1, 1<<4, 1<<5, 1<<5, 1<<3, 1<<3, 1<<4, 1<<5, 1<<6,
    1<<4, 1<<5, 1<<6, 1<<7, 1<<1, 1<<0, 1<<1, 1<<0, 1<<3, 1<<2,
    1<<1, 1<<0, 1<<0, 1<<1, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6, 1<<7,
    1<<7, 1<<6, 1<<5, 1<<4, 1<<3, 1<<2, 1<<1, 1<<0, 1<<7, 1<<2,
    1<<1, 1<<0, 1<<7, 1<<6, 1<<5, 1<<4, 1<<3, 1<<2, 1<<1, 1<<0,
    1<<3, 1<<2, 1<<1, 1<<0, 1<<0, 1<<1, 1<<2, 1<<3, 1<<4, 1<<5,
    1<<6, 1<<7, 1<<0, 1<<1, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6, 1<<7
};

static constexpr uint8_t PinToPort[] = {
    5, 5, 5, 5, 7, 5, 8, 8, 8, 8, 2, 2, 2, 2, 10, 10, 8, 8, 4, 4, 4, 4, 1, 1, 1, 1,
    1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 4, 7, 7, 7, 12, 12, 12, 12, 12, 12, 12, 12,
    2, 2, 2, 2, 6, 6, 6, 6, 6, 6, 6, 6, 11, 11, 11, 11, 11, 11, 11, 11
};

static constexpr volatile uint8_t* PortToMode[] = {
    0, &DDRA, &DDRB, &DDRC, &DDRD, &DDRE, &DDRF,
    &DDRG, &DDRH, 0, &DDRJ, &DDRK, &DDRL
};

static constexpr volatile uint8_t* PortToOutput[] = {
    0, &PORTA, &PORTB, &PORTC, &PORTD, &PORTE, &PORTF,
    &PORTG, &PORTH, 0, &PORTJ, &PORTK, &PORTL
};

static constexpr uint8_t PinToTimer[] = {
    0, 0, 9, 10, 2, 8, 11, 12, 13, 7, 6, 3, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17, 16, 15,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static constexpr uint8_t PinToChannel[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
};

static constexpr volatile uint16_t* TimerToOcr16[] = {
    0, 0, 0, &OCR1A, &OCR1B, 0, 0, 0, &OCR3A, &OCR3B, &OCR3C,
    &OCR4A, &OCR4B, &OCR4C, 0, &OCR5A, &OCR5B, &OCR5C
};

static constexpr volatile uint8_t* TimerToOcr8[] = {
    0, &OCR0A, &OCR0B, 0, 0, 0, &OCR2A, &OCR2B, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static void enableTimerInterruption() {
    sbi(TCCR0A, WGM01);
    sbi(TCCR0A, WGM00);
    sbi(TCCR0B, CS01);
    sbi(TCCR0B, CS00);
    sbi(TIMSK0, TOIE0);
}

template <unsigned T, bool Enabled>
static void setupPwmTimer();// {}

template <> void setupPwmTimer<1,  true>()  { sbi(TCCR0A, COM0A1); }
template <> void setupPwmTimer<1,  false>() { cbi(TCCR0A, COM0A1); }
template <> void setupPwmTimer<2,  true>()  { sbi(TCCR0A, COM0B1); }
template <> void setupPwmTimer<2,  false>() { cbi(TCCR0A, COM0B1); }
template <> void setupPwmTimer<3,  true>()  { sbi(TCCR1A, COM1A1); }
template <> void setupPwmTimer<3,  false>() { cbi(TCCR1A, COM1A1); }
template <> void setupPwmTimer<4,  true>()  { sbi(TCCR1A, COM1B1); }
template <> void setupPwmTimer<4,  false>() { cbi(TCCR1A, COM1B1); }
//template <> void setupPwmTimer<5,  true>()  { sbi(TCCR2,  COM21);  }
//template <> void setupPwmTimer<5,  false>() { cbi(TCCR2,  COM21);  }
template <> void setupPwmTimer<6,  true>()  { sbi(TCCR2A, COM2A1); }
template <> void setupPwmTimer<6,  false>() { cbi(TCCR2A, COM2A1); }
template <> void setupPwmTimer<7,  true>()  { sbi(TCCR2A, COM2B1); }
template <> void setupPwmTimer<7,  false>() { cbi(TCCR2A, COM2B1); }
template <> void setupPwmTimer<8,  true>()  { sbi(TCCR3A, COM3A1); }
template <> void setupPwmTimer<8,  false>() { cbi(TCCR3A, COM3A1); }
template <> void setupPwmTimer<9,  true>()  { sbi(TCCR3A, COM3B1); }
template <> void setupPwmTimer<9,  false>() { cbi(TCCR3A, COM3B1); }
template <> void setupPwmTimer<10, true>()  { sbi(TCCR3A, COM3C1); }
template <> void setupPwmTimer<10, false>() { cbi(TCCR3A, COM3C1); }
//template <> void setupPwmTimer<11, true>()  { sbi(TCCR4A, COM4A1); }
//template <> void setupPwmTimer<11, false>() { cbi(TCCR4A, COM4A1); }
template <> void setupPwmTimer<12, true>()  { sbi(TCCR4A, COM4B1); }
template <> void setupPwmTimer<12, false>() { cbi(TCCR4A, COM4B1); }
template <> void setupPwmTimer<13, true>()  { sbi(TCCR4A, COM4C1); }
template <> void setupPwmTimer<13, false>() { cbi(TCCR4A, COM4C1); }
//template <> void setupPwmTimer<14, true>()  { sbi(TCCR4A, COM4D1); }
//template <> void setupPwmTimer<14, false>() { cbi(TCCR4A, COM4D1); }
template <> void setupPwmTimer<15, true>()  { sbi(TCCR5A, COM5A1); }
template <> void setupPwmTimer<15, false>() { cbi(TCCR5A, COM5A1); }
template <> void setupPwmTimer<16, true>()  { sbi(TCCR5A, COM5B1); }
template <> void setupPwmTimer<16, false>() { cbi(TCCR5A, COM5B1); }
template <> void setupPwmTimer<17, true>()  { sbi(TCCR5A, COM5C1); }
template <> void setupPwmTimer<17, false>() { cbi(TCCR5A, COM5C1); }

}
