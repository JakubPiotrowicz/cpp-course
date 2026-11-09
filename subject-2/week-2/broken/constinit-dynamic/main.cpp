// Błąd kompilacji: constinit wymaga inicjatora stałego w czasie kompilacji. Zob. README, sekcja 3.
int initial_value() {
    return 42; // Zwykła funkcja: nie da się jej wykonać w czasie kompilacji.
}

constinit int counter = initial_value(); // Błąd. Bez constinit zmienna byłaby inicjowana dynamicznie.

int main() {
    return counter;
}
