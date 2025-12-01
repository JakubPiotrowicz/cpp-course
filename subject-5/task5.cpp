#include <iostream>
#include <string>
#include <string_view>

void process_string_copy(std::string s) {
    // Allocation happened to copy 's'
    std::cout << "Copy: " << s << "\n";
}

void process_string_view(std::string_view sv) {
    // No allocation. Just a pointer and size.
    std::cout << "View: " << sv << "\n";
}

int main() {
    std::cout << "\n--- Part 5: String View (Non-owning) ---\n";
    
    const char* raw_data = "Here is a very long string that we do not want to copy repeatedly.";

    // 1. Old C++ way (or naive way): Implicit conversion to std::string creates a copy (heap alloc)
    process_string_copy(raw_data); 

    // 2. Modern C++ way: View is just a window over the raw_data.
    // Zero allocations.
    process_string_view(raw_data);

    // Substring operations on views are O(1) and zero-alloc
    std::string_view sv = raw_data;
    auto sub = sv.substr(0, 10); 
    std::cout << "Substring view: " << sub << "\n";

    return 0;
}
