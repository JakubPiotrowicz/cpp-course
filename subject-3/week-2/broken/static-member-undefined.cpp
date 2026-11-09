// Błąd łączenia: składowa statyczna jest zadeklarowana, ale nigdzie niezdefiniowana. Zob. README, sekcja 1.
#include <iostream>

class Counter {
public:
    static int count; // Tylko deklaracja. Brak "inline" i brak definicji poza klasą.
};

// Brakuje wiersza: int Counter::count = 0;

int main() {
    ++Counter::count;
    std::cout << Counter::count << '\n';
}
