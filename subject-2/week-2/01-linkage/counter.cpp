#include "counter.hpp"

// Powiązanie wewnętrzne: ta nazwa oznacza zmienną widoczną tylko w tym pliku.
static int file_total = 0;

namespace {

// Przestrzeń anonimowa daje ten sam skutek i w nowym kodzie jest zalecana zamiast static.
int hidden_total = 0;

} // namespace

namespace counter {

int shared_count = 0; // Jedyna definicja zmiennej wspólnej.

void record_call() {
    ++shared_count;
    ++file_total;
    ++hidden_total;
}

int file_count() {
    return file_total;
}

int hidden_count() {
    return hidden_total;
}

int next_id() {
    // Zasięg lokalny, ale czas życia statyczny: wartość przetrwa między wywołaniami.
    static int last_id = 0;
    return ++last_id;
}

} // namespace counter
