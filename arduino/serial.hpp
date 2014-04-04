#pragma once
#include "board-generic.hpp"
#include "queue.hpp"
#include "stream.hpp"

#ifndef SERIAL_BUFFER
#define SERIAL_BUFFER detail__serialBufferOptimalSize
#endif

enum SerialConfig
{
    Serial5N1 = 0x00,
    Serial6N1 = 0x02,
    Serial7N1 = 0x04,
    Serial8N1 = 0x06,
    Serial5N2 = 0x08,
    Serial6N2 = 0x0A,
    Serial7N2 = 0x0C,
    Serial8N2 = 0x0E,
    Serial5E1 = 0x20,
    Serial6E1 = 0x22,
    Serial7E1 = 0x24,
    Serial8E1 = 0x26,
    Serial5E2 = 0x28,
    Serial6E2 = 0x2A,
    Serial7E2 = 0x2C,
    Serial8E2 = 0x2E,
    Serial5O1 = 0x30,
    Serial6O1 = 0x32,
    Serial7O1 = 0x34,
    Serial8O1 = 0x36,
    Serial5O2 = 0x38,
    Serial6O2 = 0x3A,
    Serial7O2 = 0x3C,
    Serial8O2 = 0x3E
};

template <unsigned Channel>
class Serial : public Stream<Serial<Channel>>
{
    static_assert(Channel < detail::serialChannelCount(), "Must use a valid serial channel.");

public:

    Serial(unsigned long baud, SerialConfig config = Serial8N1)
    {
        uint16_t ubrr = (CLOCK / 4 / baud - 1) / 2;
        if (ubrr > 4095)
        {
            ubrr = (CLOCK / 8 / baud - 1) / 2;
            UCSRA = 0;
        }
        else
        {
            UCSRA = 1 << U2X;
        }

        UBRRH = ubrr >> 9;
        UBRRL = ubrr;
        UCSRC = (uint8_t)config;

        sbi(UCSRB, RXEN);
        sbi(UCSRB, TXEN);
        sbi(UCSRB, RXCIE);
        cbi(UCSRB, UDRIE);
    }

    void putc(char c)
    {
        while (queueOut.isFull());
        disableInterruptions();
        queueOut.push(c);
        enableInterruptions();
        sbi(UCSRB, UDRIE);
        sbi(UCSRA, TXC0);
    }

    char getc()
    {
        while (queueIn.isFull());
        disableInterruptions();
        char c = queueIn.pop();
        enableInterruptions();
        return c;
    }

    char peek()
    {
        while (queueIn.isFull());
        disableInterruptions();
        char c = queueIn.top();
        enableInterruptions();
        return c;
    }

    static Queue<char, SERIAL_BUFFER> queueOut;
    static Queue<char, SERIAL_BUFFER> queueIn;

    static constexpr volatile uint8_t& UBRRH = *detail::serialObjects[Channel][0];
    static constexpr volatile uint8_t& UBRRL = *detail::serialObjects[Channel][1];
    static constexpr volatile uint8_t& UCSRA = *detail::serialObjects[Channel][2];
    static constexpr volatile uint8_t& UCSRB = *detail::serialObjects[Channel][3];
    static constexpr volatile uint8_t& UCSRC = *detail::serialObjects[Channel][4];
    static constexpr volatile uint8_t& UDR = *detail::serialObjects[Channel][5];
    static constexpr uint8_t RXEN = detail::serialConstants[Channel][0];
    static constexpr uint8_t TXEN = detail::serialConstants[Channel][1];
    static constexpr uint8_t RXCIE = detail::serialConstants[Channel][2];
    static constexpr uint8_t UDRIE = detail::serialConstants[Channel][3];
    static constexpr uint8_t U2X = detail::serialConstants[Channel][4];
    static constexpr uint8_t UPE = detail::serialConstants[Channel][5];

};

template <unsigned Channel>
Queue<char, SERIAL_BUFFER> Serial<Channel>::queueOut;

template <unsigned Channel>
Queue<char, SERIAL_BUFFER> Serial<Channel>::queueIn;

#define CREATE_SERIAL_INTR(Channel) \
    ISR(detail_serial_UDRE_intr##Channel) \
    { \
        if (!Serial<Channel>::queueOut.isEmpty()) \
            Serial<Channel>::UDR = Serial<Channel>::queueOut.pop(); \
        else \
            cbi(Serial<Channel>::UCSRB, Serial<Channel>::UDRIE); \
    } \
    ISR(detail_serial_USART_intr##Channel) \
    { \
        unsigned char c = Serial<Channel>::UDR; \
        if (Serial<Channel>::UCSRA & Serial<Channel>::UPE) \
            Serial<Channel>::queueIn.push(c); \
    }

#if detail__serialChannelCount >= 1
CREATE_SERIAL_INTR(0)
#endif

#if detail__serialChannelCount >= 2
CREATE_SERIAL_INTR(1)
#endif

#if detail__serialChannelCount >= 3
CREATE_SERIAL_INTR(2)
#endif

#if detail__serialChannelCount >= 4
CREATE_SERIAL_INTR(3)
#endif

#undef CREATE_SERIAL_INTR
