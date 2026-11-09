// Błąd kompilacji: nagłówek bez osłony włączony dwa razy. Zob. README, sekcja 1.
#include "point.hpp"
#include "point.hpp" // Błąd: redefinicja struct Point.

int main() {
    Point point{1, 2};
    return point.x - 1;
}
