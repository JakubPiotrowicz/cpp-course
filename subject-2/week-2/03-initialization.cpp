// Inicjowanie obiektów globalnych: kolejność w jednym pliku, inicjowanie przy pierwszym użyciu i constinit.
#include <iostream>

class Tracer {
public:
    explicit Tracer(const char* name) : name_(name) {
        std::cout << "  konstruktor: " << name_ << '\n';
    }

    ~Tracer() {
        std::cout << "  destruktor: " << name_ << '\n';
    }

private:
    const char* name_;
};

// Obiekty globalne powstają przed wejściem do main, w kolejności definicji w tym pliku,
// a są niszczone po zakończeniu main, w kolejności odwrotnej.
Tracer first("globalny pierwszy");
Tracer second("globalny drugi");

// constinit wymaga, żeby inicjowanie odbyło się w czasie kompilacji. Zmienna nie jest const.
constinit int counter = 0;

class Registry {
public:
    Registry() {
        std::cout << "  konstruktor Registry\n";
    }

    int count = 0;
};

// Lokalna zmienna static jest inicjowana przy pierwszym przejściu przez jej deklarację.
// Wszystkie wywołania zwracają ten sam obiekt, a kolejność inicjowania nie zależy od plików.
Registry& registry() {
    static Registry instance;
    return instance;
}

int main() {
    std::cout << "main się zaczyna\n";
    ++counter;
    std::cout << "constinit counter: " << counter << '\n';

    std::cout << "pierwsze wywołanie registry():\n";
    Registry& a = registry();
    ++a.count;
    std::cout << "drugie wywołanie registry():\n";
    Registry& b = registry();
    ++b.count;
    std::cout << "count: " << b.count << ", ten sam obiekt: " << std::boolalpha << (&a == &b) << '\n';
    std::cout << "main się kończy\n";
}
