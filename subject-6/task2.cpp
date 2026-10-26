#include <iostream>
#include <vector>
#include <memory> // For std::unique_ptr

class Shape {
public:
    virtual ~Shape() = default; // Always virtual for base classes!

    // Pure virtual function - makes Shape an Abstract Class (Interface)
    virtual void draw() const = 0; 
    
    virtual double area() const { return 0.0; }
};

class Circle : public Shape {
public:
    Circle(double r) : radius(r) {}

    // 'override' ensures we are strictly overriding a base method
    void draw() const override {
        std::cout << "Drawing Circle (r=" << radius << ")\n";
    }

    double area() const override {
        return 3.14159 * radius * radius;
    }

private:
    double radius;
};

class Rectangle : public Shape {
public:
    Rectangle(double w, double h) : width(w), height(h) {}

    void draw() const override {
        std::cout << "Drawing Rectangle (" << width << "x" << height << ")\n";
    }

    double area() const override {
        return width * height;
    }

private:
    double width, height;
};

int main() {
    // Polymorphic container
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));

    std::cout << "--- Processing Shapes ---\n";
    for (const auto& shape : shapes) {
        // Dynamic binding happens here
        shape->draw(); 
        std::cout << "Area: " << shape->area() << "\n";
    }

    return 0;
}
