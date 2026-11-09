// Błąd kompilacji: dwie dyrektywy using wprowadzają tę samą nazwę. Zob. README, sekcja 4.
#include <iostream>

namespace metric {

int step() {
    return 1;
}

} // namespace metric

namespace imperial {

int step() {
    return 3;
}

} // namespace imperial

int main() {
    using namespace metric;
    using namespace imperial;
    std::cout << metric::step() << '\n'; // Poprawnie: nazwa kwalifikowana.
    std::cout << step() << '\n'; // Błąd: step to metric::step albo imperial::step.
}
