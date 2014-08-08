#pragma once
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// Ensure all timers will be initialized on the board
namespace detail {
static void initTimers() __attribute__((constructor, used));
}

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

    explicit constexpr Time(uint32_t v=0) : value(v) {}

    uint32_t value;

    static Time now()
    {
        return Time(overflowCount);
    }

};

static constexpr Time operator"" _ms(unsigned long long v)
{
    return Time(v*1024/1000 * 2 / (CLOCK / 8000000));
}

static constexpr Time operator"" _s(unsigned long long v)
{
    return Time(v*1024 * 2 / (CLOCK / 8000000));
}

static constexpr Time operator"" _m(unsigned long long v)
{
    return Time(v*1024*60 * 2 / (CLOCK / 8000000));
}

static constexpr Time operator"" _h(unsigned long long v)
{
    return Time(v*1024*3600 * 2 / (CLOCK / 8000000));
}

static void delay(Time time)
{
    uint32_t end = overflowCount + time.value;
    while (overflowCount < end);
}
