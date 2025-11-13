#include <iostream>
#include <string>
#include <vector>

// -- Primary Class Template --
template <typename T>
class DataContainer {
private:
    T value;
public:
    DataContainer(T val) : value(val) {}
    void print() const {
        std::cout << "Generic container with value: " << value << std::endl;
    }
};

// -- Partial Specialization for pointers --
// This version of DataContainer will be used whenever T is a pointer type.
template <typename T>
class DataContainer<T*> {
private:
    T* value;
public:
    DataContainer(T* val) : value(val) {}
    void print() const {
        if (value) {
            std::cout << "Pointer container pointing to: " << *value << std::endl;
        } else {
            std::cout << "Pointer container is a nullptr." << std::endl;
        }
    }
};

// -- Auto, Decltype and Trailing Return Type --
// A function template that adds two different types.
// The return type is deduced from the result of `a + b`.
// `decltype(a + b)` determines the type of the expression `a + b`.
// The `->` syntax is the trailing return type.
template <typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}

int main() {
    // --- Partial Specialization Demonstration ---
    DataContainer<int> intContainer(42);
    intContainer.print();

    DataContainer<std::string> stringContainer("C++23");
    stringContainer.print();

    // The compiler will choose the partial specialization for T*
    int x = 100;
    DataContainer<int*> ptrContainer(&x);
    ptrContainer.print();

    DataContainer<int*> nullPtrContainer(nullptr);
    nullPtrContainer.print();
    std::cout << std::endl;

    // --- Auto and Decltype Demonstration ---
    std::cout << "--- Auto and Decltype ---" << std::endl;
    
    auto result1 = add(5, 3.14); // int + double
    std::cout << "add(5, 3.14) = " << result1 << " (type: " << typeid(result1).name() << ")" << std::endl;

    auto result2 = add(std::string("Hello, "), "World!"); // std::string + const char*
    std::cout << "add(\"Hello, \", \"World!\") = " << result2 << std::endl;

    return 0;
}
