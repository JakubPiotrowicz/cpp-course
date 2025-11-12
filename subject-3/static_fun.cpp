// **Static Members (`static`)**

// `static` members belong to the class itself, not to a specific object. There is only one copy of a static member, which is shared by all objects of the class.

// `static` member functions can be called without an object (`ClassName::function()`) and only have access to other static members.

#include <iostream>

class ObjectCounter {
private:
    // Static member variable to count the number of objects created.
    static int count;

public:
    // Constructor increments the count.
    ObjectCounter() {
        count++;
    }

    // Destructor decrements the count.
    ~ObjectCounter() {
        count--;
    }

    // Static member function to get the current count.
    static int getCount() {
        return count;
    }
};

// Definition and initialization of the static member variable.
// This must be in one .cpp file.
int ObjectCounter::count = 0;

int main() {
    std::cout << "Initial object count: " << ObjectCounter::getCount() << std::endl;

    ObjectCounter obj1;
    ObjectCounter obj2;

    std::cout << "Object count after creating two objects: " << ObjectCounter::getCount() << std::endl;

    {
        ObjectCounter obj3;
        std::cout << "Object count inside a new scope: " << ObjectCounter::getCount() << std::endl;
    } // obj3 is destroyed here

    std::cout << "Object count after the scope: " << ObjectCounter::getCount() << std::endl;

    return 0;
}
