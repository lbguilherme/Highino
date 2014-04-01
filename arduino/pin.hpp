#pragma once
#include <stdint.h>

enum PinMode { Input, Output, InputPullup };

template <unsigned P>
class Pin
{
    static_assert(detail::isValidDigitalPin(P), "Must use a valid digital pin.");

public:

    static constexpr uint8_t pin = P;

    Pin(PinMode mode=Output) {setMode(mode);}

    void setMode(PinMode mode);
    PinMode mode() const
    {
        if (modeByte & bit)
            return isHigh() ? InputPullup : Input;
        return Output;
    }

    void high()          {disablePwm(); outputByte |= bit;}
    void low()           {disablePwm(); outputByte &= ~bit;}
    void set(bool value) {if (value) high(); else low();}
    bool isHigh() const  {return outputByte & bit;}
    bool isLow() const   {return !isHigh();}
    bool get() const     {return isHigh();}

protected:

    void disablePwm() const {if (timer) detail::setupPwmTimer<timer, false>();}

    static constexpr uint8_t bit = detail::PinToBit[P];
    static constexpr uint8_t port = detail::PinToPort[P];
    static constexpr uint8_t timer = detail::PinToTimer[P];
    static constexpr volatile uint8_t& modeByte = *detail::PortToMode[port];
    static constexpr volatile uint8_t& outputByte = *detail::PortToOutput[port];

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

template <unsigned P>
class AnalogInputPin
{
    static_assert(detail::isValidAnalogInputPin(P), "Must use a valid analog input pin.");

public:

    static constexpr uint8_t pin = P;

    uint16_t get()
    {
        ADMUX = (ref << 6) | (channel & 0x07);
        sbi(ADCSRA, ADSC);
        while (bit_is_set(ADCSRA, ADSC));
        uint8_t lo = ADCL;
        uint8_t hi = ADCH;
        return (hi << 8) | lo;
    }

    AnalogReference reference() { return ref; }
    void setReference(AnalogReference value) { ref = value; }

protected:

    AnalogReference ref = Default;

    static constexpr uint8_t channel = detail::PinToChannel[P];

};

template <unsigned P>
class AnalogOutputPin : protected Pin<P>
{
    static_assert(detail::isValidAnalogOutputPin(P), "Must use a valid analog output pin.");

public:

    static constexpr uint8_t pin = P;

    AnalogOutputPin() { detail::setupPwmTimer<timer, true>();}

    void set(uint8_t value)
    {
        if (&ocr8)
            ocr8 = value;
        else
            ocr16 = value;
    }

    static constexpr uint8_t timer = detail::PinToTimer[P];
    static constexpr volatile uint8_t& ocr8 = *detail::TimerToOcr8[timer];
    static constexpr volatile uint16_t& ocr16 = *detail::TimerToOcr16[timer];

};
