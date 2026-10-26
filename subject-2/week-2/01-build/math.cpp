#include "math.hpp"

namespace math {

int add(int left, int right) {
    return left + right;
}

// The same name is allowed because the parameter types are different.
Point add(Point left, Point right) {
    return {left.x + right.x, left.y + right.y};
}

} // namespace math
