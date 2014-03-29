#pragma once

#include <stdint.h>

enum PinMode { Input, Output, InputPullup };

template <unsigned P>
class Pin
{
    static_assert(isValidDigitalPin(P), "Must use a valid digital pin.");

public:

    Pin() = default;
    Pin(PinMode mode) {setMode(mode);}

    void setMode(PinMode mode);

    void high()          {*_PortToOutput[port] |= bit;}
    void low()           {*_PortToOutput[port] &= ~bit;}
    void set(bool value) {if (value) high(); else low();}
    bool isHigh()        {return *_PortToOutput[port] & bit;}
    bool isLow()         {return !isHigh();}
    bool get()           {return isHigh();}

protected:

    static constexpr uint8_t bit = _PinToBit[P];
    static constexpr uint8_t port = _PinToPort[P];

};

template <unsigned P>
inline void Pin<P>::setMode(PinMode mode)
{
    switch (mode)
    {
    case Input:       *_PortToMode[port] &= ~bit; low();  break;
    case Output:      *_PortToMode[port] |=  bit;         break;
    case InputPullup: *_PortToMode[port] &= ~bit; high(); break;
    }
}
