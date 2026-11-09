// Przeciążanie funkcji: wybór wersji na podstawie typów argumentów oraz kodowanie nazw (name mangling).
#include <iostream>
#include <string>

void describe(int) {
    std::cout << "describe(int)\n";
}

void describe(long) {
    std::cout << "describe(long)\n";
}

void describe(double) {
    std::cout << "describe(double)\n";
}

void describe(const char*) {
    std::cout << "describe(const char*)\n";
}

void describe(const std::string&) {
    std::cout << "describe(const std::string&)\n";
}

int main() {
    std::cout << "--- Dokładne dopasowanie ---\n";
    describe(1);
    describe(1L);
    describe(1.5);
    describe("tekst");
    describe(std::string("napis"));

    std::cout << "\n--- Promocje (wygrywają z konwersjami) ---\n";
    describe('a'); // char -> int
    describe(static_cast<short>(2)); // short -> int
    describe(1.5f); // float -> double
}
