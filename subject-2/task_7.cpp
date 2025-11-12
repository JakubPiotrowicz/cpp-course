#include <iostream>
#include <vector>
#include <mdspan>
#include <ranges>
#include <numeric>

int main() {
    constexpr int N = 4;
    std::vector<double> data(N * N);

    // Fill with numbers 1..16
    std::iota(data.begin(), data.end(), 1.0);

    std::mdspan<double, std::extents<size_t, N>> mat(data.data());

    // Extract diagonal using stride view
    auto diag = std::span<double>(data).subspan(0, N * N)
                | std::views::stride(N + 1);

    std::cout << "Diagonal elements: ";
    for (double d : diag)
        std::cout << d << ' ';
    // Output: 1 6 11 16
}

// Godbolt: https://godbolt.org/z/sxdj5qW1T
