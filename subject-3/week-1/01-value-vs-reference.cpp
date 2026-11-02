// Semantyka wartości i semantyka referencji: kto widzi zmianę, a kto pracuje na kopii.
#include <iostream>
#include <vector>

#include "../noisy.hpp"

struct Point {
    int x;
    int y;
};

void shift_copy(Point point) {
    point.x += 10; // Zmiana kopii. Wywołujący jej nie zobaczy.
}

void shift_in_place(Point& point) {
    point.x += 10;
}

void print(const char* name, const Point& point) {
    std::cout << name << " = (" << point.x << ", " << point.y << ")\n";
}

void take_by_value(Noisy noisy) {
    std::cout << "  w funkcji: " << noisy.label() << '\n';
}

void take_by_const_ref(const Noisy& noisy) {
    std::cout << "  w funkcji: " << noisy.label() << '\n';
}

Noisy make_noisy() {
    return Noisy("z funkcji");
}

int main() {
    std::cout << "--- Kopia jest niezależnym obiektem ---\n";
    Point a{1, 2};
    Point b = a;
    b.x = 100;
    print("a", a);
    print("b", b);

    // Kontenery standardowe też mają semantykę wartości: kopia zawiera własne elementy.
    std::vector<int> first = {1, 2, 3};
    std::vector<int> second = first;
    second[0] = 99;
    std::cout << "first[0] = " << first[0] << ", second[0] = " << second[0] << '\n';

    std::cout << "\n--- Referencja to druga nazwa tego samego obiektu ---\n";
    Point& alias = a;
    alias.x = 7;
    print("a", a);
    alias = b; // Referencji nie da się przestawić. Do obiektu a trafia kopia wartości b.
    print("a", a);
    std::cout << std::boolalpha << "alias to ten sam obiekt co a: " << (&alias == &a) << '\n';

    std::cout << "\n--- Przekazywanie do funkcji ---\n";
    shift_copy(a);
    print("a po shift_copy", a);
    shift_in_place(a);
    print("a po shift_in_place", a);

    std::cout << "\n--- Przekazywanie obiektu, który wypisuje swoje operacje ---\n";
    Noisy original("original");
    std::cout << "przez wartość:\n";
    take_by_value(original);
    std::cout << "przez const&:\n";
    take_by_const_ref(original);
    std::cout << "przez wartość, argumentem jest wynik funkcji:\n";
    take_by_value(make_noisy());

    std::cout << "\n--- Pętla po kontenerze ---\n";
    std::vector<Noisy> items;
    items.reserve(2); // Bez tego wstawianie kopiowałoby lub przenosiło elementy przy powiększaniu.
    items.emplace_back("pierwszy");
    items.emplace_back("drugi");
    std::cout << "for (auto item : items):\n";
    for (auto item : items) {
        std::cout << "  element " << item.label() << '\n';
    }
    std::cout << "for (const auto& item : items):\n";
    for (const auto& item : items) {
        std::cout << "  element " << item.label() << '\n';
    }

    std::cout << "\n--- Koniec main, destruktory ---\n";
}
