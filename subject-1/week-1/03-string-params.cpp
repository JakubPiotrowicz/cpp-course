#include <iostream>
#include <string>
#include <string_view>

#include "alloc_counter.hpp"

// Trzy sposoby przekazania napisu tylko do odczytu.
std::size_t by_value(std::string s) {
    return s.size(); // Parametr jest kopią.
}

std::size_t by_const_ref(const std::string& s) {
    return s.size(); // Parametr jest nazwą oryginału, ale nie wolno go zmienić.
}

std::size_t by_view(std::string_view s) {
    return s.size(); // Parametr to wskaźnik i długość, bez własnej pamięci.
}

int main() {
    // Napisy krótkie (zwykle do 15 znaków) mieszczą się w samym obiekcie, bez alokacji.
    // Dlatego do pomiaru bierzemy napis dłuższy.
    const std::string text(40, 'x');
    const std::string shorter = "abc";
    const char* literal = "literał dłuższy niż piętnaście znaków";

    std::cout << "alokacje:\n";
    std::cout << "  by_value(text)          " << alloc::count([&] { by_value(text); }) << '\n';
    std::cout << "  by_value(shorter)       " << alloc::count([&] { by_value(shorter); }) << '\n';
    std::cout << "  by_const_ref(text)      " << alloc::count([&] { by_const_ref(text); }) << '\n';
    std::cout << "  by_const_ref(literal)   " << alloc::count([&] { by_const_ref(literal); }) << '\n';
    std::cout << "  by_view(text)           " << alloc::count([&] { by_view(text); }) << '\n';
    std::cout << "  by_view(literal)        " << alloc::count([&] { by_view(literal); }) << '\n';

    // string_view nie jest właścicielem napisu. Poniżej widok wskazuje na obiekt,
    // który istnieje, więc jest bezpieczny. Gdyby wskazywał na tymczasowy std::string,
    // po średniku wisiałby w próżni (zob. README).
    std::string_view part = std::string_view{text}.substr(0, 5);
    std::cout << "part = " << part << '\n';
}
