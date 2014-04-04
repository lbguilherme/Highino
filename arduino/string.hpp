#pragma once

template <unsigned Cap>
class String
{

    char buffer[Cap];
    uint16_t beg;
    uint16_t end;

public:

    String() : beg(0), end(0) {}

    String(const char* cstr) : beg(0), end(0)
    {
        while (char c = cstr[tail])
            buffer[tail++] = c;
    }

    constexpr uint16_t capacity() { return Cap; }
    uint16_t size() const { return end - beg; }

    char& operator[](uint16_t i) { return buffer[beg + i]; }
    char operator[](uint16_t i) const { return buffer[beg + i]; }



};

template <unsigned Cap>
class StringRef
{

    String<Cap>& str;
    uint16_t beg;
    uint16_t end;

public:



};
