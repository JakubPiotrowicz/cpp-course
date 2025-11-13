#include "user1.h"
#include "heavy_template.h"

void runActionFromUser1() {
    HeavyTemplate<int> user1_heavy;
    user1_heavy.performAction("Action from User1");
}
