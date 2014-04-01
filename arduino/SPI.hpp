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

// Software SPI
template<unsigned P_SS=SS, unsigned P_SCLK=SCLK, unsigned P_MOSI=MOSI, unsigned P_MISO=MISO>
class Spi
{
public:

    Spi() :
        ss(Output), sclk(Output), mosi(Output), miso(Input),
        spiMode(SpiMode0), spiBitOrder(SpiMsbFirst)
    {
        // Falling edge to select device
        ss.high();
        ss.low();
    }

    uint8_t transfer(uint8_t byte)
    {
        // TODO: handle mode
        if (spiBitOrder == SpiMsbFirst)
        {
            for (uint8_t mask = 0x80; mask; mask >>= 1)
            {
                mosi.set(byte & mask);
                sclk.high();
                byte = (byte & ~mask) | (miso.get() ? mask : 0);
                sclk.low();
            }
        }
        else
        {
            for (uint8_t mask = 0x01; mask; mask <<= 1)
            {
                mosi.set(byte & mask);
                sclk.high();
                byte = (byte & ~mask) | (miso.get() ? mask : 0);
                sclk.low();
            }
        }
        return byte;
    }

    void setMode(SpiMode mode) { spiMode = mode; }
    SpiMode mode() { return spiMode; }
    void setBitOrder(SpiBitOrder bitOrder) { spiBitOrder = bitOrder; }
    SpiBitOrder bitOrder() { return spiBitOrder; }

private:

    Pin<P_SS> ss;
    Pin<P_SCLK> sclk;
    Pin<P_MOSI> mosi;
    Pin<P_MISO> miso;
    SpiMode spiMode;
    SpiBitOrder spiBitOrder;

};

// Hardware SPI
template <>
class Spi<SS, SCLK, MOSI, MISO>
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
        SPDR = byte;
        while (!(SPSR & (1<<SPIF)));
        return SPDR;
    }

    void setMode(SpiMode m) { SPCR = (SPCR & ~0x0C) | m; }
    SpiMode mode() { return SpiMode(SPCR & 0x0C); }
    void setBitOrder(SpiBitOrder b) { if (b == SpiLsbFirst) SPCR |= (1<<DORD); else SPCR &= ~(1<<DORD); }
    SpiBitOrder bitOrder() { return SPCR & (1<<DORD) ? SpiLsbFirst : SpiMsbFirst; }

private:

    Pin<SS> ss;
    Pin<SCLK> sclk;
    Pin<MOSI> mosi;
    Pin<MISO> miso;

};

