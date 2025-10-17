#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {1, 3, 5, 2, 4, 6};
    std::inplace_merge(v.begin(), v.begin() + 3, v.end());
}
