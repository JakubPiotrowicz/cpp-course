#include <iostream>
#include <sstream>
#include <string>

#include "alloc_counter.hpp"

constexpr int repetitions = 10000;

std::string append_plain() {
    std::string s;
    for (int i = 0; i < repetitions; ++i) {
        s += "abc"; // Gdy brakuje miejsca, napis przenosi się do większego bufora.
    }
    return s;
}

std::string append_reserved() {
    std::string s;
    s.reserve(3 * repetitions); // Jedna alokacja z góry.
    for (int i = 0; i < repetitions; ++i) {
        s += "abc";
    }
    return s;
}

std::string append_stream() {
    std::ostringstream out;
    for (int i = 0; i < repetitions; ++i) {
        out << "abc";
    }
    return out.str(); // Kopiuje zawartość bufora do nowego napisu.
}

int main() {
    std::string result;
    std::cout << "alokacje przy " << repetitions << " dopisaniach:\n";
    std::cout << "  zwykle dopisywanie   " << alloc::count([&] { result = append_plain(); }) << '\n';
    std::cout << "  po reserve           " << alloc::count([&] { result = append_reserved(); }) << '\n';
    std::cout << "  ostringstream        " << alloc::count([&] { result = append_stream(); }) << '\n';

    // Rośnie pojemność (capacity), nie rozmiar (size). Pokazujemy momenty zmiany.
    std::string s;
    std::size_t last_capacity = s.capacity();
    std::cout << "capacity na początku: " << last_capacity << '\n';
    for (int i = 0; i < 200; ++i) {
        s += 'x';
        if (s.capacity() != last_capacity) {
            last_capacity = s.capacity();
            std::cout << "  size = " << s.size() << ", capacity = " << last_capacity << '\n';
        }
    }
}
