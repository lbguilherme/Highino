#pragma once

#include <stdint.h>
#include <avr/sfr_defs.h>

class Arduino
{
public:

    Arduino();

    void set(unsigned sfr, uint8_t bit, bool value) {
        if (value) _SFR_BYTE(sfr) &= ~_BV(bit); else _SFR_BYTE(sfr) |= _BV(bit);
    }
};

static Arduino arduino;

inline Arduino::Arduino()
{

}
