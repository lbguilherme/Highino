#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>

static volatile unsigned overflowCount = 0;

// Timer0 ticks every 64 cycles
// Overflow happens every 256 ticks
ISR(TIMER0_OVF_vect)
{
    ++overflowCount;
}

// returns milliseconds
static unsigned long now()
{
    return overflowCount * (unsigned long)(64LL * 256 * 1000 / CLOCK);
}

static void delay(unsigned ms)
{
    unsigned long end = now()+ms;
    while (now() < end);
}
