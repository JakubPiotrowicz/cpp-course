#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

int main() {
    // Wyszukiwanie binarne działa tylko na zakresie posortowanym względem tego samego porównania.
    std::vector<int> v = {1, 3, 3, 3, 5, 7};

    auto first_not_less = std::lower_bound(v.begin(), v.end(), 3); // Pierwszy element >= 3.
    auto first_greater = std::upper_bound(v.begin(), v.end(), 3);  // Pierwszy element > 3.
    std::cout << "lower_bound(3) na pozycji " << (first_not_less - v.begin()) << '\n';
    std::cout << "upper_bound(3) na pozycji " << (first_greater - v.begin()) << '\n';
    std::cout << "trójek: " << (first_greater - first_not_less) << '\n';

    // equal_range zwraca obie granice naraz.
    auto [lo, hi] = std::equal_range(v.begin(), v.end(), 3);
    std::cout << "equal_range ma " << (hi - lo) << " elementy\n";

    // Brakująca wartość: obie granice wskazują to samo miejsce, w którym należałoby ją wstawić.
    auto place = std::lower_bound(v.begin(), v.end(), 4);
    std::cout << "4 należałoby wstawić na pozycji " << (place - v.begin()) << '\n';
    v.insert(place, 4);

    std::cout << std::boolalpha;
    std::cout << "binary_search(4): " << std::binary_search(v.begin(), v.end(), 4) << '\n';
    std::cout << "binary_search(6): " << std::binary_search(v.begin(), v.end(), 6) << '\n';

    // Zbiór ma własną metodę lower_bound, która korzysta z drzewa i działa w czasie O(log n).
    // Algorytm std::lower_bound dla zbioru też zadziała, ale przejdzie po elementach po kolei.
    std::set<int> s = {1, 3, 5, 7};
    auto member = s.lower_bound(4);
    std::cout << "set::lower_bound(4) = " << *member << '\n';
    auto generic = std::lower_bound(s.begin(), s.end(), 4);
    std::cout << "std::lower_bound(4) = " << *generic << '\n';
}
