#include <iostream>
#include <string>

// -- Method Template --
// The DataContainer class from the previous task, now with a focus on its method template.
template <typename T>
class DataContainer {
private:
    T value;

public:
    DataContainer(T val) : value(val) {}

    T getValue() const {
        return value;
    }

    // Method template: accepts any callable object (like a lambda or function pointer)
    // that can be invoked with the container's value.
    template <typename Func>
    auto applyFunction(Func f) const {
        std::cout << "Applying function to the value..." << std::endl;
        return f(value);
    }
};

// -- Variadic Function Template --
// Base case for recursion: a function that takes a single argument and returns it.
template<typename T>
T sum(T t) {
    return t;
}

// Recursive case: takes the first argument and adds it to the sum of the rest.
// The `...` syntax indicates a "parameter pack".
template<typename T, typename... Args>
auto sum(T first, Args... rest) {
    return first + sum(rest...);
}

int main() {
    // --- Method Template Demonstration ---
    DataContainer<int> intContainer(10);

    // Use a lambda function with the method template to double the value.
    auto doubledValue = intContainer.applyFunction([](int x) { return x * 2; });
    std::cout << "Result of lambda: " << doubledValue << std::endl;

    DataContainer<double> doubleContainer(5.5);

    // Use another lambda to square the value.
    auto squaredValue = doubleContainer.applyFunction([](double x) { return x * x; });
    std::cout << "Result of lambda: " << squaredValue << std::endl << std::endl;

    // --- Variadic Template Demonstration ---
    std::cout << "--- Variadic Sum ---" << std::endl;
    
    // Call sum() with integers.
    auto intSum = sum(1, 2, 3, 4, 5);
    std::cout << "Sum of integers: " << intSum << std::endl;

    // Call sum() with floating-point numbers.
    auto doubleSum = sum(1.1, 2.2, 3.3);
    std::cout << "Sum of doubles: " << doubleSum << std::endl;
    
    // Call sum() with mixed types (C++ will handle promotions).
    auto mixedSum = sum(1, 2.5, 3);
    std::cout << "Sum of mixed types: " << mixedSum << std::endl;

    return 0;
}
