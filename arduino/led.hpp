#pragma once
#include "pin.hpp"

// Ensure all timers will be initialized on the board
namespace detail {
static void initTimers() __attribute__((constructor, used));
}

template <unsigned P>
class Led : protected Pin<P>
{
public:

    static constexpr uint8_t pin = P;

    Led() {off();}

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

    AnalogLed() {off();}

    void on(uint8_t brightness)  {AnalogOutputPin<P>::set(brightness);}
    void off()                   {on(0);}
    void set(uint8_t brightness) {on(brightness);}
    bool isOn() const            {return get() > 0;}
    bool isOff() const           {return !isOn();}
    uint8_t get() const          {return AnalogOutputPin<P>::get();}
    uint8_t brightness() const   {return get();}

    AnalogLed<P>& operator=(uint8_t brightness) { set(brightness); return *this; }
    bool operator*() { return get(); }

    AnalogLed<P>& operator+=(int delta) { set(get()+delta); return *this; }
    AnalogLed<P>& operator-=(int delta) { set(get()-delta); return *this; }

};

using BuiltinLed = Led<LED_BUILTIN>;
using BuiltinAnalogLed = AnalogLed<LED_BUILTIN>;
