// Single-argument constructor: If not marked as explicit, it defines an implicit conversion from the argument type to the class type.
// explicit: A keyword placed before a constructor to block implicit conversions. In that case, the object must be created explicitly.
// Conversion operator: Enables implicit conversion from a class type to another type (e.g., operator bool() const).

#include <iostream>

class MyNumber {
private:
    int value;

public:
    // This constructor allows implicit conversion from int.
    MyNumber(int v) : value(v) {
        std::cout << "Implicit constructor called with " << v << std::endl;
    }

    // Conversion operator to bool.
    explicit operator bool() const {
        return value != 0;
    }

    int get_value() const {
        return value;
    }
};

class ExplicitNumber {
private:
    int value;
    
public:
    // This constructor prevents implicit conversions.
    explicit ExplicitNumber(int v) : value(v) {
        std::cout << "Explicit constructor called with " << v << std::endl;
    }

    int get_value() const {
        return value;
    }
};

void process_number(MyNumber n) {
    std::cout << "process_number: " << n.get_value() << std::endl;
}

void process_explicit(ExplicitNumber en) {
    std::cout << "process_explicit: " << en.get_value() << std::endl;
}

int main() {
    MyNumber num1 = 42; // OK: Implicit conversion via constructor
    process_number(10); // OK: Implicit conversion for function argument

    // ExplicitNumber ex_num1 = 42; // ERROR: Constructor is explicit
    ExplicitNumber ex_num2(42);    // OK: Direct initialization
    // process_explicit(10);      // ERROR: No implicit conversion

    if (num1) { // OK: explicit operator bool() is used in contexts like if/while
        std::cout << "MyNumber is not zero." << std::endl;
    }
    
    return 0;
}
