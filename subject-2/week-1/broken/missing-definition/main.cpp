// Błąd łączenia: funkcja jest zadeklarowana i wywołana, ale nigdzie niezdefiniowana. Zob. README, sekcja 1.
#include <iostream>

int add(int left, int right); // Deklaracja wystarcza kompilatorowi. Ciała brakuje dopiero linkerowi.

int main() {
    std::cout << add(2, 3) << '\n';
}
