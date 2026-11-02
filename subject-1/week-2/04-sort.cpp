#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <string>
#include <vector>

struct Student {
    std::string name;
    int group;
};

void print(const std::vector<Student>& students) {
    for (const Student& s : students) {
        std::cout << "  grupa " << s.group << ": " << s.name << '\n';
    }
}

int main() {
    std::vector<int> v = {5, 2, 9, 1, 5, 6};
    std::sort(v.begin(), v.end());
    std::cout << "rosnąco:";
    for (int x : v) {
        std::cout << ' ' << x;
    }
    std::cout << '\n';

    // Własna kolejność: trzeci argument to porównanie "ma stać przed".
    std::sort(v.begin(), v.end(), std::greater<int>());
    std::cout << "malejąco:";
    for (int x : v) {
        std::cout << ' ' << x;
    }
    std::cout << '\n';

    std::vector<std::string> words = {"kot", "ananas", "pies", "mysz", "arbuz"};
    std::sort(words.begin(), words.end(), [](const std::string& a, const std::string& b) {
        return a.size() < b.size(); // Krótsze przed dłuższymi.
    });
    std::cout << "po długości:";
    for (const std::string& w : words) {
        std::cout << ' ' << w;
    }
    std::cout << '\n';
    // Porównanie musi być ścisłe: dla równych elementów zwraca false. Zapis a.size() <= b.size()
    // łamie wymaganie i sort może wyjść poza zakres albo się zawiesić.

    // sort nie gwarantuje zachowania kolejności równych elementów, stable_sort tak.
    const std::vector<Student> students = {{"Ola", 2}, {"Ala", 1}, {"Ela", 2}, {"Ewa", 1}, {"Ida", 2}};
    std::vector<Student> by_group = students;
    std::stable_sort(by_group.begin(), by_group.end(), [](const Student& a, const Student& b) {
        return a.group < b.group;
    });
    std::cout << "stable_sort po grupie (w grupie zostaje kolejność wejściowa):\n";
    print(by_group);

    std::cout << std::boolalpha << "is_sorted: " << std::is_sorted(by_group.begin(), by_group.end(),
        [](const Student& a, const Student& b) { return a.group < b.group; }) << '\n';

    // Lista nie ma iteratorów o dostępie swobodnym, więc ma własną metodę sort.
    std::list<int> l = {3, 1, 2};
    // std::sort(l.begin(), l.end()); // Błąd kompilacji.
    l.sort();
    std::cout << "list::sort:";
    for (int x : l) {
        std::cout << ' ' << x;
    }
    std::cout << '\n';
}
