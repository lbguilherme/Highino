#pragma once
#include "pin.hpp"

template <unsigned P>
class Led : protected Pin<P>
{
public:

    Led() {Pin<P>::setMode(Output);}

    void on() {Pin<P>::high();}
    void off() {Pin<P>::low();}

};

using BuiltinLed = Led<LED_BUILTIN>;

