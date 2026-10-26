#ifndef WEEK2_MATH_HPP
#define WEEK2_MATH_HPP

namespace math {

// A definition: the compiler learns the layout of Point here.
struct Point {
    int x;
    int y;
};

// Declarations: the function bodies live in math.cpp.
int add(int left, int right);
Point add(Point left, Point right);

#ifdef DEMO_HEADER_DEFINITION
// Intentional linker error: both .cpp files get this non-inline definition.
int header_bonus(int value) {
    return value + 1;
}
#endif

} // namespace math

#endif // WEEK2_MATH_HPP
