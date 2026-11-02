// Błąd kompilacji: zmiana składowej w metodzie const i wywołanie metody bez const na obiekcie const.
// Zob. README, sekcja 5.
#include <string>

class Document {
public:
    void append(const std::string& text) {
        text_ += text;
    }

    void clear() const {
        text_.clear(); // Błąd 1: metoda const nie może zmieniać składowych.
    }

private:
    std::string text_;
};

int main() {
    const Document document;
    document.append("x"); // Błąd 2: append nie jest const, a obiekt jest.
}
