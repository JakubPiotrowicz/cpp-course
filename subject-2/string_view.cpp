#include <iostream>
#include <string>
#include <string_view>

void greet(std::string_view name) {
    std::cout << "Hello, " << name << "!\n";
}

int main() {
    std::string user = "Alice";
    greet(user);           // Works with std::string
    greet("Bob");          // Works with string literal

    std::string text = "abcdef";
    std::string_view part = text.substr(1, 3); // "bcd"
    std::cout << "Substring view: " << part << '\n';

    // Be careful: string_view does not own memory
    // If 'text' is destroyed, 'part' becomes dangling!
}
