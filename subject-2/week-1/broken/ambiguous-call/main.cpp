// Błąd kompilacji: wywołanie niejednoznaczne. Zob. README, sekcja 4.
#include <iostream>

void describe(int) {
    std::cout << "int\n";
}

void describe(long) {
    std::cout << "long\n";
}

void describe(double) {
    std::cout << "double\n";
}

int main() {
    describe(1);
    describe(3u); // Błąd: unsigned int przechodzi w int, long i double równie dobrze (każda to konwersja).
}
