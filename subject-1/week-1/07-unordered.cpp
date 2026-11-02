#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int main() {
    // unordered_set: zbiór z haszowaniem. Sprawdzenie i wstawienie są średnio w stałym czasie.
    const std::vector<std::string> words = {"ala", "ma", "kota", "ala", "kot", "ma"};
    std::unordered_set<std::string> seen;
    std::vector<std::string> repeated;
    for (const std::string& word : words) {
        if (!seen.insert(word).second) { // Drugi element pary mówi, czy coś dodano.
            repeated.push_back(word);
        }
    }
    std::cout << "różnych słów: " << seen.size() << ", powtórzone:";
    for (const std::string& word : repeated) {
        std::cout << ' ' << word;
    }
    std::cout << '\n';

    // unordered_multiset: dopuszcza powtórzenia.
    std::unordered_multiset<int> multiset = {1, 2, 2, 3, 3, 3};
    std::cout << "ile trójek: " << multiset.count(3) << ", elementów: " << multiset.size() << '\n';

    // unordered_map: klucz i wartość, bez porządku.
    std::unordered_map<std::string, int> ages = {{"Ala", 20}, {"Ola", 21}};
    ages["Ela"] = 22;
    std::cout << "Ela ma " << ages.at("Ela") << " lat, elementów: " << ages.size() << '\n';

    // unordered_multimap: jeden klucz może mieć kilka wartości.
    std::unordered_multimap<std::string, int> grades;
    grades.emplace("Ala", 5);
    grades.emplace("Ala", 3);
    grades.emplace("Ola", 4);
    std::cout << "ocen Ali: " << grades.count("Ala") << '\n';

    // Kolejność elementów jest nieokreślona i może się zmienić po dodaniu kolejnych,
    // więc przed wypisaniem kopiujemy wartości do wektora i sortujemy.
    std::vector<int> alas;
    auto [first, last] = grades.equal_range("Ala");
    for (auto it = first; it != last; ++it) {
        alas.push_back(it->second);
    }
    std::sort(alas.begin(), alas.end());
    std::cout << "oceny Ali po sortowaniu:";
    for (int grade : alas) {
        std::cout << ' ' << grade;
    }
    std::cout << '\n';

    // Tablica z haszowaniem ma kubełki. Współczynnik wypełnienia nie przekracza ustalonego limitu,
    // a po jego przekroczeniu kontener zwiększa liczbę kubełków i przemieszcza elementy.
    std::cout << std::boolalpha << "load_factor <= max_load_factor: " << (ages.load_factor() <= ages.max_load_factor())
              << '\n';
}
