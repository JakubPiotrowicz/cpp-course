#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

template <typename Container>
void print(const std::string& label, const Container& c) {
    std::cout << label << ":";
    for (const auto& x : c) {
        std::cout << ' ' << x;
    }
    std::cout << '\n';
}

int main() {
    // vector: elementy leżą obok siebie, dostęp przez indeks jest szybki.
    std::vector<int> v = {3, 1, 4};
    v.push_back(1);
    v.emplace_back(5); // Konstruuje element w miejscu.
    print("v", v);
    std::cout << "size = " << v.size() << ", capacity >= size: " << (v.capacity() >= v.size()) << '\n';

    // Nawiasy okrągłe i klamrowe znaczą co innego.
    std::vector<int> five_ones(5, 1); // Pięć jedynek.
    std::vector<int> two_numbers{5, 1}; // Dwa elementy: 5 i 1.
    std::cout << "okrągłe: " << five_ones.size() << " elementów, klamrowe: " << two_numbers.size() << '\n';

    // Wstawianie i usuwanie w środku przesuwa elementy za miejscem zmiany.
    v.insert(v.begin() + 1, 9);
    v.erase(v.begin());
    v.pop_back();
    print("v po zmianach", v);

    // clear usuwa elementy, ale nie zwalnia zarezerwowanej pamięci. Prośbę o zwolnienie
    // składa shrink_to_fit (niewiążąca, ale w praktyce zwykle wykonywana).
    v.clear();
    std::cout << "po clear: size = " << v.size() << ", capacity > 0: " << (v.capacity() > 0) << '\n';
    v.shrink_to_fit();
    std::cout << "po shrink_to_fit: capacity = " << v.capacity() << '\n';

    // deque: kolejka dwustronna. Elementy leżą w osobnych blokach, więc wstawianie na początku
    // i na końcu jest szybkie, a dostęp przez indeks nadal działa. Nie ma capacity ani reserve.
    std::deque<int> d = {2, 3};
    d.push_front(1);
    d.push_back(4);
    print("d", d);
    std::cout << "d[2] = " << d[2] << '\n';

    // list: elementy są w osobnych węzłach, wstawianie i usuwanie nie przesuwa pozostałych.
    std::list<int> l = {1, 2, 3, 4, 5, 6};
    l.push_front(0);
    for (auto it = l.begin(); it != l.end();) {
        if (*it % 2 == 0) {
            it = l.erase(it); // Erase zwraca następny iterator.
        } else {
            ++it;
        }
    }
    print("l bez parzystych", l);

    // array: rozmiar znany w czasie kompilacji, brak alokacji na stercie.
    std::array<int, 3> a = {7, 8, 9};
    print("a", a);

    // pair: dwa elementy dowolnych typów.
    std::pair<std::string, int> p{"Ala", 3};
    std::cout << p.first << " ma " << p.second << '\n';
    std::cout << std::boolalpha << "pair(1, \"b\") < pair(1, \"c\"): "
              << (std::make_pair(1, std::string("b")) < std::make_pair(1, std::string("c"))) << '\n';

    // tuple: dowolna liczba elementów. Rozpakowujemy przez wiązania strukturalne.
    std::tuple<std::string, int, double> t{"Ola", 5, 1.5};
    auto [name, age, height] = t;
    std::cout << name << ", " << age << ", " << height << '\n';
    std::cout << "get<1>(t) = " << std::get<1>(t) << '\n';
}
