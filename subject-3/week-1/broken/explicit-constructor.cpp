// Błąd kompilacji: niejawna konwersja przez konstruktor explicit. Zob. README, sekcja 6.
class Seconds {
public:
    explicit Seconds(double value) : value_(value) {}

private:
    double value_;
};

void wait(Seconds) {}

int main() {
    Seconds ok(5);
    Seconds bad = 5; // Błąd: inicjowanie przez kopiowanie wymaga niejawnej konwersji.
    wait(10);        // Błąd: argument też wymagałby niejawnej konwersji.
    wait(ok);
}
