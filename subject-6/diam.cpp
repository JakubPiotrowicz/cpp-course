#include <iostream>

class A {
    virtual void foo() = 0;
    std::string name = "a";
public:
    virtual std::string getName() { return name; }
};

class B : public A {
    public:
    void foo() override {
        std::cout << "B::foo()\n";
    }
};

class C : public A {
    void foo() override {
        std::cout << "C::foo()\n";
    }
public:
    std::string name = "c";
// public:
//     virtual std::string getName() { return name; }
};

class D : public B, public C {
    public:
    std::string name = "d";
};

int main() {
    D d;

    // A* aPtr = &d; // Błąd: niejednoznaczne odniesienie do A

    B* bPtr = &d; // OK: D jest-a B
    C* cPtr = &d; // OK: D jest-a C

    A* aFromB = bPtr; // OK: B jest-a A
    A* aFromC = cPtr; // OK: C jest-a A

    static_cast<B&>(d).foo(); // OK, wywołuje B::foo()

    std::cout << d.C::getName() << "\n"; // Błąd: nie można uzyskać dostępu do getName() z A przez D

    std::cout << d.C::name << "\n"; // OK: dostęp do pola name z C przez D

    return 0;
}
