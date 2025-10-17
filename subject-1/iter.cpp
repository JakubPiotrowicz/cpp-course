#include <vector>
#include <algorithm>
#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::for_each(v.begin(), v.end(), [](int& x){ x *= 2; });
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        std::cout << *it << " "; // 10 8 6 4 2
    }
}
