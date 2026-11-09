// Błąd kompilacji: zwykłe if sprawdza obie gałęzie. Zob. README, sekcja 5.
#include <iostream>
#include <string>
#include <type_traits>

template <typename T>
std::string describe(const T& value) {
    if (std::is_integral_v<T>) {
        return "liczba " + std::to_string(value);
    } else {
        return "napis " + std::string(value); // Błąd dla T = int: tej gałęzi nie da się skompilować.
    }
}

int main() {
    std::cout << describe(42) << '\n'; // Poprawnie byłoby z if constexpr.
}
