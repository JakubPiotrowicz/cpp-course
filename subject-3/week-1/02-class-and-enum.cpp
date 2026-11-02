// Definiowanie typów: enum, enum class, alias using oraz klasa z interfejsem publicznym i prywatnym.
#include <iostream>
#include <stdexcept>

// Stary enum: nazwy trafiają do otaczającego zasięgu, a wartości zamieniają się na int.
enum Direction {
    North,
    South
};

// enum class: nazwy są w zasięgu typu i nie ma niejawnej zamiany na liczby.
// Można wybrać typ bazowy, tu najmniejszy możliwy.
enum class Scale : unsigned char {
    Celsius,
    Kelvin,
    Fahrenheit
};

namespace {

double to_kelvin(double degrees, Scale scale) {
    switch (scale) {
        case Scale::Celsius:
            return degrees + 273.15;
        case Scale::Kelvin:
            return degrees;
        case Scale::Fahrenheit:
            return (degrees + 459.67) * 5.0 / 9.0;
    }
    throw std::logic_error("nieznana skala");
}

double from_kelvin(double kelvin, Scale scale) {
    switch (scale) {
        case Scale::Celsius:
            return kelvin - 273.15;
        case Scale::Kelvin:
            return kelvin;
        case Scale::Fahrenheit:
            return kelvin * 9.0 / 5.0 - 459.67;
    }
    throw std::logic_error("nieznana skala");
}

// Zwraca temperaturę, jeśli jest dopuszczalna. W przeciwnym razie zgłasza wyjątek.
double checked(double kelvin) {
    if (kelvin < 0) {
        throw std::invalid_argument("poniżej zera absolutnego");
    }
    return kelvin;
}

} // namespace

// Interfejs publiczny to konstruktor i metody. Reprezentacja (kelvin_) jest prywatna,
// więc tylko klasa pilnuje niezmiennika: temperatura nie spada poniżej zera absolutnego.
class Temperature {
public:
    using Degrees = double; // Alias zagnieżdżony w klasie: Temperature::Degrees.

    Temperature(Degrees value, Scale scale) : kelvin_(checked(to_kelvin(value, scale))) {}

    Degrees in(Scale scale) const {
        return from_kelvin(kelvin_, scale);
    }

    // Najpierw sprawdzamy nową wartość, dopiero potem ją zapisujemy. Przy błędzie obiekt się nie zmienia.
    void change_by(Degrees delta_kelvin) {
        kelvin_ = checked(kelvin_ + delta_kelvin);
    }

private:
    Degrees kelvin_;
};

struct PlainPoint { // W struct składowe są domyślnie publiczne, w class prywatne.
    int x;
    int y;
};

int main() {
    std::cout << "--- Enum i enum class ---\n";
    std::cout << "North == 0: " << std::boolalpha << (North == 0) << '\n';
    std::cout << "Scale::Kelvin jako liczba: " << static_cast<int>(Scale::Kelvin) << '\n';
    std::cout << "sizeof(Scale) = " << sizeof(Scale) << ", sizeof(Direction) = " << sizeof(Direction)
              << '\n';

    std::cout << "\n--- Klasa z niezmiennikiem ---\n";
    Temperature boiling(100, Scale::Celsius);
    std::cout << "woda wrze: " << boiling.in(Scale::Kelvin) << " K, " << boiling.in(Scale::Fahrenheit)
              << " F\n";

    {
        using enum Scale; // C++20: nazwy enum class bez przedrostka, ale tylko w tym bloku.
        Temperature room(20, Celsius);
        std::cout << "pokój: " << room.in(Fahrenheit) << " F\n";
    }

    try {
        Temperature impossible(-300, Scale::Celsius);
    } catch (const std::invalid_argument& error) {
        std::cout << "błąd: " << error.what() << '\n'; // Wyjątki omawia temat 5.
    }

    try {
        boiling.change_by(-1000);
    } catch (const std::invalid_argument& error) {
        std::cout << "błąd: " << error.what() << '\n';
    }

    Temperature::Degrees raw = boiling.in(Scale::Celsius);
    std::cout << "po nieudanej zmianie nadal: " << raw << " C\n";

    PlainPoint point{3, 4}; // W struct można używać składowych bezpośrednio.
    std::cout << "\nPlainPoint: (" << point.x << ", " << point.y << ")\n";
}
