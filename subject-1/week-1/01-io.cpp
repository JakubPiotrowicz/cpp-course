#include <iostream>
#include <string>

int main() {
    std::cout << "cout: zwykłe wyjście.\n";
    // Strumień cerr jest osobny od cout: można go przekierować oddzielnie (2> plik).
    std::cerr << "cerr: komunikaty o błędach.\n";

    // Operator >> pomija białe znaki i czyta jedno słowo albo jedną liczbę.
    std::string name;
    int count = 0;
    std::cin >> name >> count;
    std::cout << "Imię: " << name << ", liczba: " << count << '\n';

    // Po >> w strumieniu zostaje znak nowego wiersza, więc getline zwraca resztę tego wiersza.
    std::string rest;
    std::getline(std::cin, rest);
    std::cout << "Reszta pierwszego wiersza: [" << rest << "]\n";

    // Wczytywanie wierszy aż do końca danych. Warunek pętli sprawdza stan strumienia.
    std::cout << "Kolejne wiersze:\n";
    std::string line;
    while (std::getline(std::cin, line)) {
        std::cout << "  [" << line << "]\n";
    }

    // Po końcu danych strumień jest w stanie błędu i kolejne odczyty nic nie zmienią.
    std::cout << "Po końcu danych: eof=" << std::cin.eof() << " fail=" << std::cin.fail() << '\n';
}
