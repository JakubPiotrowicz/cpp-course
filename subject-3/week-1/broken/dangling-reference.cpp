// Wiszące odwołanie do wartości tymczasowej. Zob. README, sekcja 7.
// AddressSanitizer zgłasza heap-use-after-free.
#include <iostream>
#include <string>

const std::string& longer(const std::string& left, const std::string& right) {
    return left.size() >= right.size() ? left : right;
}

int main() {
    // Tymczasowe napisy giną na końcu tego wiersza, a referencja nadal na jeden z nich wskazuje.
    // Napisy mają 40 i 30 znaków, więc są na stercie (krótsze mieszczą się w samym obiekcie).
    const std::string& result = longer(std::string(40, 'a'), std::string(30, 'b'));
    std::cout << result << '\n';
}
