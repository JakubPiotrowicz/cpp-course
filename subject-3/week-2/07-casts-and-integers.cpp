// Dygresje: rzutowanie static_cast oraz typy całkowite o zadanej szerokości.
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <utility>

enum class Level : std::uint8_t {
    Low = 1,
    High = 9
};

int main() {
    std::cout << "--- Rzutowanie ---\n";
    double pi = 3.99;
    int truncated = static_cast<int>(pi); // Jawna, wyszukiwalna i ograniczona do sensownych konwersji.
    int c_style = (int)pi; // Zapis z C: robi to samo, ale bez zabezpieczeń i trudno go znaleźć w kodzie.
    std::cout << "static_cast<int>(3.99) = " << truncated << ", (int)3.99 = " << c_style << '\n';

    int apples = 7;
    int people = 2;
    std::cout << "7 / 2 = " << apples / people << ", ale static_cast<double>(7) / 2 = "
              << static_cast<double>(apples) / people << '\n';
    std::cout << "Level::High jako liczba: " << static_cast<int>(Level::High) << '\n';

    std::cout << "\n--- Typy o zadanej szerokości (<cstdint>) ---\n";
    std::cout << "sizeof: int8_t = " << sizeof(std::int8_t) << ", int16_t = " << sizeof(std::int16_t)
              << ", int32_t = " << sizeof(std::int32_t) << ", int64_t = " << sizeof(std::int64_t)
              << ", size_t = " << sizeof(std::size_t) << '\n';
    std::cout << "int32_t: od " << std::numeric_limits<std::int32_t>::min() << " do "
              << std::numeric_limits<std::int32_t>::max() << '\n';

    std::int8_t letter = 65;
    std::cout << "int8_t o wartości 65 wypisany wprost: " << letter << ", po rzutowaniu: "
              << static_cast<int>(letter) << '\n';

    std::cout << "\n--- Arytmetyka bez znaku zawija się ---\n";
    std::uint8_t byte = 255;
    byte = byte + 1; // Dodawanie odbywa się na int, a zapis do uint8_t zachowuje resztę z dzielenia przez 256.
    std::cout << "uint8_t 255 + 1 = " << static_cast<int>(byte) << '\n';

    std::size_t smaller = 2;
    std::size_t larger = 3;
    std::cout << "size_t 2 - 3 = " << smaller - larger << '\n';

    std::cout << "\n--- Porównywanie liczb ze znakiem i bez znaku ---\n";
    int negative = -1;
    unsigned int one = 1;
    std::cout << std::boolalpha;
    std::cout << "-1 < 1u po zamianie na unsigned: " << (static_cast<unsigned int>(negative) < one) << '\n';
    std::cout << "std::cmp_less(-1, 1u): " << std::cmp_less(negative, one) << '\n';
}
