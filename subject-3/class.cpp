#include <iostream>

// A simple class to represent a rectangle.
class Rectangle {
// Member variables
private:
    int width, height;

// Member functions
public:
    void set_values(int w, int h) {
        width = w;
        height = h;
    }

    int area() {
        return width * height;
    }
};

int main() {
    Rectangle rect;
    rect.set_values(10, 5);
    std::cout << "The area of the rectangle is: " << rect.area() << std::endl;
    return 0;
}
