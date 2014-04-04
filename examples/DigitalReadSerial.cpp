#include <Pin>
#include <Time>
#include <Serial>

int main()
{
    Pin<2> button(Input);
    Serial<0> s(9600);

    while(true)
    {
        s << *button << endl;
        delay(1_ms);
    }
}
