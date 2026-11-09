// Przenoszenie: r-referencje, std::move, przeciążanie po rodzaju wartości, stan po przeniesieniu i noexcept.
#include <iostream>
#include <utility>
#include <vector>

#include "../noisy.hpp"

void accept(const Noisy&) {
    std::cout << "  accept(const Noisy&)\n";
}

void accept(Noisy&&) {
    std::cout << "  accept(Noisy&&)\n";
}

// Dwie klasy różnią się tylko tym, czy przenoszenie jest noexcept.
class Careful {
public:
    Careful() = default;

    Careful(const Careful&) {
        std::cout << "  Careful: kopia\n";
    }

    Careful(Careful&&) noexcept {
        std::cout << "  Careful: przeniesienie\n";
    }
};

class Careless {
public:
    Careless() = default;

    Careless(const Careless&) {
        std::cout << "  Careless: kopia\n";
    }

    Careless(Careless&&) {
        std::cout << "  Careless: przeniesienie\n";
    }
};

int main() {
    std::cout << "--- std::move to tylko rzutowanie na r-wartość ---\n";
    Noisy source("source");
    Noisy target = std::move(source);
    std::cout << "etykieta source po przeniesieniu: [" << source.label() << "]\n";
    std::cout << "etykieta target: [" << target.label() << "]\n";

    std::cout << "\n--- Przeciążenia ---\n";
    Noisy lvalue("lvalue");
    std::cout << "accept(lvalue):\n";
    accept(lvalue);
    std::cout << "accept(std::move(lvalue)):\n";
    accept(std::move(lvalue)); // Samo wywołanie niczego nie przenosi. Przenosi dopiero kod w środku.
    std::cout << "etykieta lvalue po wywołaniu: [" << lvalue.label() << "]\n";
    std::cout << "accept(Noisy(\"tymczasowy\")):\n";
    accept(Noisy("tymczasowy"));

    std::cout << "\n--- Przypisanie przenoszące ---\n";
    Noisy left("left");
    Noisy right("right");
    left = std::move(right);
    std::cout << "left: [" << left.label() << "], right: [" << right.label() << "]\n";

    std::cout << "\n--- Obiekt const nie da się przenieść ---\n";
    const Noisy fixed("fixed");
    Noisy attempt = std::move(fixed); // r-wartość const pasuje tylko do konstruktora kopiującego.

    std::cout << "\n--- Powiększanie wektora a noexcept ---\n";
    std::cout << "Careful:\n";
    std::vector<Careful> careful;
    for (int i = 0; i < 4; ++i) {
        careful.emplace_back();
    }
    std::cout << "Careless:\n";
    std::vector<Careless> careless;
    for (int i = 0; i < 4; ++i) {
        careless.emplace_back();
    }

    std::cout << "\n--- Koniec main, destruktory ---\n";
}
