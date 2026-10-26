#include "counter.hpp"

// Internal linkage: this name refers to a variable private to this .cpp file.
static int file_count = 0;

namespace counter {

int shared_count = 0; // The single definition of the shared variable.

void record_call() {
    ++shared_count;
    ++file_count;
}

int private_count() {
    return file_count;
}

int next_id() {
    // Local scope, static storage duration: the value survives each call.
    static int last_id = 0;
    return ++last_id;
}

} // namespace counter
