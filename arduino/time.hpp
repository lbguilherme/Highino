#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>

static volatile uint32_t overflowCount = 0;

// Timer0 ticks every 64 cycles
// Overflow happens every 256 ticks
ISR(TIMER0_OVF_vect)
{
    ++overflowCount;
}

static uint32_t now_nonstandard()
{
    return overflowCount * 2 / (CLOCK / 8000000);
}

static void delay_nonstandard(unsigned time)
{
    uint32_t end = now_nonstandard() + time;
    while (now_nonstandard() < end);
}

#define delay(ms) delay_nonstandard(ms*1024ULL/1000);
