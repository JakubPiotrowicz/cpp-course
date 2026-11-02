// Obliczenia w czasie kompilacji: constexpr, consteval i constinit (C++20).
// O inicjowaniu zmiennych globalnych i constinit była też mowa w temacie 2 (week-2/05).
#include <iostream>
#include <type_traits>

// Może zostać wykonana w czasie kompilacji (gdy argumenty są stałe) albo w czasie działania programu.
constexpr int square(int x) {
    return x * x;
}

// Musi zostać wykonana w czasie kompilacji. Każde wywołanie z wartością niestałą jest błędem.
consteval int square_now(int x) {
    return x * x;
}

constexpr const char* where() {
    return std::is_constant_evaluated() ? "kompilacji" : "działania programu";
}

constexpr int limit = square(4); // constexpr oznacza też const. Wartość jest znana w czasie kompilacji.
constinit int counter = square(3); // Inicjowany stałą, ale nie jest const: można go zmieniać.

constexpr const char* at_compile_time = where();

int main() {
    static_assert(square(5) == 25);
    static_assert(square_now(6) == 36);

    std::cout << "limit = " << limit << ", counter = " << counter << '\n';
    ++counter;
    std::cout << "po ++counter: " << counter << '\n';

    std::cout << "\n--- Gdzie wykonuje się funkcja ---\n";
    const char* at_run_time = where();
    std::cout << "constexpr const char* z where(): " << at_compile_time << '\n';
    std::cout << "zwykła zmienna z where(): " << at_run_time << '\n';

    int runtime_value = 7;
    int from_variable = square(runtime_value); // Zwykłe wywołanie w czasie działania programu.
    std::cout << "square(runtime_value) = " << from_variable << '\n';
}
