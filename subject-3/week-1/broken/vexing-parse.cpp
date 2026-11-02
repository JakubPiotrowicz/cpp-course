// Ostrzeżenie -Wvexing-parse: puste nawiasy to deklaracja funkcji, a nie obiekt. Zob. README, sekcja 4.
#include <iostream>
#include <string>

int main() {
    std::string text(); // Deklaracja funkcji text() zwracającej std::string, a nie pusty napis.
    std::string fixed{}; // Puste klamry zawsze tworzą obiekt.
    std::cout << "fixed ma " << fixed.size() << " znaków\n";
}
