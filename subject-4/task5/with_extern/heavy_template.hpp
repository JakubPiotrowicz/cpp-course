#ifndef HEAVY_TEMPLATE_H
#define HEAVY_TEMPLATE_H

#include <iostream>
#include <string>

template<typename T>
class HeavyTemplate {
public:
    void performAction(const std::string& actionName);
};

extern template class HeavyTemplate<int>;

#endif // HEAVY_TEMPLATE_H
