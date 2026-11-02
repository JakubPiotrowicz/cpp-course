// Błąd kompilacji: zawężanie w inicjowaniu klamrami. Zob. README, sekcja 4.
#include <iostream>

int main() {
    int allowed = 3.9; // Znak = zgadza się na utratę części ułamkowej.
    int forbidden{3.9}; // Błąd: klamry nie pozwalają na zawężenie.
    std::cout << allowed << forbidden << '\n';
}
