#pragma once
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>

//static void cbi(volatile uint8_t& sfr, uint8_t bit) {sfr &= ~_BV(bit);}
static void sbi(volatile uint8_t& sfr, uint8_t bit) {sfr |= _BV(bit);}

static void enableInterruptions() {sei();}
//static void disableInterruptions() {cli();}

static void setupTimer0()
{
    // on the ATmega168, timer 0 is also used for fast hardware pwm
    #if defined(TCCR0A) && defined(WGM01)
        sbi(TCCR0A, WGM01);
        sbi(TCCR0A, WGM00);
    #endif

        // set timer 0 prescale factor to 64
    #if defined(__AVR_ATmega128__)
        // CPU specific: different values for the ATmega128
        sbi(TCCR0, CS02);
    #elif defined(TCCR0) && defined(CS01) && defined(CS00)
        // this combination is for the standard atmega8
        sbi(TCCR0, CS01);
        sbi(TCCR0, CS00);
    #elif defined(TCCR0B) && defined(CS01) && defined(CS00)
        // this combination is for the standard 168/328/1280/2560
        sbi(TCCR0B, CS01);
        sbi(TCCR0B, CS00);
    #elif defined(TCCR0A) && defined(CS01) && defined(CS00)
        // this combination is for the __AVR_ATmega645__ series
        sbi(TCCR0A, CS01);
        sbi(TCCR0A, CS00);
    #else
        #error Timer 0 prescale factor 64 not set correctly
    #endif

        // enable timer 0 overflow interrupt
    #if defined(TIMSK) && defined(TOIE0)
        sbi(TIMSK, TOIE0);
    #elif defined(TIMSK0) && defined(TOIE0)
        sbi(TIMSK0, TOIE0);
    #else
        #error	Timer 0 overflow interrupt not set correctly
    #endif
}
