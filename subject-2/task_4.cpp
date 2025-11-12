#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>

int main() {
    std::vector<int> v(50);
    std::ranges::iota(v, 1); // Fill 1..50

    auto filtered = v 
        | std::views::filter([](int x) { return x % 3 == 0 || x % 5 == 0; });

    // Copy filtered elements into a vector
    std::vector<int> result(filtered.begin(), filtered.end());
    std::ranges::sort(result, std::ranges::greater{});

    for (int x : result)
        std::cout << x << ' ';
}
