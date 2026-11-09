// Składowe statyczne klasy oraz zmienne lokalne static.
// O zmiennych static na poziomie pliku i o inicjowaniu przy pierwszym użyciu jest też temat 2 (week-2/02, 05).
#include <cstddef>
#include <iostream>

class Connection {
public:
    static constexpr std::size_t limit = 3; // Stała wspólna dla całej klasy.

    Connection() : id_(++created_) {
        ++alive_;
        std::cout << "  połączenie " << id_ << " otwarte\n";
    }

    ~Connection() {
        --alive_;
        std::cout << "  połączenie " << id_ << " zamknięte\n";
    }

    // Metoda statyczna nie ma wskaźnika this, więc widzi tylko składowe statyczne.
    static std::size_t alive() {
        return alive_;
    }

    static bool can_open() {
        return alive_ < limit;
    }

    void log() const {
        static int calls = 0; // Jedna zmienna dla wszystkich obiektów. Inicjowana raz, wartość zostaje.
        ++calls;
        std::cout << "  log() wywołane " << calls << ". raz, tym razem przez połączenie " << id_ << '\n';
    }

private:
    // inline static: definicja jest w klasie, więc nie trzeba jej powtarzać w pliku .cpp (od C++17).
    inline static std::size_t created_ = 0;
    inline static std::size_t alive_ = 0;
    std::size_t id_;
};

int next_ticket() {
    static int last = 100; // Inicjowana raz, przy pierwszym wywołaniu, a nie przy każdym.
    return ++last;
}

int expensive_calculation() {
    std::cout << "  obliczam wartość początkową\n";
    return 42;
}

int cached_value() {
    static const int value = expensive_calculation(); // Wywołanie funkcji tylko za pierwszym razem.
    return value;
}

int main() {
    std::cout << "--- Składowe statyczne ---\n";
    std::cout << "otwartych na starcie: " << Connection::alive() << '\n';
    std::cout << "sizeof(Connection) = " << sizeof(Connection) << ", sizeof(size_t) = " << sizeof(std::size_t)
              << " (składowe statyczne nie powiększają obiektu)\n";

    Connection first;
    {
        Connection second;
        std::cout << "otwartych: " << Connection::alive() << ", limit: " << Connection::limit << '\n';
        std::cout << "przez obiekt też można: " << second.alive() << '\n';
        first.log();
        second.log();
    }
    std::cout << "po zamknięciu drugiego: " << Connection::alive() << ", można otworzyć kolejne: "
              << std::boolalpha << Connection::can_open() << '\n';

    std::cout << "\n--- Zmienne lokalne static ---\n";
    std::cout << "bilety: " << next_ticket() << ", " << next_ticket() << ", " << next_ticket() << '\n';

    std::cout << "pierwsze wywołanie cached_value():\n";
    int first_call = cached_value();
    std::cout << "drugie wywołanie cached_value():\n";
    int second_call = cached_value();
    std::cout << "wartości: " << first_call << ", " << second_call << '\n';

    std::cout << "\n--- Koniec main ---\n";
}
