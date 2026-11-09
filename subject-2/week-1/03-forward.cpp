// Deklaracje zapowiadające: nazwa typu lub funkcji znana przed pełną definicją.
#include <iostream>

struct Node; // Deklaracja zapowiadająca: typ niepełny.

struct Link {
    Node* target; // Wskaźnik do typu niepełnego jest dozwolony.
};

void print(const Node& node); // Referencja do typu niepełnego też, w samej deklaracji funkcji.

struct Node {
    int value;
    Link next;
};

void print(const Node& node) { // Definicja funkcji wymaga już pełnego typu.
    std::cout << "węzeł " << node.value << '\n';
}

// Funkcje wzajemnie rekurencyjne: pierwsza musi znać nazwę drugiej, więc jedna jest tylko zadeklarowana.
bool is_even(unsigned number);

bool is_odd(unsigned number) {
    return number != 0 && is_even(number - 1);
}

bool is_even(unsigned number) {
    return number == 0 || is_odd(number - 1);
}

int main() {
    Node last{2, Link{nullptr}};
    Node first{1, Link{&last}};
    print(first);
    print(*first.next.target);

    std::cout << "sizeof(Link) = " << sizeof(Link) << ", sizeof(Node) = " << sizeof(Node) << '\n';
    std::cout << std::boolalpha << "is_even(10): " << is_even(10) << ", is_odd(7): " << is_odd(7) << '\n';
}
