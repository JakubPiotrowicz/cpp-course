#include "math.hpp"
#include "math.hpp" // Celowo drugi raz: osłona nagłówka sprawia, że jego treść zostanie wczytana tylko raz.

#include <iostream>

int main() {
    // Kompilator wybiera przeciążenie na podstawie typów argumentów.
    std::cout << math::add(2, 3) << '\n';

    const math::Point result = math::add(math::Point{1, 2}, math::Point{3, 4});
    std::cout << result.x << ' ' << result.y << '\n';
}
