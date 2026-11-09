// Błąd kompilacji: nagłówek <flat_set> (C++23) nie istnieje w g++ 13. Zob. README, sekcja 6.
#include <flat_set>
#include <iostream>

int main() {
    std::flat_set<int> numbers = {3, 1, 2};
    std::cout << numbers.size() << '\n';
}
