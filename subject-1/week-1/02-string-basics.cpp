#include <iostream>
#include <stdexcept>
#include <string>

int main() {
    std::string s = "abrakadabra";

    // Operator [] nie sprawdza zakresu, at() rzuca wyjątek.
    std::cout << "s[1] = " << s[1] << '\n';
    try {
        std::cout << s.at(20) << '\n';
    } catch (const std::out_of_range& e) {
        std::cout << "at(20) rzuciło wyjątek: " << e.what() << '\n';
    }

    // Wyszukiwanie zwraca indeks albo std::string::npos, gdy nic nie znaleziono.
    std::cout << "find(\"ra\") = " << s.find("ra") << '\n';
    std::cout << "rfind(\"ra\") = " << s.rfind("ra") << '\n';
    std::cout << "find_first_of(\"kd\") = " << s.find_first_of("kd") << '\n';
    std::cout << "find_last_of(\"kd\") = " << s.find_last_of("kd") << '\n';
    if (s.find("xyz") == std::string::npos) {
        std::cout << "find(\"xyz\") = npos\n";
    }

    // Porównania są leksykograficzne, bajt po bajcie (małe litery są po wielkich).
    std::cout << std::boolalpha;
    std::cout << "\"abc\" < \"abd\": " << (std::string("abc") < "abd") << '\n';
    std::cout << "\"ab\" < \"abc\": " << (std::string("ab") < "abc") << '\n';
    std::cout << "\"Z\" < \"a\": " << (std::string("Z") < "a") << '\n';
    std::cout << "s == \"abrakadabra\": " << (s == "abrakadabra") << '\n';

    // Operacje modyfikujące. Wszystkie działają w miejscu.
    std::string t = s.substr(3, 4); // Od indeksu 3, cztery znaki.
    t += "!";
    t.insert(0, ">>");
    t.replace(2, 2, "RA");
    std::cout << "t = " << t << '\n';
    t.erase(t.size() - 1);
    std::cout << "t = " << t << ", size = " << t.size() << '\n';

    // Dodawanie: jeden z argumentów musi być typu std::string.
    std::string u = "ab" + t + "cd";
    // std::string v = "ab" + "cd"; // Błąd kompilacji: dodawanie dwóch wskaźników.
    std::cout << "u = " << u << '\n';
}
