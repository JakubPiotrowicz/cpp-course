#include "counter.hpp"

#include <iostream>

// Te nazwy są takie same jak w counter.cpp, ale to zupełnie inne zmienne.
static int file_total = 0;

namespace {

int hidden_total = 0;

} // namespace

int main() {
    ++file_total;
    hidden_total += 3;
    counter::record_call();
    counter::record_call();
    counter::shared_count += 10; // Oba pliki działają na tym samym obiekcie.

    std::cout << "shared: " << counter::shared_count << '\n';
    std::cout << "file_total: main " << file_total << ", counter " << counter::file_count() << '\n';
    std::cout << "hidden_total: main " << hidden_total << ", counter " << counter::hidden_count() << '\n';
    std::cout << "ids: " << counter::next_id() << ' ' << counter::next_id() << '\n';
}
