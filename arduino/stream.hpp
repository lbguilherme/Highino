#pragma once
#include "math.hpp"

static char endl() { return '\n'; }

template <typename Derived>
class OutStream
{
private:

    void putc(char c) { ((Derived*)this)->putc(c); }

public:

    OutStream& operator<<(char c)
    {
        putc(c);
        return *this;

    }
    template <typename F>
    OutStream& operator<<(const F& f)
    {
        return *this << f();
    }

    OutStream& operator<<(const char* s)
    {
        while (char c = *(s++))
            *this << c;
        return *this;
    }

    OutStream& operator<<(bool b)
    {
        return b ? *this << "true" : *this << "false";
    }

    OutStream& operator<<(uint8_t n)
    {
        while (n) { *this << '0' + n % 10; n /= 10; }
        return *this;
    }

    OutStream& operator<<(uint16_t n)
    {
        while (n) { *this << '0' + n % 10; n /= 10; }
        return *this;
    }

    OutStream& operator<<(uint32_t n)
    {
        while (n) { *this << '0' + n % 10; n /= 10; }
        return *this;
    }

    OutStream& operator<<(uint64_t n)
    {
        while (n) { *this << '0' + n % 10; n /= 10; }
        return *this;
    }

    OutStream& operator<<(int8_t n)
    {
        if (n < 0) *this << '-';
        while (n) { *this << '0' + abs(n % 10); n /= 10; }
        return *this;
    }

    OutStream& operator<<(int16_t n)
    {
        if (n < 0) *this << '-';
        while (n) { *this << '0' + abs(n % 10); n /= 10; }
        return *this;
    }

    OutStream& operator<<(int32_t n)
    {
        if (n < 0) *this << '-';
        while (n) { *this << '0' + abs(n % 10); n /= 10; }
        return *this;
    }

    OutStream& operator<<(int64_t n)
    {
        if (n < 0) *this << '-';
        while (n) { *this << '0' + abs(n % 10); n /= 10; }
        return *this;
    }

};

template <typename Derived>
class InStream
{
private:

    char getc() { return ((Derived*)this)->getc(); }
    char peek() { return ((Derived*)this)->peek(); }

public:

    InStream& operator>>(char& c)
    {
        c = getc();
        return *this;
    }

    InStream& operator>>(uint8_t& n)
    {
        char c;
        n = 0;
        while (isnum(c=peek()))
        {
            n *= 10;
            n += getc() - '0';
        }
        return n;
    }

};

template <typename Derived>
class Stream : public OutStream<Derived>, public InStream<Derived> {};
