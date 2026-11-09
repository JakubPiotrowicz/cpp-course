// constexpr w funkcjach i klasach: obiekty i obliczenia dostępne w czasie kompilacji.
#include <array>
#include <cstddef>
#include <iostream>

// Klasa z konstruktorem constexpr jest typem literalnym: jej obiekty mogą istnieć w czasie kompilacji.
class Interval {
public:
    constexpr Interval(int begin, int end) : begin_(begin), end_(end) {}

    constexpr int length() const {
        return end_ - begin_;
    }

    constexpr bool contains(int value) const {
        return begin_ <= value && value < end_;
    }

    constexpr Interval shifted(int by) const {
        return Interval(begin_ + by, end_ + by);
    }

private:
    int begin_;
    int end_;
};

constexpr Interval window(1, 5);
constexpr Interval later = window.shifted(10);

static_assert(window.length() == 4);
static_assert(window.contains(4));
static_assert(!window.contains(5));
static_assert(later.contains(12));

constexpr int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i) { // W funkcji constexpr można używać pętli i zmiennych lokalnych.
        result *= i;
    }
    return result;
}

static_assert(factorial(5) == 120);

constexpr std::array<int, 6> make_squares() {
    std::array<int, 6> result{};
    for (std::size_t i = 0; i < result.size(); ++i) {
        result[i] = static_cast<int>(i * i);
    }
    return result;
}

constexpr auto squares = make_squares(); // Cała tablica jest policzona przez kompilator.

int main() {
    std::cout << "--- Obiekty w czasie kompilacji ---\n";
    std::array<int, window.length()> buffer{}; // Rozmiar tablicy musi być wyrażeniem stałym.
    std::cout << "buffer ma " << buffer.size() << " elementy\n";
    std::cout << "squares:";
    for (int value : squares) {
        std::cout << ' ' << value;
    }
    std::cout << '\n';

    std::cout << "\n--- Te same funkcje w czasie działania ---\n";
    int runtime_end = 3;
    Interval dynamic(0, runtime_end); // Argument nie jest stałą, więc obiekt powstaje w czasie działania.
    std::cout << "dynamic.length() = " << dynamic.length() << ", factorial(runtime_end) = "
              << factorial(runtime_end) << '\n';
    std::cout << std::boolalpha << "dynamic.contains(2) = " << dynamic.contains(2) << '\n';
}
