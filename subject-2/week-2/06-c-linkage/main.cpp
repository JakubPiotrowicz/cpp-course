#include "api.h"

#include <iostream>

int main()
{
    // The implementation is in a separately compiled C object file.
    std::cout << "triple(7) = " << triple(7) << '\n';

    // Define DEMO_CPP_LINKAGE to request a C++ symbol that api.c does not export.
    return 0;
}
