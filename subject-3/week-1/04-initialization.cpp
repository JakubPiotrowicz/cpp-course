// Inicjowanie: bezpośrednie i przez kopiowanie, nawiasy okrągłe i klamrowe, lista inicjująca, auto.
#include <initializer_list>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

#include "../noisy.hpp"

struct Point {
    int x;
    int y;
};

struct Config {
    int retries = 3;
    std::string name = "domyślna";
};

// Konstruktor z std::initializer_list wygrywa z innymi, gdy użyjemy klamer.
class Stack {
public:
    Stack(std::size_t size, int value) : data_(size, value) {
        std::cout << "  Stack(size, value)\n";
    }

    Stack(std::initializer_list<int> values) : data_(values) {
        std::cout << "  Stack(initializer_list)\n";
    }

    std::size_t size() const {
        return data_.size();
    }

private:
    std::vector<int> data_;
};

int main() {
    std::cout << "--- Bezpośrednie i przez kopiowanie ---\n";
    Noisy a("a");
    std::cout << "Noisy b = Noisy(\"b\"):\n";
    Noisy b = Noisy("b"); // Od C++17 obiekt powstaje od razu w b, bez kopii.
    std::cout << "Noisy c = a:\n";
    Noisy c = a;
    std::cout << "Noisy d(a):\n";
    Noisy d(a);
    std::cout << "Noisy e{a}:\n";
    Noisy e{a};

    std::cout << "\n--- Nawiasy okrągłe i klamrowe ---\n";
    std::vector<int> round(3, 7); // Trzy elementy równe 7.
    std::vector<int> curly{3, 7}; // Dwa elementy: 3 i 7.
    std::cout << "vector(3, 7) ma " << round.size() << " elementy, vector{3, 7} ma " << curly.size() << '\n';
    Stack s1(3, 7);
    Stack s2{3, 7};
    std::cout << "rozmiary: " << s1.size() << " i " << s2.size() << '\n';

    std::cout << "\n--- Zawężanie ---\n";
    int truncated = 3.9; // Znak = pozwala na utratę informacji. Zapis int{3.9} się nie skompiluje.
    std::cout << "int truncated = 3.9 daje " << truncated << '\n';

    std::cout << "\n--- Wartości domyślne ---\n";
    int zero{}; // Puste klamry dają zero. Zwykłe "int x;" zostawia wartość nieokreśloną.
    Point origin{};
    Point point{1, 2};
    Point named{.x = 5, .y = 6}; // C++20: nazwane pola, w kolejności deklaracji.
    std::cout << "zero = " << zero << ", origin = (" << origin.x << ", " << origin.y << ")\n";
    std::cout << "point = (" << point.x << ", " << point.y << "), named = (" << named.x << ", " << named.y
              << ")\n";

    Config defaults{};
    Config custom{.name = "własna"};
    std::cout << "defaults: " << defaults.retries << ", " << defaults.name << '\n';
    std::cout << "custom: " << custom.retries << ", " << custom.name << '\n';

    std::cout << "\n--- auto ---\n";
    auto i = 5;
    auto j{5};
    auto k = {5};
    static_assert(std::is_same_v<decltype(i), int>);
    static_assert(std::is_same_v<decltype(j), int>);
    static_assert(std::is_same_v<decltype(k), std::initializer_list<int>>);
    std::cout << "auto i = 5 i auto j{5} dają int, a auto k = {5} daje std::initializer_list<int>\n";

    std::cout << "\n--- Koniec main, destruktory ---\n";
}
