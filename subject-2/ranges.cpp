#include <iostream>
#include <ranges>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6};

    // Create a view pipeline: take even numbers, square them
    auto view = v 
              | std::views::filter([](int x){ return x % 2 == 0; })
              | std::views::transform([](int x){ return x * x; });

    for (int x : view)
        std::cout << x << ' ';  // Output: 4 16 36
    std::cout << '\n';
}
