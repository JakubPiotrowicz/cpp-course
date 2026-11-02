#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    // istringstream czyta z napisu tak jak cin z klawiatury.
    std::istringstream in("10 20 30 x40");
    int x = 0;
    int sum = 0;
    while (in >> x) { // Pętla kończy się na pierwszym tekście, który nie jest liczbą.
        sum += x;
    }
    std::cout << "suma = " << sum << ", strumień w stanie błędu: " << in.fail() << '\n';

    // ostringstream składa napis z różnych typów, z formatowaniem.
    std::ostringstream out;
    out << "pi = " << std::fixed << std::setprecision(3) << 3.14159265 << ", id = " << std::setw(5) << std::setfill('0')
        << 42;
    std::string message = out.str();
    std::cout << message << '\n';

    // fstream: najpierw zapis do pliku. Plik zamyka się w destruktorze.
    const std::string path = "08-streams.tmp";
    {
        std::ofstream file(path);
        file << "pierwszy wiersz\ndrugi wiersz\n";
    }

    // Potem odczyt wierszami.
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku " << path << '\n';
        return 1;
    }
    std::string line;
    int number = 1;
    while (std::getline(file, line)) {
        std::cout << number++ << ": " << line << '\n';
    }
    file.close();
    std::filesystem::remove(path);

    // Otwieranie nieistniejącego pliku nie rzuca wyjątku, trzeba sprawdzić stan.
    std::ifstream missing("nie-ma-takiego-pliku.txt");
    std::cout << "nieistniejący plik otwarty: " << std::boolalpha << missing.is_open() << '\n';
}
