#include "api.h"

// Compile this translation unit as C.
// It exports the plain symbol name "triple" on the demonstrated toolchains.
int triple(int value)
{
    // The example uses small values that fit in int.
    return 3 * value;
}
