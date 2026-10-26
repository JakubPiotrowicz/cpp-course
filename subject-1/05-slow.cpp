#include <string>
#include <iostream>

int main() {
    std::string s;
    for (int i = 0; i < 10000; ++i) {
        s += "abc"; // Reallocations
    }

    std::cout << s << std::endl;
    return 0;
}
