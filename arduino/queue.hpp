#pragma once
#include <stdint.h>
#include "avr.hpp"

template <typename T, uint16_t S>
class Queue
{
    T buffer[S];
    volatile uint16_t head = 0;
    volatile uint16_t tail = 0;

public:

    static constexpr uint16_t capacity() { return S; }
    uint16_t size() const { return (S + tail - head) % S; }
    bool isFull() { return size() == S; }
    bool isEmpty() { return size() == 0; }

    T pop()
    {
        uint16_t i = head;
        head = (head + 1) % S;
        return buffer[i];
    }

    T top()
    {
        return buffer[head];
    }

    void push(T obj)
    {
        uint16_t i = tail;
        tail = (tail + 1) % S;
        buffer[i] = obj;
    }

};
