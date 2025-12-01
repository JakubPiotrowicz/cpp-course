#include <iostream>
#include <memory>
#include <string>

#include "task4.hpp"

// Definition of the incomplete type
struct API::Impl {
    std::string internal_state;
    
    void do_work() {
        std::cout << "Impl working with state: " << internal_state << "\n";
    }
};

// Constructor can call make_unique because Impl is now complete
API::API() : pImpl(std::make_unique<Impl>()) {
    pImpl->internal_state = "Hidden Data";
}

// CRITICAL: Destructor implementation must be here, 
// where API::Impl is a COMPLETE type.
// If we put ~API() {} in the header, compilation would fail or warn 
// about deleting incomplete type.
API::~API() = default; 

// Default move operations.
// These must be defined HERE, because replacing a unique_ptr 
// (which happens during assignment) requires destroying the old object.
// Destroying the old object requires Impl to be a complete type.
API::API(API&&) noexcept = default;

API& API::operator=(API&&) noexcept = default;

void API::execute() {
    pImpl->do_work();
}

int main() {
    std::cout << "\n--- Part 4: Pimpl Idiom ---\n";
    
    API api;
    api.execute();
    
    // Test move semantics
    API api2 = std::move(api);
    std::cout << "Moved API object.\n";
    api2.execute();

    return 0;
}
