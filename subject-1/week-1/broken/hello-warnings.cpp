// Wariant celowo podejrzany: poprawny kod, który kompilator ostrzega. Zob. README, sekcja 0.
// Kompilacja: make broken (flagi -Wall -Wextra -Wpedantic włączają ostrzeżenia).
#include <iostream>

int main() {
    int unused = 5; // Zmienna nigdy nie jest używana.
    unsigned int three = 3;
    if (three < -1) { // Liczba -1 zostaje zamieniona na ogromną liczbę bez znaku.
        std::cout << "3 jest mniejsze od -1?\n";
    }
    return 0;
}
