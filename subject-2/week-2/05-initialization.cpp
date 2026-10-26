#include <iostream>

// constinit requires static initialization; it does not make counter const.
constinit int counter = 0;

#ifdef DEMO_BAD_CONSTINIT
int initial_value()
{
    return 42;
}

// A call to this non-constexpr function cannot be a constant initializer.
constinit int bad_counter = initial_value();
#endif

struct Registry {
    int count = 0;

    Registry()
    {
        std::cout << "Registry initialized\n";
    }
};

Registry& registry()
{
    // This object is initialized the first time execution reaches this line.
    // Later calls return a reference to the same object.
    static Registry instance;
    return instance;
}

int main()
{
    std::cout << "main started\n";
    ++counter;
    std::cout << "constinit counter: " << counter << '\n';

    Registry& first = registry();
    std::cout << "first count: " << ++first.count << '\n';

    Registry& second = registry();
    std::cout << "second count: " << ++second.count << '\n';

    std::cout << std::boolalpha;
    std::cout << "same object: " << (&first == &second) << '\n';
}
