// Osłona chroni przed wielokrotnym włączeniem w jednej jednostce translacji,
// ale nie przed wystąpieniem tej samej definicji w dwóch różnych plikach .cpp.
#ifndef COURSE_UTIL_HPP
#define COURSE_UTIL_HPP

int bonus(int value) { // Definicja zwykłej funkcji w nagłówku. Poprawnie: deklaracja w .hpp, ciało w .cpp lub inline.
    return value + 1;
}

#endif // COURSE_UTIL_HPP
