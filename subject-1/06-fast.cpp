#include <iostream>
#include <string>
// #include <sstream>

int main() {
    std::string s;
    s.reserve(30000); // we reserve enough space to avoid multiple reallocations
    for (int i = 0; i < 10000; ++i) {
        s += "abc";
    }

    // std::ostringstream oss;
    // for (int i = 0; i < 10000; ++i)
    //     oss << "abc";
    // std::string s = oss.str();

    std::cout << s << std::endl;
    return 0;
}

