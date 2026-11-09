// Błąd kompilacji: r-referencja nie wiąże się z nazwanym obiektem. Zob. README, sekcja 4.
#include <iostream>
#include <string>

void consume(std::string&& text) {
    std::cout << "przejmuję: " << text << '\n';
}

int main() {
    std::string name = "Ala";
    consume(std::string("tymczasowy")); // Poprawnie: wartość tymczasowa.
    consume(name); // Błąd: name to l-wartość. Poprawnie: consume(std::move(name)).
}
