// Ostrzeżenie -Wreorder: lista inicjująca w innej kolejności niż deklaracje składowych. Zob. README, sekcja 3.
#include <iostream>

class Range {
public:
    // Składowe powstają w kolejności deklaracji (first_, potem last_),
    // choć lista inicjująca sugeruje odwrotnie. first_ czyta last_, zanim ten dostanie wartość.
    Range(int length) : last_(length), first_(last_ - length) {}

    int first() const {
        return first_;
    }

    int last() const {
        return last_;
    }

private:
    int first_;
    int last_;
};

int main() {
    Range range(10);
    std::cout << "first = " << range.first() << ", last = " << range.last() << '\n';
}
