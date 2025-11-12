#include <iostream>

// Defines a strongly-typed enumeration for colors
enum class Color {
    Red,
    Green,
    Blue
};

int main() {
    Color myColor = Color::Red;

    if (myColor == Color::Red) {
        std::cout << "The color is Red." << std::endl;
    }

    // int colorValue = myColor; // Error: No implicit conversion to int
    int colorValue = static_cast<int>(myColor); // OK: Explicit cast
    std::cout << "Integer value of Red: " << colorValue << std::endl;

    return 0;
}
