#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

namespace {

constexpr std::string_view vowels = "aeiouyAEIOUY";

std::string remove_vowels(std::string s) {
    // remove_if przesuwa elementy do zachowania na początek i zwraca iterator za nimi.
    // Rozmiar napisu się nie zmienia, zmienić go może tylko metoda kontenera.
    auto new_end = std::remove_if(s.begin(), s.end(), [](char c) { return vowels.find(c) != std::string_view::npos; });
    s.erase(new_end, s.end());
    return s;
}

} // Anonimowa przestrzeń nazw.

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6};

    auto new_end = std::remove_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
    std::cout << "size po remove_if: " << v.size() << ", elementów do zachowania: " << (new_end - v.begin()) << '\n';
    v.erase(new_end, v.end());
    std::cout << "size po erase: " << v.size() << '\n';

    // Od C++20 ten sam efekt daje jedna funkcja.
    std::vector<int> w = {1, 2, 3, 4, 5, 6};
    std::erase_if(w, [](int x) { return x % 2 == 0; });
    std::cout << "erase_if: ";
    for (int x : w) {
        std::cout << x << ' ';
    }
    std::cout << '\n';

    // Usuwanie duplikatów: unique usuwa tylko sąsiadujące powtórzenia, więc najpierw sortujemy.
    std::vector<int> d = {3, 1, 3, 2, 1, 3};
    std::sort(d.begin(), d.end());
    d.erase(std::unique(d.begin(), d.end()), d.end());
    std::cout << "unikalne: ";
    for (int x : d) {
        std::cout << x << ' ';
    }
    std::cout << '\n';

    std::cout << remove_vowels("This is an example sentence.") << '\n';
}
