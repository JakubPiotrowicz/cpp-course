// main.cpp
import MathEngine; // Importujemy nasz moduł
import <iostream>; 

int main() {
    Calculator calc;
    
    std::cout << "5 + 3 = " << calc.add(5, 3) << "\n";
    std::cout << "5 - 3 = " << calc.subtract(5, 3) << "\n";

    // helper(5); // ERROR: 'helper' was not exported
    return 0;
}
