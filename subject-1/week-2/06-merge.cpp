#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <typename Iterator>
void merge_sort(Iterator first, Iterator last) {
    const auto size = std::distance(first, last);
    if (size < 2) {
        return;
    }
    Iterator middle = std::next(first, size / 2);
    merge_sort(first, middle);
    merge_sort(middle, last);
    // Obie połówki są już posortowane, więc wystarczy je scalić.
    std::inplace_merge(first, middle, last);
}

void print(const char* label, const std::vector<int>& v) {
    std::cout << label << ":";
    for (int x : v) {
        std::cout << ' ' << x;
    }
    std::cout << '\n';
}

int main() {
    // inplace_merge scala dwa sąsiednie posortowane zakresy w jeden, w tym samym kontenerze.
    std::vector<int> v = {1, 3, 5, 2, 4, 6};
    std::inplace_merge(v.begin(), v.begin() + 3, v.end());
    print("inplace_merge", v);

    // merge zapisuje wynik w osobnym miejscu. Zakresy wejściowe zostają bez zmian.
    const std::vector<int> a = {1, 4, 7};
    const std::vector<int> b = {2, 3, 8, 9};
    std::vector<int> merged;
    std::merge(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(merged));
    print("merge", merged);

    // Sortowanie przez scalanie zbudowane z inplace_merge.
    std::vector<int> unsorted = {8, 3, 5, 1, 9, 2, 7};
    merge_sort(unsorted.begin(), unsorted.end());
    print("merge_sort", unsorted);
}
