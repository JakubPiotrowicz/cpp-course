// Przestrzenie nazw: nazwa kwalifikowana, deklaracja using i dyrektywa using, aliasy oraz ADL.
#include <iostream>

namespace metric {

int step = 1;

} // namespace metric

namespace imperial {

int step = 3;

} // namespace imperial

namespace company::tools { // Zagnieżdżona przestrzeń w jednym zapisie (C++17).

int version() {
    return 7;
}

} // namespace company::tools

namespace ct = company::tools; // Alias przestrzeni nazw.

namespace shapes {

struct Circle {
    int radius;
};

void print(const Circle& circle) {
    std::cout << "okrąg o promieniu " << circle.radius << '\n';
}

} // namespace shapes

int main() {
    std::cout << "--- Nazwa kwalifikowana ---\n";
    std::cout << "metric::step: " << metric::step << ", imperial::step: " << imperial::step << '\n';

    std::cout << "\n--- Deklaracja using ---\n";
    {
        using metric::step; // Wprowadza jedną nazwę do bieżącego bloku.
        std::cout << "step: " << step << '\n';
    }

    std::cout << "\n--- Dyrektywa using ---\n";
    {
        using namespace imperial; // Udostępnia nazwy z przestrzeni przy wyszukiwaniu. Nic nie kopiuje.
        std::cout << "step: " << step << '\n';
    }

    std::cout << "\n--- Alias przestrzeni ---\n";
    std::cout << "ct::version() = " << ct::version() << '\n';

    std::cout << "\n--- Wyszukiwanie zależne od argumentów (ADL) ---\n";
    shapes::Circle circle{4};
    print(circle); // Bez shapes::, bo kompilator szuka też w przestrzeni nazw argumentu.
}
