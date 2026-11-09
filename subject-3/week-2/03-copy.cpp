// Konstruktor kopiujący i operator przypisania kopiującego: kiedy się wykonują i co kopiują.
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "../noisy.hpp"

// Bez własnych operacji kopiujących kompilator kopiuje składowe po kolei.
class Bundle {
private:
    Noisy first_{"first"};
    Noisy second_{"second"};
};

// Własne operacje kopiujące: kopia dokumentu zaczyna własną historię zmian.
class Document {
public:
    explicit Document(std::string text) : text_(std::move(text)) {}

    // Parametr musi być referencją. Gdyby był wartością, jego utworzenie wymagałoby kopiowania, czyli rekurencji.
    Document(const Document& other) : text_(other.text_) {
        std::cout << "  Document: kopiowanie, historia kopii zaczyna się od zera\n";
    }

    Document& operator=(const Document& other) {
        if (this == &other) {
            std::cout << "  Document: przypisanie do samego siebie, nic do zrobienia\n";
            return *this;
        }
        std::cout << "  Document: przypisanie kopiujące\n";
        text_ = other.text_;
        ++revisions_;
        return *this;
    }

    int revisions() const {
        return revisions_;
    }

private:
    std::string text_;
    int revisions_ = 0;
};

// Klasa, której nie wolno kopiować (na przykład uchwyt do unikalnego zasobu).
class Token {
public:
    explicit Token(int value) : value_(value) {}
    Token(const Token&) = delete;
    Token& operator=(const Token&) = delete;

    int value() const {
        return value_;
    }

private:
    int value_;
};

static_assert(!std::is_copy_constructible_v<Token>);
static_assert(!std::is_copy_assignable_v<Token>);

void inspect(const Token& token) {
    std::cout << "  token " << token.value() << " oglądany przez referencję\n";
}

int main() {
    std::cout << "--- Kiedy powstaje kopia ---\n";
    Noisy original("original");
    std::cout << "Noisy copy = original (inicjowanie):\n";
    Noisy copy = original;
    Noisy other("other");
    std::cout << "other = original (przypisanie do istniejącego obiektu):\n";
    other = original;

    std::cout << "\n--- Kontener ---\n";
    std::vector<Noisy> items;
    items.reserve(1);
    std::cout << "push_back(original):\n";
    items.push_back(original);
    std::cout << "kopia całego kontenera:\n";
    std::vector<Noisy> duplicate = items;

    std::cout << "\n--- Kopiowanie generowane przez kompilator ---\n";
    Bundle bundle;
    std::cout << "Bundle copy_of_bundle = bundle:\n";
    Bundle copy_of_bundle = bundle;
    std::cout << "copy_of_bundle = bundle:\n";
    copy_of_bundle = bundle;

    std::cout << "\n--- Własne operacje kopiujące ---\n";
    Document first("pierwszy");
    Document second = first;
    second = first;
    second = second;
    std::cout << "historia: first = " << first.revisions() << ", second = " << second.revisions() << '\n';

    std::cout << "\n--- Klasa niekopiowalna ---\n";
    Token token(7);
    inspect(token);

    std::cout << "\n--- Koniec main, destruktory ---\n";
}
