// Wariant celowo błędny: copy do pustego wektora. Zob. README, sekcja 3.
// Kompilacja z AddressSanitizer: make broken (dodaje -g -fsanitize=address).
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    const std::vector<int> a = {1, 2, 3};

    // Błąd: pusty vector nie ma miejsca na trzy elementy. To zachowanie nieokreślone.
    // Rozwiązanie: std::back_inserter(empty) zamiast empty.begin().
    std::vector<int> empty;
    std::copy(a.begin(), a.end(), empty.begin());

    std::cout << "rozmiar po copy: " << empty.size() << '\n';
}
