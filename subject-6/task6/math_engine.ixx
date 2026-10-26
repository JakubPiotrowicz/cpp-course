// math_engine.ixx
export module MathEngine; // Definiujemy moduł

// Eksportujemy to, co ma być widoczne
export class Calculator {
public:
    Calculator();
    int add(int a, int b);
    int subtract(int a, int b);
};

// Funkcja pomocnicza, nie wyeksportowana (prywatna dla modułu)
int helper(int x) {
    return x * 2;
}
