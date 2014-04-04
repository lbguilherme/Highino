#pragma once
#include <stdint.h>
#include "board-generic.hpp"

enum PinMode { Input, Output, InputPullup };

template <unsigned P>
class Pin
{
    static_assert(detail::isValidDigitalPin(P), "Must use a valid digital pin.");

public:

    static constexpr uint8_t pin = P;

    Pin(PinMode mode=Output) { disablePwm(); setMode(mode);}

    void setMode(PinMode mode);
    PinMode mode() const
    {
        if (modeByte & bit)
            return isHigh() ? InputPullup : Input;
        return Output;
    }

    void high()          { outputByte |= bit; }
    void low()           { outputByte &= ~bit; }
    void set(bool value) { if (value) high(); else low(); }
    bool isHigh() const  { return modeByte & bit ? inputByte & bit : outputByte & bit; }
    bool isLow() const   { return !isHigh(); }
    bool get() const     { return isHigh(); }

    Pin<P>& operator=(bool value) { set(value); return *this; }
    bool operator*() { return get(); }

protected:

    void disablePwm() const {if (timer) detail::setupPwmTimer<timer, false>();}

    static constexpr uint8_t bit = detail::PinToBit[P];
    static constexpr uint8_t port = detail::PinToPort[P];
    static constexpr uint8_t timer = detail::PinToTimer[P];
    static constexpr volatile uint8_t& modeByte = *detail::PortToMode[port];
    static constexpr volatile uint8_t& inputByte = *detail::PortToInput[port];
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
template <unsigned i>
class a;
template <unsigned P>
class AnalogInputPin
{
    static_assert(detail::isValidAnalogInputPin(P), "Must use a valid analog input pin.");

public:

    static constexpr uint8_t pin = P;

    uint16_t get() const
    {
        if (channel <= 7)
            cbi(ADCSRB, MUX5);
        else
            sbi(ADCSRB, MUX5);

        ADMUX = (ref << 6) | (channel & 0x07);
        sbi(ADCSRA, ADEN);
        sbi(ADCSRA, ADSC);
        while (bit_is_set(ADCSRA, ADSC));
        uint8_t lo = ADCL;
        uint8_t hi = ADCH;
        return (hi << 8) | lo;
    }

    AnalogReference reference() { return ref; }
    void setReference(AnalogReference value) { ref = value; }

    uint16_t operator*() { return get(); }

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

    uint8_t get() const
    {
        if (&ocr8)
            return ocr8;
        else
            return ocr16;
    }

    AnalogOutputPin<P>& operator=(uint8_t value) { set(value); return *this; }
    uint8_t operator*() { return get(); }

    static constexpr uint8_t timer = detail::PinToTimer[P];
    static constexpr volatile uint8_t& ocr8 = *detail::TimerToOcr8[timer];
    static constexpr volatile uint16_t& ocr16 = *detail::TimerToOcr16[timer];

};
