#include "user1.hpp"
#include "heavy_template.hpp"

void runActionFromUser1() {
    HeavyTemplate<int> user1_heavy;
    user1_heavy.performAction("Action from User1");
}
