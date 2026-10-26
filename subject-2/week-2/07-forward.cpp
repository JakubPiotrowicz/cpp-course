#include <iostream>

// A forward declaration introduces the type, but does not reveal its layout.
struct Node;

struct Link {
    Node* target; // A pointer does not need the complete definition of Node.
};

#ifdef DEMO_INCOMPLETE
// Intentional compiler error: a value member needs a complete type.
struct BrokenLink {
    Node target;
};
#endif

struct Node {
    int value;
};

int main() {
    Node node{42}; // The definition is visible here.
    Link link{&node};
    std::cout << link.target->value << '\n';
}
