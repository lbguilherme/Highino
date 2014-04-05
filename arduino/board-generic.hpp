#ifndef BOARD
#error This file is not meant to be compiled. Use a real board header
// This file is for highlighting and code completion only.
// Ignore any values and definitions present here.

#include "avr.hpp"
#include <avr/sfr_defs.h>
#include <avr/io.h>

static constexpr unsigned long CLOCK;

enum // Digital Pins
{
    // SPI
    SS,
    MOSI,
    MISO,
    SCLK,

    // I2C/TWI
    SDA,
    SCL,

    // Serial
    TX0,
    RX0,
    TX1,
    RX1,
    TX2,
    RX2,
    TX3,
    RX3,

    // Onboard LED
    LED_BUILTIN
};

enum // Analog Input Pins
{
    A0,
    A1, A2, A3, A4, A5, A6, A7, A8,
    A9, A10, A11, A12, A13, A14, A15
};

enum AnalogReference
{
    Default,
    External,
    Internal,
    Internal1V1,
    Internal2V56
};

namespace detail {

#define detail__serialChannelCount 999
#define detail__serialBufferOptimalSize 1024
constexpr unsigned serialChannelCount() { return 999; }
constexpr bool isValidDigitalPin(uint8_t) { return true; }
constexpr bool isValidAnalogInputPin(uint8_t) { return true; }
constexpr bool isValidAnalogOutputPin(uint8_t) { return true; }

static constexpr uint8_t PinToBit[] = {};
static constexpr uint8_t PinToPort[] = {};
static constexpr volatile uint8_t* PortToMode[] = {};
static constexpr volatile uint8_t* PortToInput[] = {};
static constexpr volatile uint8_t* PortToOutput[] = {};
static constexpr uint8_t PinToTimer[] = {};
static constexpr uint8_t PinToChannel[] = {};
static constexpr volatile uint16_t* TimerToOcr16[] = {};
static constexpr volatile uint8_t* TimerToOcr8[] = {};

static constexpr volatile uint8_t* serialObjects[][6] = {};
static constexpr uint8_t serialConstants[][6] = {};

static void init() {}

template <unsigned T, bool Enabled>
static void setupPwmTimer();
#endif
