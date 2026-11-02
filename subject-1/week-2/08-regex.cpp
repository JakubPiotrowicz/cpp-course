// Przykład dodatkowy: wyrażenia regularne (czytanka ,,może się przydać'').
#include <iostream>
#include <iterator>
#include <regex>
#include <string>

int main() {
    // Literał surowy R"(...)" nie wymaga podwajania ukośników. Wzorzec: data RRRR-MM-DD z grupami.
    const std::regex date(R"((\d{4})-(\d{2})-(\d{2}))");

    std::cout << std::boolalpha;
    // regex_match wymaga, żeby pasował cały napis.
    std::cout << "regex_match(\"2026-11-02\"): " << std::regex_match("2026-11-02", date) << '\n';
    std::cout << "regex_match(\"2026-11-02 r.\"): " << std::regex_match("2026-11-02 r.", date) << '\n';

    // regex_search szuka dopasowania w dowolnym miejscu. Wynik trafia do obiektu smatch,
    // który wskazuje na fragmenty napisu. Napis musi więc istnieć, dopóki używamy wyniku.
    const std::string text = "Termin: 2026-11-15, poprawka: 2026-12-20.";
    std::smatch match;
    if (std::regex_search(text, match, date)) {
        std::cout << "pierwsza data: " << match[0] << " (pozycja " << match.position(0) << "), rok " << match[1]
                  << '\n';
    }

    // sregex_iterator przechodzi po wszystkich dopasowaniach, jak zwykły iterator.
    std::cout << "wszystkie daty:";
    for (std::sregex_iterator it(text.begin(), text.end(), date), end; it != end; ++it) {
        std::cout << ' ' << (*it)[0];
    }
    std::cout << '\n';

    // regex_replace: odwołania $1, $2, $3 to grupy.
    std::cout << std::regex_replace(text, date, "$3.$2.$1") << '\n';
}
