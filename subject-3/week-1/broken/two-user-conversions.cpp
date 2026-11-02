// Błąd kompilacji: dwie konwersje zdefiniowane przez użytkownika w jednym ciągu. Zob. README, sekcja 6.
#include <iostream>
#include <string>

class Name {
public:
    Name(const std::string& text) : text_(text) {}

    const std::string& text() const {
        return text_;
    }

private:
    std::string text_;
};

void greet(const Name& name) {
    std::cout << "Cześć, " << name.text() << "!\n";
}

int main() {
    // const char* -> std::string to jedna konwersja użytkownika, std::string -> Name druga.
    // Dozwolona jest tylko jedna. Poprawnie: greet(std::string("Ala")) albo greet(Name("Ala")).
    greet("Ala");
}
