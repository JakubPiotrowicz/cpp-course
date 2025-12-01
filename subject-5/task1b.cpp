// Comment exception throwing to see normal cleanup behavior.
// Use valgrind or similar tools to check for memory leaks.

#include <iostream>
#include <stdexcept>
#include <algorithm>

// A wrapper around a raw pointer (The "Old Way")
class LegacyBuffer {
public:
    // Constructor: Manual Allocation
    LegacyBuffer(size_t size) : size_(size) {
        std::cout << "Allocating " << size_ << " integers.\n";
        // allocating array, must use delete[] later
        data_ = new int[size_]; 
        
        // Initialize data
        std::fill(data_, data_ + size_, 0);
    }

    // Destructor: Manual Deallocation
    ~LegacyBuffer() {
        std::cout << "Releasing memory.\n";
        // CRITICAL: Must use delete[] for arrays, delete for single objects.
        delete[] data_; 
    }

    // Example of a raw pointer acting as an iterator
    int* begin() { return data_; }
    int* end() { return data_ + size_; }

    void risky_operation() {
        // Simulate an error.
        // If this throws, the destructor IS called if the object was fully constructed 
        // and lives on the stack. But... see Main.
        // throw std::runtime_error("Something went wrong during processing!");
    }

private:
    size_t size_;
    int* data_; // Owning pointer
};

void memory_leak_demonstration() {
    std::cout << "--- Part 1b: Raw Pointer Risks ---\n";
    
    // Scenario: We allocate a pointer to an object on the heap.
    LegacyBuffer* heapObj = new LegacyBuffer(10); // Pointer to Object

    try {
        heapObj->risky_operation();
        
        // If operation succeeds, we must manually delete.
        delete heapObj; 
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << "\n";
        // PROBLEM: 'delete heapObj' was skipped! Memory Leak!
        // We also leaked the internal 'data_' array inside LegacyBuffer.
        std::cout << "FATAL ERROR: 'heapObj' was never deleted. Memory leaked.\n";
    }
}

int main() {
    memory_leak_demonstration();
    return 0;
}
