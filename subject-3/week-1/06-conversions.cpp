// Konwersje: konstruktor jednoargumentowy, explicit, operator konwersji i ciąg konwersji niejawnych.
#include <iostream>
#include <string>

class Meters {
public:
    Meters(double value) : value_(value) { // Bez explicit: niejawna konwersja z double.
        std::cout << "  Meters(" << value << ")\n";
    }

    double value() const {
        return value_;
    }

private:
    double value_;
};

class Seconds {
public:
    explicit Seconds(double value) : value_(value) { // explicit: tylko jawne tworzenie obiektu.
        std::cout << "  Seconds(" << value << ")\n";
    }

    double value() const {
        return value_;
    }

private:
    double value_;
};

// Operator konwersji do double: obiekt można użyć tam, gdzie oczekiwany jest double.
class Ratio {
public:
    Ratio(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {}

    operator double() const {
        return static_cast<double>(numerator_) / denominator_;
    }

private:
    int numerator_;
    int denominator_;
};

// Operator konwersji do bool jako explicit działa tylko w warunkach (if, while, !, &&, ||).
class Handle {
public:
    explicit Handle(int descriptor) : descriptor_(descriptor) {}

    explicit operator bool() const {
        return descriptor_ >= 0;
    }

private:
    int descriptor_;
};

class Name {
public:
    Name(const std::string& text) : text_(text) {}

    const std::string& text() const {
        return text_;
    }

private:
    std::string text_;
};

void walk(Meters distance) {
    std::cout << "  walk: " << distance.value() << " m\n";
}

void wait(Seconds time) {
    std::cout << "  wait: " << time.value() << " s\n";
}

void greet(const Name& name) {
    std::cout << "  Cześć, " << name.text() << "!\n";
}

int main() {
    std::cout << "--- Konstruktor jednoargumentowy ---\n";
    Meters first = 5.5;
    std::cout << "walk(100):\n";
    walk(100); // int -> double (konwersja standardowa) -> Meters (konwersja użytkownika).

    std::cout << "\n--- explicit ---\n";
    Seconds second(2.5);
    wait(second);
    std::cout << "wait(Seconds{10}):\n";
    wait(Seconds{10});

    std::cout << "\n--- Operator konwersji ---\n";
    Ratio half(1, 2);
    double as_double = half;
    int as_int = half; // double -> int po drodze: ułamek ginie.
    std::cout << "double: " << as_double << ", int: " << as_int << ", half + 1 = " << half + 1 << '\n';

    Handle valid(3);
    Handle invalid(-1);
    std::cout << std::boolalpha;
    std::cout << "if (valid): " << (valid ? "tak" : "nie") << ", if (invalid): " << (invalid ? "tak" : "nie")
              << '\n';
    std::cout << "static_cast<bool>(valid) = " << static_cast<bool>(valid) << '\n';

    std::cout << "\n--- Ciąg konwersji: co najwyżej jedna konwersja użytkownika ---\n";
    greet(std::string("Ala")); // std::string -> Name: jedna konwersja użytkownika.
    greet(Name("Ola"));
    std::cout << "first.value() = " << first.value() << '\n';
}
