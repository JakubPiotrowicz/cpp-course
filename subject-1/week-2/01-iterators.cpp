#include <forward_list>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <string>
#include <type_traits>
#include <vector>

// Ta sama funkcja działa dla każdego kontenera, który ma iteratory dwukierunkowe.
template <typename Container>
void print_reverse(const Container& c) {
    for (auto it = c.rbegin(); it != c.rend(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';
}

// Kategoria iteratora mówi, jakie operacje są dozwolone.
static_assert(std::is_same_v<std::iterator_traits<std::vector<int>::iterator>::iterator_category,
                             std::random_access_iterator_tag>);
static_assert(std::is_same_v<std::iterator_traits<std::list<int>::iterator>::iterator_category,
                             std::bidirectional_iterator_tag>);
static_assert(std::is_same_v<std::iterator_traits<std::forward_list<int>::iterator>::iterator_category,
                             std::forward_iterator_tag>);

int main() {
    std::vector<int> v = {10, 20, 30, 40, 50};

    // Zakres to para iteratorów [begin, end): end wskazuje za ostatni element.
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    print_reverse(v);
    print_reverse(std::string("Hello, World!"));
    print_reverse(std::list<int>{1, 2, 3});

    // Iterator stały nie pozwala zmieniać elementu.
    auto cit = v.cbegin();
    // *cit = 1; // Błąd kompilacji.
    std::cout << "*cit = " << *cit << '\n';

    // Iteratory o dostępie swobodnym pozwalają na arytmetykę. Dla pozostałych
    // służą funkcje next, prev, advance i distance (wolniejsze: krok po kroku).
    std::cout << "*(begin + 2) = " << *(v.begin() + 2) << '\n';
    std::cout << "distance = " << std::distance(v.begin(), v.end()) << '\n';
    std::list<int> l = {1, 2, 3, 4};
    std::cout << "*next(l.begin(), 2) = " << *std::next(l.begin(), 2) << '\n';
    // l.begin() + 2; // Błąd kompilacji: list nie ma iteratora o dostępie swobodnym.

    // Iteratory mapy wskazują na pary klucz-wartość.
    std::map<std::string, int> m = {{"a", 1}, {"b", 2}};
    for (auto it = m.begin(); it != m.end(); ++it) {
        std::cout << it->first << " -> " << it->second << '\n';
    }

    // Unieważnianie. Gdy vector zabraknie miejsca, przenosi elementy do nowej pamięci
    // i wszystkie iteratory z poprzedniej chwili przestają być ważne.
    const bool will_reallocate = v.size() == v.capacity();
    std::cout << "następny push_back zrobi realokację: " << std::boolalpha << will_reallocate << '\n';
    // Dla list usunięcie elementu unieważnia tylko iterator do niego.
    auto after = l.erase(l.begin());
    std::cout << "po erase pierwszy element to " << *after << '\n';
}
