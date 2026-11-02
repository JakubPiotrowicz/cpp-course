#include <iomanip>
#include <iostream>
#include <string>

// Liczy punkty kodowe UTF-8: pomija bajty kontynuacji, które mają postać 10xxxxxx.
std::size_t count_code_points(const std::string& s) {
    std::size_t count = 0;
    for (unsigned char c : s) {
        if ((c & 0xC0) != 0x80) {
            ++count;
        }
    }
    return count;
}

int main() {
    // std::string przechowuje bajty. Plik źródłowy jest w UTF-8, więc ż, ó, ł i ć zajmują po dwa bajty.
    const std::string word = "zażółć";
    std::cout << word << ": size() = " << word.size() << " bajtów, ";
    std::cout << count_code_points(word) << " znaków\n";

    std::cout << "bajty:" << std::hex << std::setfill('0');
    for (unsigned char c : word) {
        std::cout << ' ' << std::setw(2) << static_cast<unsigned>(c);
    }
    std::cout << std::dec << '\n';

    // Indeks i substr działają na bajtach, więc trzy pierwsze bajty przecinają ż.
    std::cout << "substr(0, 3) kończy się w połowie znaku, więc nie jest poprawnym UTF-8\n";

    // wstring: elementem jest wchar_t. Jego rozmiar zależy od platformy: 4 bajty w Linuksie
    // (jeden element to jeden punkt kodowy), 2 bajty w Windows (UTF-16, część znaków zajmuje dwa elementy).
    const std::wstring wide_word = L"zażółć";
    std::cout << "wstring: size() = " << wide_word.size() << ", sizeof(wchar_t) = " << sizeof(wchar_t) << '\n';
    std::cout << "kod trzeciej litery (ż): U+" << std::hex << std::uppercase << std::setw(4)
              << static_cast<unsigned>(wide_word[2]) << std::dec << '\n';
    // Do wypisania wstring służy osobny strumień wcout. Nie wolno go mieszać z cout w jednym programie
    // bez dodatkowych ustawień, więc w przykładzie wypisujemy tylko rozmiary i kody.

    // u32string: zawsze jeden element na punkt kodowy (UTF-32).
    const std::u32string wide = U"zażółć";
    std::cout << "u32string: size() = " << wide.size() << '\n';
}
