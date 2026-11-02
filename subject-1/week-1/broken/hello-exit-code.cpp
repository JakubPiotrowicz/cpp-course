// Wariant celowo kończący się błędem: niezerowy kod wyjścia. Zob. README, sekcja 0.
// Uruchomienie: ./build/broken/hello-exit-code; echo $?
#include <iostream>

int main() {
    std::cout << "Coś poszło nie tak.\n";
    return 3; // Niezerowy kod wyjścia oznacza błąd.
}
