#pragma once
#include "pin.hpp"

template <unsigned P>
class Led : protected Pin<P>
{
public:

    static constexpr uint8_t pin = P;

    Led() {Pin<P>::setMode(Output);}

    void on()            {Pin<P>::high();}
    void off()           {Pin<P>::low();}
    void set(bool value) {Pin<P>::set(value);}
    bool isOn() const    {return Pin<P>::isHigh();}
    bool isOff() const   {return Pin<P>::isLow();}
    bool get() const     {return Pin<P>::get();}

    Led<P>& operator=(bool value) { set(value); return *this; }
    bool operator*() { return get(); }

};

using BuiltinLed = Led<LED_BUILTIN>;

