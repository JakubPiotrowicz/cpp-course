// Błąd kompilacji: funkcja consteval wywołana z wartością znaną dopiero w czasie działania. Zob. README, sekcja 9.
#include <iostream>

consteval int square_now(int x) {
    return x * x;
}

int main() {
    int runtime_value = 7;
    std::cout << square_now(5) << '\n'; // Poprawnie: argument jest stałą.
    std::cout << square_now(runtime_value) << '\n'; // Błąd: runtime_value nie jest stałą.
}
