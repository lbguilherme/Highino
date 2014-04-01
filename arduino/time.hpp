#pragma once
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

static volatile uint32_t overflowCount = 0;

// Timer0 ticks every 64 cycles
// Overflow happens every 256 ticks
ISR(TIMER0_OVF_vect)
{
    ++overflowCount;
}

class Time;
class Time
{
public:

    constexpr Time(uint32_t v) : value(v) {}
    uint32_t value;

    static Time now()
    {
        return overflowCount * 2 / (CLOCK / 8000000);
    }

};

static constexpr Time operator"" _ms(unsigned long long v)
{
    return v*1024/1000;
}

static constexpr Time operator"" _s(unsigned long long v)
{
    return v*1024;
}

static void delay(Time time)
{
    uint32_t end = Time::now().value + time.value;
    while (Time::now().value < end);
}
