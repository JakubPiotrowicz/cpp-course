#include <string>
#include <iostream>

// ==, <, > are lexicographic.
// For search you can use find, rfind, find_first_of, find_last_of etc.

int main() {
    std::string s = "abrakadabra";
    std::cout << s.find("ra"); // 2
}
