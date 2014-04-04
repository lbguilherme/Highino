#pragma once
#include "pin.hpp"

enum SpiMode
{
    SpiMode0 = 0x00,
    SpiMode1 = 0x04,
    SpiMode2 = 0x08,
    SpiMode3 = 0x0C
};

enum SpiBitOrder
{
    SpiLsbFirst,
    SpiMsbFirst
};

template <unsigned P_SS>
class Spi
{
public:

    Spi() : ss(Output), sclk(Output), mosi(Output), miso(Input)
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
        ss.low();
        SPDR = byte;
        while (!(SPSR & (1<<SPIF)));
        uint8_t r = SPDR;
        ss.high();
        return r;
    }

    void setMode(SpiMode m) { SPCR = (SPCR & ~0x0C) | m; }
    SpiMode mode() { return SpiMode(SPCR & 0x0C); }
    void setBitOrder(SpiBitOrder b) { if (b == SpiLsbFirst) SPCR |= (1<<DORD); else SPCR &= ~(1<<DORD); }
    SpiBitOrder bitOrder() { return SPCR & (1<<DORD) ? SpiLsbFirst : SpiMsbFirst; }

private:

    Pin<P_SS> ss;
    Pin<SCLK> sclk;
    Pin<MOSI> mosi;
    Pin<MISO> miso;

};
