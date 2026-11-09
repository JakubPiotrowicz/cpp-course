// Nagłówek wspólny dla C i C++. Kompilator C nie zna składni extern "C", więc osłaniamy ją
// makrem __cplusplus, które jest zdefiniowane tylko w C++.
#ifndef COURSE_TRIPLE_API_H
#define COURSE_TRIPLE_API_H

#ifdef __cplusplus
extern "C" {
#endif

int triple(int value);

#ifdef __cplusplus
}
#endif

#endif // COURSE_TRIPLE_API_H
