#include <iostream>
#include <span>
#include <vector>
#include <ranges>
#include <algorithm>

int max_element(std::span<const int> data) {
    // Use ranges algorithm - no loops
    return std::ranges::max(data);
}

int main() {
    int arr[] = {1, 9, 3, 7, 5};
    std::vector<int> vec = {2, 8, 6, 4, 10};

    std::cout << max_element(arr) << '\n'; // 9
    std::cout << max_element(vec) << '\n'; // 10

    std::span<int> sp = vec;
    std::cout << max_element(sp.subspan(1, 3)) << '\n'; // 8
}
