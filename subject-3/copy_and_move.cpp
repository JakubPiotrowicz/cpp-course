// Copy and Move Semantics

// Copy Constructor (ClassName(const ClassName& other)):
// Creates a new object as a copy of an existing one. It is called,
// for example, when passing an object by value.

// Move Constructor (ClassName(ClassName&& other)):
// "Steals" resources from a temporary object (an r-value), leaving it in a "hollow" or empty state.
// Significantly more efficient than copying for objects that manage resources.

// Copy Assignment Operator (operator=(const ClassName& other)):
// Copies the contents of one object to another, already existing object.

// Move Assignment Operator (operator=(ClassName&& other)):
// Moves resources from a temporary object to an existing object.

#include <iostream>
#include <vector>
#include <string>
#include <utility>

class Buffer {
private:
    std::string name;
    std::vector<int> data;

public:
    // Constructor
    Buffer(const std::string& n) : name(n), data(1000, 0) {
        std::cout << "CONSTRUCT: " << name << std::endl;
    }

    // Copy Constructor
    Buffer(const Buffer& other) : name(other.name + "_copy"), data(other.data) {
        std::cout << "COPY CONSTRUCT: " << name << std::endl;
    }

    // Move Constructor
    Buffer(Buffer&& other) noexcept : name(std::move(other.name)), data(std::move(other.data)) {
        name += "_moved";
        std::cout << "MOVE CONSTRUCT: " << name << std::endl;
    }
    
    // Copy Assignment Operator
    Buffer& operator=(const Buffer& other) {
        name = other.name + "_assigned_copy";
        data = other.data;
        std::cout << "COPY ASSIGNMENT to " << name << std::endl;
        return *this;
    }

    // Move Assignment Operator
    Buffer& operator=(Buffer&& other) noexcept {
        name = std::move(other.name) + "_assigned_move";
        data = std::move(other.data);
        std::cout << "MOVE ASSIGNMENT to " << name << std::endl;
        return *this;
    }
};

Buffer createBuffer(const std::string& name) {
    return Buffer(name);
}

int main() {
    Buffer b1("b1"); // Construct
    Buffer b2 = b1;  // Copy construct
    
    std::cout << "\n--- Creating with move ---\n";
    Buffer b3 = createBuffer("temporary"); // Move construct (due to RVO/NRVO, may be optimized out)
                                           // But if not, move constructor is chosen.
    
    std::cout << "\n--- Assignment ---\n";
    Buffer b4("b4");
    b4 = b2;         // Copy assignment
    b4 = createBuffer("temp_assign"); // Move assignment

    return 0;
}
