#pragma once
#include "avr.hpp"

class Arduino
{
public:

    Arduino();

};

static Arduino arduino;

inline Arduino::Arduino()
{
    enableInterruptions();
    detail::init();
}
