// Ostrzeżenie -Wpessimizing-move: std::move przy zwracaniu zmiennej lokalnej. Zob. README, sekcja 4.
#include <iostream>

#include "../../noisy.hpp"

Noisy make_plain() {
    Noisy local("bez move");
    return local; // Kompilator pomija kopię i przeniesienie.
}

Noisy make_with_move() {
    Noisy local("z move");
    return std::move(local); // Wymusza przeniesienie i wyłącza to pominięcie.
}

int main() {
    std::cout << "make_plain():\n";
    Noisy plain = make_plain();
    std::cout << "make_with_move():\n";
    Noisy with_move = make_with_move();
}
