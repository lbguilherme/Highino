#include <Led>
#include <Time>

int main() {
    AnalogLed<13> led; // You could use 'BuiltinAnalogLed' instead of 'AnalogLed<13>' as well

    int fadeAmount = 5;
    while (true) {
        // Just change it! You could also use led.set(led.get()+value) or led.on(led.brightness()+value)
        led += fadeAmount;

        // We can read the brightness directly from the LED
        if (led.brightness() == 0 || led.brightness() == 255) {
          fadeAmount = -fadeAmount;
        }

        delay(30_ms); // 30ms delay
    }
}
