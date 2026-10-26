#include "counter.hpp"

#include <iostream>

// A different variable, despite having the same name as in counter.cpp.
static int file_count = 0;

int main() {
    ++file_count;
    counter::record_call();
    counter::record_call();
    counter::shared_count += 10; // Both files access the same shared object.

    std::cout << "shared: " << counter::shared_count << '\n';
    std::cout << "main private: " << file_count << '\n';
    std::cout << "counter private: " << counter::private_count() << '\n';
    std::cout << "ids: " << counter::next_id() << ' ' << counter::next_id() << '\n';
}
