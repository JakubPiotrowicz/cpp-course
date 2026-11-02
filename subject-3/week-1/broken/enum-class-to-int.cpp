// Błąd kompilacji: enum class nie zamienia się niejawnie na liczbę. Zob. README, sekcja 2.
#include <iostream>

enum class Scale {
    Celsius,
    Kelvin
};

int main() {
    int number = Scale::Kelvin; // Błąd. Poprawnie: static_cast<int>(Scale::Kelvin).
    std::cout << number << '\n';
}
