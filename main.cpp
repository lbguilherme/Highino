#include <Serial>
#include <Time>

int main() {
    Serial<0> s(9600);
    while (true) {
        s << "Hello!" << endl;
        delay(1_s);
    }
}
