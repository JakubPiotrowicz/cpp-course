#include <iostream>

void f(int) {
    std::cout << "f(int)\n";
}

void f(const char*) {
    std::cout << "f(const char*)\n";
}

int main() {
    // f(NULL);  // ambigious / sometimes NULL is defined as 0, then f(int) is called
    f(nullptr);  // nullptr has type std::nullptr_t -> f(const char*)
}
