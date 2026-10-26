#include <iostream>

namespace metric {
    int step = 1;
}

namespace imperial {
    int step = 3;
}

int main()
{
    // A qualified name says exactly which namespace we mean.
    std::cout << "metric::step: " << metric::step << '\n';
    std::cout << "imperial::step: " << imperial::step << '\n';

    {
        // A using-declaration introduces this one name into the block.
        using metric::step;
        std::cout << "using-declaration: " << step << '\n';
    }

    {
        // A using-directive makes namespace members available for lookup.
        using namespace metric;
        std::cout << "using-directive: " << step << '\n';

#ifdef DEMO_AMBIGUOUS
        // Both namespaces have step: lookup cannot choose between them.
        using namespace imperial;
        std::cout << "ambiguous: " << step << '\n';
#endif
    }

    // Both using statements were local to their own blocks.
    std::cout << "qualified again: " << metric::step << '\n';
}
