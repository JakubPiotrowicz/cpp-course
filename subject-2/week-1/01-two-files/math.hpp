// Nagłówek opisuje interfejs modułu: typy i deklaracje funkcji, ale nie ich ciała.
#ifndef COURSE_MATH_HPP
#define COURSE_MATH_HPP

namespace math {

// Definicja typu. Każda jednostka translacji, która używa Point, musi ją zobaczyć.
struct Point {
    int x;
    int y;
};

// Deklaracje funkcji. Ciała są w math.cpp.
int add(int left, int right);
Point add(Point left, Point right);

} // namespace math

#endif // COURSE_MATH_HPP
