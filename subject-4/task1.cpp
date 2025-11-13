#include <iostream>
#include <vector>
#include <string>

// -- Class Template --
// A generic container to hold a value of any type T.
template <typename T>
class DataContainer {
private:
    T value;

public:
    // Constructor to initialize the value.
    DataContainer(T val) : value(val) {}

    // Method to get the stored value.
    T getValue() const {
        return value;
    }

    // A method template (szablon metody) to process data with a given function.
    // This will be explored more in the next task.
    template <typename Func>
    void process(Func f) {
        f(value);
    }
};

// -- Function Template --
// A generic function to print the value of any DataContainer.
template <typename T>
void printContainerValue(const DataContainer<T>& container) {
    std::cout << "Container holds: " << container.getValue() << std::endl;
}

int main() {
    // Instantiate DataContainer for an integer.
    DataContainer<int> intContainer(123);
    printContainerValue(intContainer);

    // Instantiate DataContainer for a string.
    DataContainer<std::string> stringContainer("Hello, Templates!");
    printContainerValue(stringContainer);

    // Instantiate DataContainer for a double.
    DataContainer<double> doubleContainer(3.14159);
    printContainerValue(doubleContainer);

    return 0;
}
