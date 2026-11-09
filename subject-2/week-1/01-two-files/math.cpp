#include "math.hpp"

namespace math {

int add(int left, int right) {
    return left + right;
}

// Ta sama nazwa jest dozwolona, bo typy parametrów są inne.
Point add(Point left, Point right) {
    return {left.x + right.x, left.y + right.y};
}

} // namespace math
