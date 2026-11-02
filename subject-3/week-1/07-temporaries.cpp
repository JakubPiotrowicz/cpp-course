// Wartości tymczasowe: kiedy powstają, kiedy znikają i kiedy wiązanie z referencją przedłuża im życie.
#include <iostream>
#include <string>

#include "../noisy.hpp"

Noisy make(const char* label) {
    return Noisy(label);
}

Noisy make_named() {
    Noisy local("lokalny");
    return local; // Kompilator zwykle pomija kopię (NRVO), ale nie musi.
}

void use(const Noisy& noisy) {
    std::cout << "  używam " << noisy.label() << '\n';
}

// Zwraca referencję do swojego argumentu. Nie przedłuża życia niczemu.
const Noisy& first_of(const Noisy& first, const Noisy&) {
    return first;
}

int main() {
    std::cout << "--- Tymczasowy obiekt żyje do końca pełnego wyrażenia ---\n";
    use(make("tymczasowy"));
    std::cout << "po średniku\n";

    std::cout << "\n--- Metoda wywołana na wartości tymczasowej ---\n";
    std::size_t length = make("abcdef").label().size();
    std::cout << "długość etykiety: " << length << '\n';

    std::cout << "\n--- Wiązanie z const& przedłuża życie do końca zasięgu referencji ---\n";
    {
        const Noisy& extended = make("przedłużony");
        std::cout << "  w bloku nadal istnieje: " << extended.label() << '\n';
    }
    std::cout << "po bloku\n";

    std::cout << "\n--- To samo dla r-referencji ---\n";
    {
        Noisy&& owner = make("r-referencja");
        std::cout << "  w bloku nadal istnieje: " << owner.label() << '\n';
    }

    std::cout << "\n--- Przedłużenie nie przechodzi przez funkcję ---\n";
    Noisy existing("istniejący");
    std::string copy = first_of(make("tymczasowy argument"), existing).label();
    std::cout << "kopia etykiety (bezpieczna, wykonana przed średnikiem): " << copy << '\n';

    std::cout << "\n--- Zwracanie wartości z funkcji ---\n";
    Noisy result = make("wynik");
    Noisy named = make_named();
    std::cout << "result: " << result.label() << ", named: " << named.label() << '\n';

    std::cout << "\n--- Koniec main, destruktory ---\n";
}
