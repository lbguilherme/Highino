#include <arduino>

int main(void)
{

    BuiltinLed led;

    while (true) {
        led.on();
        delay(1000);
        led.off();
        delay(1000);
    }
}
