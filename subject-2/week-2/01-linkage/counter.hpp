#ifndef COURSE_COUNTER_HPP
#define COURSE_COUNTER_HPP

namespace counter {

// Deklaracja zmiennej wspólnej dla wszystkich plików. Jedyna definicja jest w counter.cpp.
extern int shared_count;

void record_call();
int file_count();
int hidden_count();
int next_id();

} // namespace counter

#endif // COURSE_COUNTER_HPP
