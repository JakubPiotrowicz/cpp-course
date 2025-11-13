#include <iostream>

// Template metaprogramming is a technique where the compiler is used to
// execute code at compile time. This allows for optimizations and computations
// to be performed before the program even runs.

// Primary template for calculating factorial.
// This is a "recursive" template that defines Factorial<N> in terms of Factorial<N-1>.
// The calculation `N * Factorial<N - 1>::value` happens at compile time.
template<long long N>
struct Factorial {
    // `static const` or `static constexpr` makes `value` a compile-time constant.
    static_assert(N >= 0, "Factorial input cannot be negative");
    static constexpr long long value = N * Factorial<N - 1>::value;
};

// Template specialization to define the base case for the recursion.
// When the compiler encounters Factorial<0>, it will use this specialization
// instead of the primary template, thus stopping the recursion.
template<>
struct Factorial<0> {
    static constexpr long long value = 1;
};

int main() {
    // The value of `Factorial<5>::value` is computed entirely during compilation.
    // The compiled code will simply contain the final result, 120.
    long long fact5 = Factorial<5>::value;
    std::cout << "Factorial<5>::value = " << fact5 << std::endl;

    long long fact10 = Factorial<10>::value;
    std::cout << "Factorial<10>::value = " << fact10 << std::endl;
    
    // We can use static_assert to verify the compile-time computation.
    // If the condition is false, the code will fail to compile.
    static_assert(Factorial<7>::value == 5040, "Compile-time calculation is incorrect!");
    std::cout << "static_assert(Factorial<7>::value == 5040) passed at compile time." << std::endl;

    // The line below would cause a compilation error due to the static_assert
    // inside the primary template.
    // std::cout << Factorial<-1>::value << std::endl;

    return 0;
}
