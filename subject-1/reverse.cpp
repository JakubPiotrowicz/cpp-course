#include <iostream>
#include <vector>

template <typename Container>
void print_reverse(const Container& c) {
    for (auto it = c.rbegin(); it != c.rend(); ++it)
        std::cout << *it << " ";
}

int main() {
    std::string s = "Hello, World!";
    print_reverse(s); // ! dlroW ,olleH

    std::cout << std::endl;

    std::vector<int> v = {1, 2, 3, 4, 5};
    print_reverse(v); // 5 4 3 2 1

    return 0;
}
