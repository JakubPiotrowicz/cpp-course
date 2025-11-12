// Reference (&): An alias (another name) for an existing variable. It must be initialized at the moment of declaration and cannot be changed to refer to a different object.

// const: A keyword meaning "constant". const-correctness is the practice of using const to declare which data should not be modified.

// Passing by const T&: A very common idiom in C++. It allows you to avoid the expensive copy of an object while simultaneously guaranteeing that the function will not modify the object passed by reference.

// const member functions: A function marked const (after the argument list) promises that it will not change the logical state of the object. It can be called on const objects.

#include <iostream>
#include <string>

class MyData {
private:
    std::string data;

public:
    MyData(const std::string& s) : data(s) {}

    // A 'const' member function. It promises not to modify the object's state.
    void print() const {
        std::cout << "Data: " << data << std::endl;
        // data = "new value"; // ERROR: Cannot modify a member in a const function.
    }

    // A non-const member function. It can modify the object's state.
    void update(const std::string& newData) {
        data = newData;
    }
};

// This function takes a const reference to avoid a copy and guarantees no modification.
void displayData(const MyData& d) {
    std::cout << "Displaying data..." << std::endl;
    d.print();
    // d.update("attempted change"); // ERROR: Cannot call non-const member on a const reference.
}

int main() {
    MyData d1("Initial data");

    const MyData d2("Constant data");
    d2.print(); // OK: print() is a const member function.
    // d2.update("new"); // ERROR: Cannot call non-const member on a const object.

    displayData(d1); // Pass by const reference.

    return 0;
}
