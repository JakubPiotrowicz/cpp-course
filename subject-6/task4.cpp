#include <iostream>
#include <cassert>

class Rectangle {
public:
    virtual void setWidth(int w) { width_ = w; }
    virtual void setHeight(int h) { height_ = h; }
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    int getArea() const { return width_ * height_; }
protected:
    int width_ = 0, height_ = 0;
};

class Square : public Rectangle {
public:
    // Violating LSP: Changing semantics of setWidth/setHeight
    void setWidth(int w) override {
        width_ = w;
        height_ = w;
    }
    void setHeight(int h) override {
        width_ = h;
        height_ = h;
    }
};

void processRectangle(Rectangle& r) {
    r.setWidth(5);
    r.setHeight(4);
    // The user expects a rectangle of 5x4 = 20
    if (r.getArea() != 20) {
        std::cout << "LSP Violation! Expected area 20, got " << r.getArea() << "\n";
    } else {
        std::cout << "Rectangle logic implies area 20. Correct.\n";
    }
}

int main() {
    Rectangle rect;
    std::cout << "Testing Rectangle: ";
    processRectangle(rect);

    Square sq;
    std::cout << "Testing Square (as Rectangle): ";
    // This will fail logic, because setting height to 4 also changed width to 4 (area 16)
    processRectangle(sq); 

    return 0;
}
