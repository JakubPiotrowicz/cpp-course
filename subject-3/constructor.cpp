// Constructors and Destructor
// **Constructor:** A special member function automatically called when an object is created. It is used to initialize the object. It can be overloaded.

// **Member initializer list:** The preferred way to initialize class fields. It is more efficient than assigning values inside the constructor body and is required for `const` and reference members.

// **Default constructor:** A constructor that can be called without any arguments. If no constructor is defined, the compiler will generate one automatically.

// **Destructor (~ClassName):** Automatically called when an object is destroyed (e.g., when it goes out of scope). It is used to release resources (memory, files, etc.).

#include <iostream>
#include <string>

class Resource {
private:
    std::string name;

public:
    // Constructor with a member initializer list.
    Resource(const std::string& n) : name(n) {
        std::cout << "Resource '" << name << "' is being constructed." << std::endl;
    }

    // Destructor.
    ~Resource() {
        std::cout << "Resource '" << name << "' is being destructed." << std::endl;
    }

    void identify() const {
        std::cout << "This is resource '" << name << "'." << std::endl;
    }
};

int main() {
    std::cout << "Entering main function." << std::endl;
    {
        Resource localResource("Local"); // Object is created here.
        localResource.identify();
    } // localResource is destroyed here as it goes out of scope.
    std::cout << "Exiting main function." << std::endl;
    return 0;
}
