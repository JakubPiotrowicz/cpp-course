#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6};

    // Wyrażenie lambda to funkcja bez nazwy. Parametr przez referencję pozwala zmieniać elementy.
    std::for_each(v.begin(), v.end(), [](int& x) { x *= 2; });
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    // transform zapisuje wyniki w zakresie zaczynającym się od trzeciego argumentu.
    // Tutaj nadpisujemy te same elementy (wolno).
    std::transform(v.begin(), v.end(), v.begin(), [](int x) { return x + 1; });
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    // Lambda może używać zmiennych z otoczenia. [limit] kopiuje, [&limit] bierze referencję.
    const int limit = 7;
    std::cout << "większych od " << limit << ": " << std::count_if(v.begin(), v.end(), [limit](int x) { return x > limit; })
              << '\n';

    // find_if zwraca iterator. Trzeba sprawdzić, czy to nie end.
    auto it = std::find_if(v.begin(), v.end(), [](int x) { return x % 5 == 0; });
    if (it != v.end()) {
        std::cout << "pierwsza wielokrotność 5: " << *it << " na pozycji " << (it - v.begin()) << '\n';
    }

    std::cout << std::boolalpha;
    std::cout << "any_of parzyste: " << std::any_of(v.begin(), v.end(), [](int x) { return x % 2 == 0; }) << '\n';
    std::cout << "all_of dodatnie: " << std::all_of(v.begin(), v.end(), [](int x) { return x > 0; }) << '\n';
    std::cout << "none_of ujemne: " << std::none_of(v.begin(), v.end(), [](int x) { return x < 0; }) << '\n';

    // Algorytmy liczbowe są w <numeric>. Trzeci argument accumulate to wartość początkowa
    // i jej typ decyduje o typie wyniku.
    std::cout << "suma = " << std::accumulate(v.begin(), v.end(), 0) << '\n';
    std::cout << "suma jako double = " << std::accumulate(v.begin(), v.end(), 0.5) << '\n';

    // Wartości skrajne zwracają iteratory.
    auto [smallest, largest] = std::minmax_element(v.begin(), v.end());
    std::cout << "min = " << *smallest << ", max = " << *largest << '\n';

    // Te same algorytmy działają na napisach.
    std::string s = "Hello";
    std::for_each(s.begin(), s.end(), [](char& c) { c = static_cast<char>(c + 1); });
    std::cout << s << '\n';
}
