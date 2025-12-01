#include <iostream>
#include <memory> // For smart pointers
#include <vector>

// RAII compliant class
class SafeBuffer {
public:
    SafeBuffer(size_t size) {
        std::cout << "SafeBuffer constructed.\n";
        // vector manages memory automatically (RAII container)
        data_.resize(size, 0);
    }

    ~SafeBuffer() {
        // No explicit delete needed. Vector cleans itself up.
        std::cout << "SafeBuffer destroyed automatically.\n";
    }

private:
    std::vector<int> data_;
};

// Recursive structure using unique_ptr
struct Node {
    int value;
    // Owns the next node. When this node dies, the next dies.
    std::unique_ptr<Node> next; 

    Node(int v) : value(v), next(nullptr) {
        std::cout << "Node(" << value << ") created.\n";
    }

    ~Node() {
        std::cout << "Node(" << value << ") destroyed.\n";
    }
};

void raii_demonstration() {
    std::cout << "\n--- Part 2: RAII and Smart Pointers ---\n";

    try {
        // use make_unique (C++14/23 standard practice)
        auto safeObj = std::make_unique<SafeBuffer>(5);
        
        std::cout << "Doing work...\n";
        throw std::runtime_error("Error in RAII block");
    } catch (const std::exception& e) {
        std::cout << "Caught: " << e.what() << "\n";
        std::cout << "Notice: SafeBuffer destructor ran BEFORE this catch block entered (stack unwinding).\n";
    }

    std::cout << "\n--- Recursive Ownership ---\n";
    auto head = std::make_unique<Node>(1);
    head->next = std::make_unique<Node>(2);
    head->next->next = std::make_unique<Node>(3);
    
    std::cout << "Exiting scope... List will be destroyed head-to-tail.\n";
}

int main() {
    raii_demonstration();
    return 0;
}
