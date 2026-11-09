// Preprocesor: makra, ich pułapki, wybór kodu przez #if oraz makra predefiniowane.
// Preprocesor działa przed kompilatorem i operuje na tekście, nie na typach. Edytor wyszarza
// gałęzie #if, które nie trafią do programu, bo kompilator ich w ogóle nie zobaczy.
#include <algorithm>
#include <iostream>

#define SCALE 2 + 3
#define SQUARE(x) x * x
#define SQUARE_SAFE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define SHOW(expression) std::cout << #expression << " = " << (expression) << '\n'

// Wartość domyślna, którą można zmienić z wiersza poleceń: g++ -DBUILD_NAME='"test"' ...
#ifndef BUILD_NAME
#define BUILD_NAME "domyślna"
#endif

int main() {
    std::cout << "--- Makro to podmiana tekstu ---\n";
    std::cout << "4 * SCALE = " << 4 * SCALE << " (rozwija się do 4 * 2 + 3)\n";
    int n = 3;
    std::cout << "SQUARE(n + 1) = " << SQUARE(n + 1) << " (rozwija się do n + 1 * n + 1)\n";
    std::cout << "SQUARE_SAFE(n + 1) = " << SQUARE_SAFE(n + 1) << '\n';
    SHOW(SQUARE_SAFE(n) + 1); // Operator # zamienia argument na napis z jego tekstem.

    std::cout << "\n--- Argument makra może wykonać się dwa razy ---\n";
    int i = 5;
    int from_macro = MAX(i++, 2);
    std::cout << "MAX(i++, 2) = " << from_macro << ", i = " << i << '\n';
    int j = 5;
    int from_function = std::max(j++, 2);
    std::cout << "std::max(j++, 2) = " << from_function << ", j = " << j << '\n';

    std::cout << "\n--- Makra predefiniowane ---\n";
    std::cout << "__FILE__ = " << __FILE__ << ", __LINE__ = " << __LINE__ << '\n';
    std::cout << "__cplusplus = " << __cplusplus << '\n';
    std::cout << "BUILD_NAME = " << BUILD_NAME << '\n';

    std::cout << "\n--- Wybór kodu przed kompilacją ---\n";
#if defined(__linux__)
    const char* platform = "Linux";
#elif defined(_WIN32)
    const char* platform = "Windows";
#elif defined(__APPLE__)
    const char* platform = "macOS";
#else
    const char* platform = "nieznana";
#endif
    std::cout << "platforma: " << platform << '\n';

#if __cplusplus >= 202002L
    std::cout << "kompilacja w trybie C++20 lub nowszym\n";
#else
    std::cout << "kompilacja w starszym trybie\n";
#endif
}
