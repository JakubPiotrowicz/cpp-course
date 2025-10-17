#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

int main() {
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {4, 5, 6};
    std::copy(a.begin(), a.end(), std::back_inserter(b));
    for (int x : b) {
        std::cout << x << " ";
    }
}
