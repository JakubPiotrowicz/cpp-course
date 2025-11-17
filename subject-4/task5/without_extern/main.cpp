#include "heavy_template.hpp"
#include "user1.hpp" // Include the header for our other user

int main() {
    HeavyTemplate<int> main_heavy;
    main_heavy.performAction("Action from Main");

    // Call the function from the other file
    runActionFromUser1();

    HeavyTemplate<double> main_heavy_double;

    return 0;
}
