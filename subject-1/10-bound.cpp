#include <vector>
#include <algorithm>
#include <iostream>

int main() {
    std::vector<int> v = {1, 3, 3, 5, 7};
    auto it1 = std::lower_bound(v.begin(), v.end(), 3); // >= 3
    auto it2 = std::upper_bound(v.begin(), v.end(), 3); // > 3
    std::cout << (it2 - it1); // number of elements equal to 3
}
