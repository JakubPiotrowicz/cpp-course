// Pierwsza z dwóch jednostek. Zob. README, sekcja 3.
#include <iostream>

int compute() {
    std::cout << "first.cpp: liczę wartość\n";
    return 42;
}

int value = compute(); // Inicjowanie dynamiczne: wykona się przed main, ale nie wiadomo, czy przed second.cpp.
