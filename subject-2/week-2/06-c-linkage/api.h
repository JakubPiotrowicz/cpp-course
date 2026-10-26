#ifndef COURSE_TRIPLE_API_H
#define COURSE_TRIPLE_API_H

// A C compiler must not see C++ syntax.
#ifdef __cplusplus
#ifndef DEMO_CPP_LINKAGE
extern "C" {
#endif
#endif

// In C++, C language linkage keeps this declaration compatible with api.c.
int triple(int value);

#ifdef __cplusplus
#ifndef DEMO_CPP_LINKAGE
}
#endif
#endif

#endif
