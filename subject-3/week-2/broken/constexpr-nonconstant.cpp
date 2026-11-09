// Błąd kompilacji: constexpr wymaga wartości znanej w czasie kompilacji. Zob. README, sekcja 6.
#include <iostream>

int read_limit() {
    return 5; // Zwykła funkcja: kompilator nie może jej policzyć w czasie kompilacji.
}

constexpr int twice(int value) {
    return 2 * value;
}

int main() {
    int runtime_value = read_limit();
    constexpr int fine = twice(4); // Poprawnie: argument jest stałą.
    constexpr int from_function = read_limit(); // Błąd: wywołanie funkcji niebędącej constexpr.
    constexpr int from_variable = twice(runtime_value); // Błąd: runtime_value nie jest stałą.
    std::cout << fine << from_function << from_variable << '\n';
}
