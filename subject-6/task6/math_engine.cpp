// math_engine.cpp
module MathEngine; // Implementujemy moduł

import <iostream>; // Import standard library (lub #include <iostream> w starszych kompilatorach)

import MathEngine; // Importujemy interfejs modułu

Calculator::Calculator() {
    std::cout << "Calculator Module Initialized\n";
}

int Calculator::add(int a, int b) {
    return a + b;
}

int Calculator::subtract(int a, int b) {
    return a - b;
}
