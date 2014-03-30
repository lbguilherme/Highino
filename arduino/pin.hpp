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
    PinMode mode() const
    {
        if (modeByte & bit)
            return isHigh() ? InputPullup : Input;
        return Output;
    }

    void high()          {*detail::PortToOutput[port] |= bit;}
    void low()           {*detail::PortToOutput[port] &= ~bit;}
    void set(bool value) {if (value) high(); else low();}
    bool isHigh() const  {return *detail::PortToOutput[port] & bit;}
    bool isLow() const   {return !isHigh();}
    bool get() const     {return isHigh();}

protected:

    static constexpr uint8_t bit = detail::PinToBit[P];
    static constexpr uint8_t port = detail::PinToPort[P];
    static constexpr volatile uint8_t& modeByte = *detail::PortToMode[port];

};

template <unsigned P>
inline void Pin<P>::setMode(PinMode mode)
{
    switch (mode)
    {
    case Input:       modeByte &= ~bit; low();  break;
    case Output:      modeByte |=  bit;         break;
    case InputPullup: modeByte &= ~bit; high(); break;
    }
}
