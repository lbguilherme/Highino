#pragma once
#include "pin.hpp"

template <unsigned P>
class Led : protected Pin<P>
{
public:

    Led() {Pin<P>::setMode(Output);}

    void on()          {Pin<P>::high();}
    void off()         {Pin<P>::low();}
    bool isOn() const  {return Pin<P>::isHigh();}
    bool isOff() const {return Pin<P>::isLow();}

};

using BuiltinLed = Led<LED_BUILTIN>;

