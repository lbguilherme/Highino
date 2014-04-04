#include <Led>
#include <Time>

int main() {
    Led<13> led; // You could use 'BuiltinLed' instead of 'Led<13>' as well
    // The pin is already set as Output (it is a LED!)

    while (true) {
        led.on();    // Simple on/off functions. You don't have to expose what HIGH/LOW means to a LED
        delay(1000_ms); // This is unchanged.
        led.off();
        delay(1000_ms);
    }
}
