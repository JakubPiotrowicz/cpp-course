#include <iostream>
#include <vector>
#include <string>

// Create a type alias for an integer vector.
// This is the modern equivalent of 'typedef std::vector<int> IntVector;'
using IntVector = std::vector<int>;

// Create an alias template for a vector of any type.
template<typename T>
using GenericVector = std::vector<T>;

int main() {
    IntVector numbers = {1, 2, 3, 4, 5};
    std::cout << "Numbers in IntVector: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    GenericVector<std::string> words = {"Hello", "World"};
    std::cout << "Words in GenericVector<string>: ";
    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;

    return 0;
}
