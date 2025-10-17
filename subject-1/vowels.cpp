#include <string>
#include <iostream>
#include <algorithm>

namespace {
    std::string_view vowels = "aeiouyAEIOUY";
}

std::string remove_vowels(std::string s) {
    s.erase(std::remove_if(s.begin(), s.end(), [](char c) {
        return vowels.find(c) != std::string::npos;
    }), s.end());
    return s;
}
