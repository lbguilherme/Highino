#include <arduino>

void sleep()
{
    volatile int i = 1;
    while (i) ++i;
}

int main(void)
{
    BuiltinLed led;
    led.on();

    while (true) {
        led.off();
        sleep();
        led.on();
        sleep();
    }
}
