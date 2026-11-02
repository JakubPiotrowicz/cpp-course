// Błędny wariant (copy do pustego wektora) jest w pliku broken/copy-to-empty.cpp.
#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <set>
#include <vector>

int main() {
    const std::vector<int> a = {1, 2, 3};

    // Algorytm copy sam nie zmienia rozmiaru kontenera. Zapisuje pod podany iterator,
    // więc docelowy zakres musi już istnieć.
    std::vector<int> ready(a.size());
    std::copy(a.begin(), a.end(), ready.begin());

    // back_inserter wywołuje push_back przy każdym zapisie, więc kontener rośnie sam.
    std::vector<int> b = {4, 5, 6};
    std::copy(a.begin(), a.end(), std::back_inserter(b));

    // front_inserter robi push_front. Elementy trafiają w odwrotnej kolejności.
    std::list<int> front = {0};
    std::copy(a.begin(), a.end(), std::front_inserter(front));

    // inserter wstawia w dowolne miejsce, także do zbioru, który ma własną kolejność.
    std::set<int> s = {2, 10};
    std::copy(a.begin(), a.end(), std::inserter(s, s.begin()));

    // copy_if kopiuje tylko elementy spełniające warunek.
    std::vector<int> odd;
    std::copy_if(b.begin(), b.end(), std::back_inserter(odd), [](int x) { return x % 2 == 1; });

    // ostream_iterator zapisuje do strumienia: wygodny sposób wypisania zakresu.
    auto print = [](const char* label, const auto& container) {
        std::cout << label << ": ";
        std::copy(container.begin(), container.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';
    };
    print("ready", ready);
    print("b", b);
    print("front", front);
    print("s", s);
    print("odd", odd);
}
