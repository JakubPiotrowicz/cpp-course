#include <iostream>
#include <span>
#include <vector>

void printSpan(std::span<int> s) {
    // Access like a normal array
    for (int x : s)
        std::cout << x << ' ';
    std::cout << '\n';
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    std::vector<int> vec = {10, 20, 30, 40, 50};

    printSpan(arr);    // Works with raw arrays
    printSpan(vec);    // Works with std::vector

    // Create subspan (view of a fragment)
    std::span<int> sp = vec;
    printSpan(sp.subspan(1, 3)); // prints 20 30 40
}
