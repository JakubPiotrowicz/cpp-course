// const, constexpr i makra: typ, zasięg i moment obliczenia wartości.
#include <iostream>
#include <type_traits>

#define PI_MACRO 3.14159 // Tekst podstawiany przez preprocesor. Nie ma typu ani zasięgu.

const double pi_const = 3.14159; // Obiekt typu const double. Na poziomie pliku ma powiązanie wewnętrzne.
constexpr double pi_constexpr = 3.14159; // Wartość musi być znana w czasie kompilacji.
extern const int exported_limit = 9; // Dopiero extern daje powiązanie zewnętrzne dla const.

namespace geometry {

constexpr double pi = 3.14159; // Ma zasięg: geometry::pi nie koliduje z innymi nazwami pi.

} // namespace geometry

int read_value() {
    return 5; // Zwykła funkcja: jej wyniku nie da się obliczyć w czasie kompilacji.
}

static_assert(std::is_same_v<decltype(pi_const), const double>);
static_assert(std::is_same_v<decltype(pi_constexpr), const double>); // constexpr oznacza też const.

int main() {
    std::cout << "--- Makro i stałe ---\n";
    std::cout << "PI_MACRO = " << PI_MACRO << ", pi_const = " << pi_const << ", geometry::pi = " << geometry::pi
              << '\n';
    const double* address = &pi_const; // Stała jest obiektem: ma adres. Makro nie ma (&PI_MACRO to błąd).
    std::cout << "adres pi_const można wziąć: " << std::boolalpha << (address != nullptr) << '\n';

    std::cout << "\n--- Zasięg: stała może przesłonić inną, makro nie ---\n";
    const int limit = 3;
    {
        const int limit = 5;
        std::cout << "wewnątrz bloku: " << limit << '\n';
    }
    std::cout << "na zewnątrz bloku: " << limit << '\n';

    std::cout << "\n--- const a constexpr ---\n";
    const int computed_later = read_value(); // Dozwolone: const nie wymaga wartości znanej wcześniej.
    constexpr int known_early = 2 + 3; // Musi być stałą w czasie kompilacji.
    const int also_known_early = 2 + 3; // Takie const też bywa stałą w czasie kompilacji.
    static_assert(known_early == 5);
    static_assert(also_known_early == 5);
    std::cout << "computed_later = " << computed_later << ", known_early = " << known_early << '\n';
    std::cout << "exported_limit = " << exported_limit << '\n';
}
