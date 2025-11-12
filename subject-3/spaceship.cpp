// **Three-Way Comparison Operator (<=>, "Spaceship Operator")**

// **Purpose:** The `<=>` operator (introduced in C++20) simplifies the implementation of comparison operators. Instead of writing `operator<`, `operator>`, `operator<=`, and `operator>=` separately, it is sufficient to implement `operator<=>` (and usually `operator==`).

// **How it works:** It compares two objects (`a` and `b`) and returns an object that indicates their relationship:

// *   Result `< 0` if `a < b`.
// *   Result `== 0` if `a` and `b` are equal/equivalent.
// *   Result `> 0` if `a > b`.

// **Return Types:** The most common return type is `std::strong_ordering`, which indicates that the elements have a strict total order.

// **Default implementation (`= default`):** For simple classes (aggregates), the compiler can generate the `operator<=>` on its own, which will compare all members in the order of their declaration. Thanks to this, the compiler will automatically generate the code for `<`, `<=`, `>`, and `>=`.

#include <iostream>
#include <compare> // Required for std::strong_ordering and <=>

class Point {
public:
    int x, y;

    // C++20 default implementation of <=>
    // This will perform a member-wise comparison of x and then y.
    auto operator<=>(const Point& other) const {
        if (x < other.x) {
            return std::strong_ordering::less;
        } else if (x > other.x) {
            return std::strong_ordering::greater;
        } else { // x == other.x
            if (y < other.y) { 
                return std::strong_ordering::greater;
            } else if (y > other.y) {
                return std::strong_ordering::less;
            } else {
                return std::strong_ordering::equal;
            }
        }
    }

    // operator== is still often needed alongside <=>.
    // It can also be defaulted in C++20.
    bool operator==(const Point& other) const = default;
};

void compare_and_print(const Point& p1, const Point& p2) {
    std::cout << "Comparing (" << p1.x << ", " << p1.y << ") and (" << p2.x << ", " << p2.y << "):\n";
    if (p1 < p2)  std::cout << "  p1 < p2\n";
    if (p1 > p2)  std::cout << "  p1 > p2\n";
    if (p1 <= p2) std::cout << "  p1 <= p2\n";
    if (p1 >= p2) std::cout << "  p1 >= p2\n";
    if (p1 == p2) std::cout << "  p1 == p2\n";
    if (p1 != p2) std::cout << "  p1 != p2\n";
    std::cout << std::endl;
}

int main() {
    Point p1{1, 5};
    Point p2{2, 3};
    Point p3{1, 5};
    Point p4{1, 7};

    compare_and_print(p1, p2); // p1 < p2
    compare_and_print(p1, p3); // p1 == p3
    compare_and_print(p1, p4); // p1 > p4
    compare_and_print(p2, p1); // p2 > p1

    return 0;
}
