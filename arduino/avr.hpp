#pragma once
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>

static void cbi(volatile uint8_t& sfr, uint8_t bit) {sfr &= ~_BV(bit);}
static void sbi(volatile uint8_t& sfr, uint8_t bit) {sfr |= _BV(bit);}

static void enableInterruptions() {sei();}
//static void disableInterruptions() {cli();}
