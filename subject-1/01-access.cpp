#include <string>
#include <iostream>

int main() {
    std::string s = "Hello";
    std::cout << s[1];   // 'e'
    std::cout << s.at(10); // exception std::out_of_range
}
