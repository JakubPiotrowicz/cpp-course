#include <iostream>

class Base {
public:
    Base(int val) : baseVal(val) {}
    Base(const Base& other) : baseVal(other.baseVal) {
        std::cout << "Base copy ctor\n";
    }
    virtual ~Base() = default;
    
    virtual void identify() const { std::cout << "I am Base (" << baseVal << ")\n"; }

protected:
    int baseVal;
};

class Derived : public Base {
public:
    Derived(int bVal, int dVal) : Base(bVal), derivedVal(dVal) {}
    
    // Explicitly calling Base copy ctor
    Derived(const Derived& other) : Base(other), derivedVal(other.derivedVal) {
        std::cout << "Derived copy ctor\n";
    }

    void identify() const override { std::cout << "I am Derived (" << baseVal << ", " << derivedVal << ")\n"; }
    void specificAction() const { std::cout << "Derived specific action!\n"; }

private:
    int derivedVal;
};

void invokeSlicing(Base b) { // Pass by value causes slicing!
    std::cout << "Inside invokeSlicing: ";
    b.identify(); // Will call Base::identify(), not Derived::identify()
}

int main() {
    Derived d(10, 20);

    std::cout << "--- Slicing Demo ---\n";
    invokeSlicing(d); // Only Base part is copied

    std::cout << "\n--- Casting Demo ---\n";
    Base* ptr = &d;
    
    // Unsafe downcast (undefined behavior if ptr is not actually Derived*)
    // static_cast is faster but assumes you know what you are doing.
    Derived* staticD = static_cast<Derived*>(ptr);
    staticD->specificAction();

    // Safe downcast (Runtime check)
    if (Derived* dynamicD = dynamic_cast<Derived*>(ptr)) {
        std::cout << "Dynamic cast success.\n";
        dynamicD->specificAction();
    } else {
        std::cout << "Dynamic cast failed.\n";
    }

    Base otherBase(5);
    Base* otherPtr = &otherBase;
    
    // This will return nullptr
    if (dynamic_cast<Derived*>(otherPtr)) {
        std::cout << "This won't print.\n";
    } else {
        std::cout << "Dynamic cast correctly returned nullptr for pure Base object.\n";
    }

    return 0;
}
