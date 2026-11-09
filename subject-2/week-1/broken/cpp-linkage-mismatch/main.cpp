// Błąd łączenia: deklaracja bez extern "C" żąda symbolu zakodowanego z typem parametru. Zob. README, sekcja 5.
#include <iostream>

int triple(int value); // Powinno być: extern "C" int triple(int value);

int main() {
    std::cout << "triple(7) = " << triple(7) << '\n';
}
