// Które operacje specjalne kompilator generuje, a które nie, zależnie od tego, co zadeklarujemy sami.
// Każda klasa ma składową Noisy, więc widać, czy składowa jest kopiowana, czy przenoszona.
#include <iostream>
#include <type_traits>
#include <utility>

#include "../noisy.hpp"

// Reguła zera: niczego nie deklarujemy i dostajemy kopiowanie oraz przenoszenie.
struct RuleOfZero {
    Noisy member{"reguła zera"};
};

// Własny destruktor wyłącza generowanie operacji przenoszących. Przenoszenie zamienia się w kopiowanie.
struct WithDestructor {
    Noisy member{"destruktor"};

    ~WithDestructor() {}
};

// Własny konstruktor kopiujący też wyłącza generowanie operacji przenoszących.
struct WithCopyConstructor {
    Noisy member{"konstruktor kopiujący"};

    WithCopyConstructor() = default;
    WithCopyConstructor(const WithCopyConstructor&) = default;
};

// Własny konstruktor przenoszący usuwa operacje kopiujące.
struct WithMoveConstructor {
    Noisy member{"konstruktor przenoszący"};

    WithMoveConstructor() = default;
    WithMoveConstructor(WithMoveConstructor&&) = default;
};

static_assert(!std::is_copy_constructible_v<WithMoveConstructor>);
static_assert(!std::is_copy_assignable_v<WithMoveConstructor>);

// Własny konstruktor wyłącza generowanie konstruktora domyślnego.
struct NeedsArgument {
    explicit NeedsArgument(int) {}
};

static_assert(!std::is_default_constructible_v<NeedsArgument>);

int main() {
    std::cout << "--- RuleOfZero ---\n";
    RuleOfZero zero;
    std::cout << "kopiowanie:\n";
    RuleOfZero zero_copy = zero;
    std::cout << "przenoszenie:\n";
    RuleOfZero zero_moved = std::move(zero);

    std::cout << "\n--- WithDestructor ---\n";
    WithDestructor with_destructor;
    std::cout << "przenoszenie:\n";
    WithDestructor destructor_moved = std::move(with_destructor);

    std::cout << "\n--- WithCopyConstructor ---\n";
    WithCopyConstructor with_copy;
    std::cout << "przenoszenie:\n";
    WithCopyConstructor copy_moved = std::move(with_copy);

    std::cout << "\n--- WithMoveConstructor ---\n";
    WithMoveConstructor with_move;
    std::cout << "przenoszenie:\n";
    WithMoveConstructor move_moved = std::move(with_move);

    std::cout << "\n--- Koniec main, destruktory ---\n";
}
