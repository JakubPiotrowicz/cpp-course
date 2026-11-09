// Wynik zależy od kolejności łączenia plików. Zob. README, sekcja 3.
#include <iostream>

extern int value;

// Inicjowanie dynamiczne, które czyta zmienną z innego pliku. Standard nie określa kolejności inicjowania
// obiektów globalnych z różnych jednostek translacji. Przed inicjowaniem dynamicznym value ma wartość 0.
int copy_of_value = value;

int main() {
    std::cout << "value = " << value << ", copy_of_value = " << copy_of_value << '\n';
}
