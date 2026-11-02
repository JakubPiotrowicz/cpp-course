// Pomocnik do przykładów: liczy alokacje pamięci na stercie.
//
// Zastępuje globalny operator new, więc ten plik wolno włączyć tylko do jednego
// pliku .cpp w programie. Funkcje zastępcze nie mogą być zdefiniowane dwa razy
// (podobnie jak zwykła funkcja z nagłówka, zob. temat 2).
#pragma once

#include <cstddef>
#include <cstdlib>
#include <new>

namespace alloc {

inline std::size_t counter = 0;

// Zwraca liczbę alokacji wykonanych podczas wywołania f.
template <typename F>
std::size_t count(F&& f) {
    const std::size_t before = counter;
    f();
    return counter - before;
}

} // Przestrzeń nazw alloc.

void* operator new(std::size_t size) {
    ++alloc::counter;
    if (void* p = std::malloc(size)) {
        return p;
    }
    throw std::bad_alloc{};
}

void operator delete(void* p) noexcept {
    std::free(p);
}

void operator delete(void* p, std::size_t) noexcept {
    std::free(p);
}
