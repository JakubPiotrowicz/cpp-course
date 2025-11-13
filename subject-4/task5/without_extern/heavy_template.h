#ifndef HEAVY_TEMPLATE_H
#define HEAVY_TEMPLATE_H

#include <iostream>
#include <string>

template<typename T>
class HeavyTemplate {
public:
    void performAction(const std::string& actionName);
};

// Definition in the header
template<typename T>
void HeavyTemplate<T>::performAction(const std::string& actionName) {
    std::cout << "Action '" << actionName 
              << "' with type " << typeid(T).name() << std::endl;
}

// extern template class HeavyTemplate<int>;

#endif // HEAVY_TEMPLATE_H
