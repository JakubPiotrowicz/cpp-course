// Instrukcja warunkowa wyliczana w czasie kompilacji: if constexpr.
// Szablony (template) omawia temat 4. Tu wystarczy wiedzieć, że kompilator tworzy osobną wersję funkcji
// dla każdego typu T użytego w wywołaniu.
#include <iostream>
#include <string>
#include <type_traits>

template <typename T>
std::string describe(const T& value) {
    if constexpr (std::is_integral_v<T>) {
        return "liczba całkowita " + std::to_string(value);
    } else if constexpr (std::is_floating_point_v<T>) {
        return "liczba zmiennoprzecinkowa " + std::to_string(value);
    } else {
        // Ta gałąź nie jest kompilowana dla int ani double, więc std::string(value) nie musi mieć sensu dla liczb.
        return "napis " + std::string(value);
    }
}

int main() {
    std::cout << describe(42) << '\n';
    std::cout << describe(2.5) << '\n';
    std::cout << describe("tekst") << '\n';

    // Poza szablonem if constexpr też działa, ale obie gałęzie muszą być poprawne.
    if constexpr (sizeof(void*) == 8) {
        std::cout << "wskaźnik ma 8 bajtów\n";
    } else {
        std::cout << "wskaźnik ma inny rozmiar\n";
    }
}
