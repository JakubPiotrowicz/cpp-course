#include <iostream>
#include <string_view>

std::string_view first_word(std::string_view line) {
    size_t pos = line.find(' ');
    if (pos == std::string_view::npos)
        return line;
    return line.substr(0, pos);
}

int main() {
    std::string text = "Hello world from C++23";
    std::cout << first_word(text) << '\n'; // "Hello"
    std::cout << first_word("NoSpaces") << '\n'; // "NoSpaces"
}
