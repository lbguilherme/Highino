#include <Serial>
#include <Time>
#include <Pin>

int main() {
    Serial<0> s(9600);
    AnalogInputPin<A0> pin;
    while (true) {
        s << *pin << endl;
        delay(1_ms);
    }
}
