#pragma once
#include "pin.hpp"

// Software SPI
template<unsigned P_SS=SS, unsigned P_SCK=SCK, unsigned P_MOSI=MOSI, unsigned P_MISO=MISO>
class Spi
{
public:

    Spi() : ss(Output), sck(Output), mosi(Output), miso(Input)
    {
    }

    uint8_t transfer(uint8_t byte)
    {
        for (uint8_t bit = 0x80; bit; bit >>= 1) {
            ss.set(byte & bit);
            sck.high();
            sck.low();
        }
        return 0; // ?
    }

private:

    Pin<P_SS> ss;
    Pin<P_SCK> sck;
    Pin<P_MOSI> mosi;
    Pin<P_MISO> miso;

};

// Hardware SPI
template <>
class Spi<SS, SCK, MOSI, MISO>
{
public:

    Spi() : ss(Output), sck(Output), mosi(Output), miso(Input)
    {
        ss.high();
        SPCR |= _BV(MSTR);
        SPCR |= _BV(SPE);
    }

    ~Spi()
    {
        SPCR &= ~_BV(SPE);
    }

    uint8_t transfer(uint8_t byte)
    {
        SPDR = byte;
        while (!(SPSR & (1<<SPIF)));
        return SPDR;
    }

private:

    Pin<SS> ss;
    Pin<SCK> sck;
    Pin<MOSI> mosi;
    Pin<MISO> miso;

};

