// **Temporary Values (temporaries):** Objects created by the compiler during the evaluation of expressions. By default, they exist until the end of the full expression (until the semicolon).

// **Binding to `const T&`:** The lifetime of a temporary object can be extended to the lifetime of the reference if it is bound to a const reference (`const T&`). This is a very important feature of the language.

// **Local `static` variables:** A variable within a function declared as `static` is initialized only once - on the first call to the function. It retains its value between subsequent calls and exists until the end of the program.

#include <iostream>

class Tracer {
public:
    Tracer(const char* name) : name_(name) {
        std::cout << name_ << " created." << std::endl;
    }
    ~Tracer() {
        std::cout << name_ << " destroyed." << std::endl;
    }
private:
    const char* name_;
};

Tracer make_tracer(const char* name) {
    return Tracer(name);
}

void counter() {
    // This static variable is initialized only once.
    static int count = 0;
    count++;
    std::cout << "Counter function called " << count << " times." << std::endl;
}

int main() {
    std::cout << "--- Temporary lifetime ---\n";
    {
        std::cout << "Creating a temporary, its lifetime ends at the semicolon." << std::endl;
        make_tracer("Temporary");
        std::cout << "After the full expression." << std::endl;
    }

    Tracer&& ref2 = make_tracer("TemporaryRef");
    std::cout << "\n--- Extending lifetime with const& ---\n";
    {
        std::cout << "Binding temporary to a const reference." << std::endl;
        const Tracer& ref = make_tracer("Extended");
        ref2 = ref;
        std::cout << "Reference is in scope." << std::endl;
    } // 'Extended' is destroyed here, when the reference goes out of scope.

    std::cout << "\n--- Static local variable ---\n";
    counter();
    counter();
    counter();

    return 0;
}
