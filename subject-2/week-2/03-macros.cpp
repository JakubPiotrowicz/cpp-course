#include <iostream>

// A macro is a sequence of tokens, not a typed variable.
#define SCALE 2 + 3

// A command-line definition, such as -DDEMO_VERBOSE=1, overrides this default.
#ifndef DEMO_VERBOSE
#define DEMO_VERBOSE 0
#endif

int main()
{
    const int scale = 2 + 3;
    constexpr int compile_time_scale = 2 + 3;

    // After preprocessing, this expression is: 4 * 2 + 3.
    std::cout << "macro: " << 4 * SCALE << '\n';
    std::cout << "const: " << 4 * scale << '\n';
    std::cout << "constexpr: " << 4 * compile_time_scale << '\n';

    // Parentheses fix this particular macro expression.
    std::cout << "parenthesized macro: " << 4 * (SCALE) << '\n';

    // The preprocessor selects which source lines reach the compiler.
#if DEMO_VERBOSE
    std::cout << "verbose mode is enabled\n";
#endif

    // This use requires a constant expression.
    static_assert(compile_time_scale == 5);
}
