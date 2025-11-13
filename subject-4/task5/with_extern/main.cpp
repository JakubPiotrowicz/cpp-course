#include "heavy_template.h"
#include "user1.h" // Include the header for our other user

int main() {
    HeavyTemplate<int> main_heavy;
    main_heavy.performAction("Action from Main");

    // Call the function from the other file
    runActionFromUser1();

    HeavyTemplate<double> main_heavy_double;

    return 0;
}
