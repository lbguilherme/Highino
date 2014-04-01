#include <arduino>

int main(void)
{
    AnalogOutputPin<BuiltinLed::pin> led;

    while (true)
    {
        for(int fadeValue = 0 ; fadeValue <= 255; fadeValue += 1) {
            led.set(fadeValue);
            delay(1);
        }

        for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 1) {
            led.set(fadeValue);
            delay(1);
        }
    }
}
