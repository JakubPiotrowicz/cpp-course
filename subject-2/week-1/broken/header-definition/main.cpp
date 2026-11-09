// Błąd łączenia: funkcja bonus jest zdefiniowana w obu plikach .cpp. Zob. README, sekcja 1.
#include "util.hpp"

#include <iostream>

int other_bonus();

int main() {
    std::cout << bonus(1) << ' ' << other_bonus() << '\n';
}
