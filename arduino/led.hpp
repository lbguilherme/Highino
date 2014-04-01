#pragma once
#include "pin.hpp"

template <unsigned P>
class Led : protected Pin<P>
{
public:

    static constexpr uint8_t pin = P;

    void on()            {Pin<P>::high();}
    void off()           {Pin<P>::low();}
    void set(bool value) {Pin<P>::set(value);}
    bool isOn() const    {return Pin<P>::isHigh();}
    bool isOff() const   {return Pin<P>::isLow();}
    bool get() const     {return Pin<P>::get();}

    Led<P>& operator=(bool value) { set(value); return *this; }
    bool operator*() { return get(); }

};

template <unsigned P>
class AnalogLed : protected AnalogOutputPin<P>
{
public:

    static constexpr uint8_t pin = P;

    void on(uint8_t brightness)  {AnalogOutputPin<P>::set(brightness);}
    void off()                   {on(0);}
    void set(uint8_t brightness) {on(brightness);}
    bool isOn() const            {return get() > 0;}
    bool isOff() const           {!isOff();}
    uint8_t get() const          {return AnalogOutputPin<P>::get();}
    uint8_t brightness() const   {return get();}

    AnalogLed<P>& operator=(bool value) { set(value); return *this; }
    bool operator*() { return get(); }

};

using BuiltinLed = Led<LED_BUILTIN>;
using AnalogBuiltinLed = AnalogLed<LED_BUILTIN>;
