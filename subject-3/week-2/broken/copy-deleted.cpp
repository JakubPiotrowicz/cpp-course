// Błąd kompilacji: użycie usuniętego konstruktora kopiującego. Zob. README, sekcja 3.
class Token {
public:
    explicit Token(int value) : value_(value) {}
    Token(const Token&) = delete;
    Token& operator=(const Token&) = delete;

private:
    int value_;
};

void take(Token) {}

int main() {
    Token token(7);
    Token copy = token; // Błąd: kopiowanie jest usunięte.
    take(token); // Błąd: przekazanie przez wartość też wymaga kopii.
}
