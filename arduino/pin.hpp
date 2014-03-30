#pragma once
#include <stdint.h>

enum PinMode { Input, Output, InputPullup };

template <unsigned P>
class Pin
{
    static_assert(detail::isValidDigitalPin(P), "Must use a valid digital pin.");

public:

    Pin() = default;
    Pin(PinMode mode) {setMode(mode);}

    void setMode(PinMode mode);

    void high()          {*detail::PortToOutput[port] |= bit;}
    void low()           {*detail::PortToOutput[port] &= ~bit;}
    void set(bool value) {if (value) high(); else low();}
    bool isHigh()        {return *detail::PortToOutput[port] & bit;}
    bool isLow()         {return !isHigh();}
    bool get()           {return isHigh();}

protected:

    static constexpr uint8_t bit = detail::PinToBit[P];
    static constexpr uint8_t port = detail::PinToPort[P];

};

template <unsigned P>
inline void Pin<P>::setMode(PinMode mode)
{
    switch (mode)
    {
    case Input:       *detail::PortToMode[port] &= ~bit; low();  break;
    case Output:      *detail::PortToMode[port] |=  bit;         break;
    case InputPullup: *detail::PortToMode[port] &= ~bit; high(); break;
    }
}
