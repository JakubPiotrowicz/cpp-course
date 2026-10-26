#include <vector>
#include <algorithm>
#include <iostream>

int main() {
    std::vector<int> v = {1, 3, 5, 2, 4, 6};
    std::inplace_merge(v.begin(), v.begin() + 3, v.end());
    for (int i : v) {
        std::cout << i << " ";
    } 
}
