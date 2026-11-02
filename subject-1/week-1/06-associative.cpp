#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>

int main() {
    // map: pary klucz-wartość, uporządkowane po kluczu. Policzymy słowa.
    std::map<std::string, int> counts;
    std::istringstream text("ala ma kota a kot ma ale ala nie ma psa");
    std::string word;
    while (text >> word) {
        ++counts[word]; // Brakujący klucz jest dodawany z wartością 0.
    }
    for (const auto& [key, value] : counts) {
        std::cout << key << ": " << value << '\n';
    }

    // Odczyt przez [] też wstawia brakujący klucz, find i contains nie.
    std::cout << "rozmiar przed: " << counts.size() << '\n';
    if (!counts.contains("zebra")) { // contains od C++20.
        std::cout << "nie ma zebry\n";
    }
    auto it = counts.find("ala");
    if (it != counts.end()) {
        std::cout << "ala -> " << it->second << '\n';
    }
    std::cout << "counts[\"zebra\"] = " << counts["zebra"] << '\n';
    std::cout << "rozmiar po: " << counts.size() << '\n';

    // set: unikalne elementy po kolei. Insert mówi, czy coś dodał.
    std::set<int> s = {5, 1, 3};
    auto [position, inserted] = s.insert(3);
    std::cout << "wstawiono 3 ponownie: " << std::boolalpha << inserted << ", rozmiar " << s.size() << '\n';

    // multiset: dopuszcza powtórzenia.
    std::multiset<int> ms = {5, 1, 3, 3, 3};
    std::cout << "ile trójek: " << ms.count(3) << '\n';

    // Własna kolejność przez trzeci parametr szablonu.
    std::set<int, std::greater<int>> descending = {5, 1, 3};
    std::cout << "malejąco:";
    for (int x : descending) {
        std::cout << ' ' << x;
    }
    std::cout << '\n';

    // multimap: jeden klucz może mieć kilka wartości. Nie ma operatora [].
    // Wartości o równych kluczach zostają w kolejności wstawiania.
    std::multimap<std::string, std::string> phones;
    phones.emplace("Ala", "111");
    phones.emplace("Ala", "222");
    phones.emplace("Ola", "333");
    std::cout << "numerów Ali: " << phones.count("Ala") << ":";
    auto [first, last] = phones.equal_range("Ala"); // Zakres wszystkich wpisów o tym kluczu.
    for (auto range_it = first; range_it != last; ++range_it) {
        std::cout << ' ' << range_it->second;
    }
    std::cout << '\n';
}
