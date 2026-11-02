// Pierwszy program: budowa pliku, funkcja main i kod wyjścia.
// Warianty z ostrzeżeniami i niezerowym kodem wyjścia są w katalogu broken/.
#include <iostream> // Dyrektywa preprocesora: wstawia deklaracje strumieni (cout, cin, cerr).

// Funkcja musi być zadeklarowana przed użyciem. Tu deklaracja jest zarazem definicją.
int square(int x) {
    return x * x;
}

int main() {
    std::cout << "Witaj, świecie!\n";
    std::cout << "square(7) = " << square(7) << '\n';
    return 0; // Zero oznacza sukces. W main można pominąć ten wiersz.
}
