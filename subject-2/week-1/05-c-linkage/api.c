#include "api.h"

// Ta jednostka jest kompilowana jako C. Na tej platformie eksportuje symbol o nazwie "triple".
int triple(int value) {
    return 3 * value;
}
