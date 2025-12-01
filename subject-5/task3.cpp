#include <iostream>
#include <utility> // for std::swap
#include <stdexcept>

class HeavyResource {
public:
    HeavyResource() { std::cout << "Resource acquired.\n"; }
    ~HeavyResource() { std::cout << "Resource released.\n"; }
};

class ResourceManager {
    HeavyResource* ptr; // Raw pointer to demonstrate manual safety logic

public:
    ResourceManager() : ptr(new HeavyResource()) {}

    // Destructor (No-throw guarantee standard)
    ~ResourceManager() noexcept {
        delete ptr;
    }

    // Copy Constructor
    // Can throw std::bad_alloc. If it throws, we haven't modified anything yet.
    ResourceManager(const ResourceManager& other) : ptr(new HeavyResource(*other.ptr)) {}

    // Move Constructor (C++11)
    // Should be noexcept to allow optimized vector reallocations
    ResourceManager(ResourceManager&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    // Custom swap function (No-throw)
    friend void swap(ResourceManager& first, ResourceManager& second) noexcept {
        // Swap primitive types (pointers)
        std::swap(first.ptr, second.ptr);
    }

    // ASSIGNMENT OPERATOR (Sutter's Idiom)
    // 1. We accept the argument by VALUE. This invokes the Copy Constructor (or Move Ctor).
    //    If Copy Ctor fails, exception happens BEFORE we enter the function. State is safe.
    // 2. We swap our content with the temporary copy.
    // 3. The temporary copy (containing our old data) is destroyed at function exit.
    ResourceManager& operator=(ResourceManager other) noexcept {
        std::cout << "Copy-and-swap assignment.\n";
        swap(*this, other);
        return *this;
    }
    
    // Catching exceptions: Best practice is by const reference
    void trigger_error() {
        throw std::logic_error("Simulated failure");
    }
};

int main() {
    std::cout << "\n--- Part 3: Exception Safety ---\n";
    try {
        ResourceManager a;
        ResourceManager b;
        
        std::cout << "Assigning b = a ...\n";
        b = a; // Uses copy-and-swap

        std::cout << "Attempting risky operation...\n";
        try {
            a.trigger_error();
        } catch (const std::exception& e) { // Catch by const ref!
            std::cout << "Caught safely: " << e.what() << "\n";
            // 'a' is still valid here (Strong Guarantee logic applied conceptually)
        }
    } catch (...) {
        // Catch-all handler
        std::cout << "Unknown error.\n";
    }
    return 0;
}
