#include "math.hpp"
#include "math.hpp" // Intentionally repeated: the guard skips the second copy.

#include <iostream>

int main() {
    // The compiler chooses the overload using the argument types.
    std::cout << math::add(2, 3) << '\n';

    const math::Point result = math::add(math::Point{1, 2}, math::Point{3, 4});
    std::cout << result.x << ' ' << result.y << '\n';
}
