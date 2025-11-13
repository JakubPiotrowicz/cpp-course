#include "heavy_template.h"

// The template's implementation
template<typename T>
void HeavyTemplate<T>::performAction(const std::string& actionName) {
    std::cout << "Action '" << actionName 
              << "' with type " << typeid(T).name() << std::endl;
}

// Explicit instantiation to generate the code for <int> here.
template class HeavyTemplate<int>;
