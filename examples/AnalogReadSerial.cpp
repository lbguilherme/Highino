#include <Pin>
#include <Time>
#include <Serial>

int main()
{
    AnalogInputPin<A0> pin;
    Serial<0> s(9600);

    while(true)
    {
        s << *pin << endl;
        delay(1_ms);
    }
}
