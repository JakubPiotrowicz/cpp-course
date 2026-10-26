#ifndef WEEK2_COUNTER_HPP
#define WEEK2_COUNTER_HPP

namespace counter {

// A declaration of one shared variable, defined in counter.cpp.
extern int shared_count;

void record_call();
int private_count();
int next_id();

} // namespace counter

#endif // WEEK2_COUNTER_HPP
