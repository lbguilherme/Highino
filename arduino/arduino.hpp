#pragma once
#include "board-generic.hpp"
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
