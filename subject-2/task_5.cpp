#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <ranges>
#include <algorithm>

bool is_palindrome(std::string_view s) {
    return std::ranges::equal(s, s | std::views::reverse);
}

int main() {
    std::vector<std::string> words = {"level", "civic", "hello", "radar", "world"};

    auto palindromes = words
        | std::views::transform([](const std::string& s) { return std::string_view(s); })
        | std::views::filter(is_palindrome);

    for (auto w : palindromes)
        std::cout << w << ' ';
    // Output: level civic radar
}
