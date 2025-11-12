#include <iostream>
#include <ranges>
#include <numeric>
#include <vector>

int main() {
    std::cout << "Enter numbers (end with Ctrl+D on Linux/macOS or Ctrl+Z then Enter on Windows):\n";

    auto numbers = std::ranges::istream_view<int>(std::cin);

    auto v = std::ranges::to<std::vector>(numbers);

    if (v.empty()) {
        std::cout << "No numbers entered.\n";
        return 0;
    }
    
    std::vector<int> prefix(v.size());
    std::partial_sum(v.begin(), v.end(), prefix.begin());

    std::cout << "Prefix sums: ";
    for (int x : prefix)
        std::cout << x << ' ';
    std::cout << std::endl;
}
