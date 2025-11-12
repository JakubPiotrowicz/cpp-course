#include <iostream>
#include <vector>
#include <span>
#include <numeric>
#include <algorithm>
#include <ranges>

void normalize(std::span<double> data) {
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    if (sum == 0) return;
    std::ranges::transform(data, data.begin(), [sum](double x) { return x / sum; });
}

int main() {
    std::vector<double> v = {2.0, 3.0, 5.0};
    normalize(v);
    for (double x : v)
        std::cout << x << ' '; // 0.2 0.3 0.5
}
