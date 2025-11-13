#include <iostream>
#include <vector>
#include <list>

// This function template takes a container `C` and returns its first element.
// T is a dependent name; it depends on the template parameter C.
// The compiler doesn't know if `C::value_type` is a type or a static member variable.
// We must use `typename` to tell the compiler that `C::value_type` is a type.
template <typename C>
typename C::value_type getFirstElement(const C& container) {
    // Similarly, `C::const_iterator` is a dependent type name.
    // We need `typename` here as well.
    typename C::const_iterator it = container.begin();
    return *it;
}

int main() {
    std::vector<int> myVector = {10, 20, 30};
    std::cout << "First element of vector: " << getFirstElement(myVector) << std::endl;

    std::list<std::string> myList = {"alpha", "beta", "gamma"};
    std::cout << "First element of list: " << getFirstElement(myList) << std::endl;

    // Without `typename`, the code above would fail to compile with an error like:
    // error: need 'typename' before 'C::value_type' because 'C' is a dependent scope

    return 0;
}
