# Temat 3 - czytanki

Obowiązujący spis czytanek jest na stronie kursu w Moodle (zakładka ,,Czytanki'' przy Temacie 3).
Poniższa lista to kopia linków z 2 listopada 2026 (wersja z Moodle zmieniona ostatnio 30 października).
Jeśli Moodle się zmieni, wiążąca jest wersja z Moodle.

## Obowiązkowe na pierwszy tydzień

Semantyka wartości a semantyka referencji:

- <https://isocpp.org/wiki/faq/value-vs-ref-semantics>
- <http://stackoverflow.com/questions/1885785/passing-c-strings-by-value-or-by-reference>
- <http://www.cprogramming.com/c++11/rvalue-references-and-move-semantics-in-c++11.html>
  (bez akapitu bezpośrednio po śródtytule ,,Move constructors and implicitly generated constructors'')

Klasy, podstawy:

- <https://www.cplusplus.com/doc/tutorial/classes>
- <https://www.cplusplus.com/doc/tutorial/classes2>
- <https://www.cprogramming.com/tutorial/lesson12.html>
- Definiowanie operatorów: <http://users.cms.caltech.edu/~donnie/cs11/cpp/cpp-ops.html>

Klasy, zagadnienia bardziej zaawansowane:

- <http://gotw.ca/gotw/076.htm>

Inicjowanie:

- Zmienne: <http://www.gotw.ca/gotw/001.htm>
- Listy inicjujące: <https://isocpp.org/wiki/faq/cpp11-language#init-list>
- Bezpośrednie i przez kopiowanie: <http://www.gotw.ca/gotw/036.htm>
- Konstruktory: <https://isocpp.org/wiki/faq/ctors>

Const-correctness:

- <https://isocpp.org/wiki/faq/const-correctness>
- <http://www.gotw.ca/gotw/006.htm>
- <http://gotw.ca/gotw/081.htm>

Obiekty tymczasowe:

- <http://www.gotw.ca/gotw/002.htm>
- <http://herbsutter.wordpress.com/2008/01/01/gotw-88-a-candidate-for-the-most-important-const/>

Operator `<=>` w C++20:

- <https://en.cppreference.com/w/cpp/language/default_comparisons>

Inicjowanie w C++20 (`consteval` i `constinit`):

- <https://www.modernescpp.com/index.php/c-20-consteval-and-constinit>

Program `rational.cc` jest dostępny na stronie kursu w Moodle (zasób ,,Przykład'' w Temacie 3).

## Obowiązkowe na drugi tydzień

- `static`: <http://www.cprogramming.com/tutorial/statickeyword.html>
- `inline`: <https://en.cppreference.com/w/cpp/language/inline>
- `typedef`: <http://www.gotw.ca/gotw/046.htm>
- `using`: <https://en.cppreference.com/w/cpp/language/type_alias>
- Obiekty tymczasowe:
  <https://web.archive.org/web/20160709175149/http://www.informit.com/guides/content.aspx?g=cplusplus&seqNum=198>
- Semantyka r-wartości a semantyka przenoszenia:
  <http://www.cprogramming.com/c++11/rvalue-references-and-move-semantics-in-c++11.html>
- Wyrażenia stałe:
  <http://www.cprogramming.com/c++11/c++11-compile-time-processing-with-constexpr.html>
- Konstruktory kopiujące: <http://www.cplusplus.com/articles/y8hv0pDG/>

Dygresja o rzutowaniu:

- <https://stackoverflow.com/questions/103512/why-use-static-castintx-instead-of-intx>
- <https://stackoverflow.com/a/332086>

Dygresja o typach całkowitych o zadanej szerokości:

- <https://en.cppreference.com/w/cpp/types/integer>

## Uzupełniające

- Optymalizacja stałych: <http://www.gotw.ca/gotw/081.htm>
- Safe bool idiom (tylko po to, żeby zobaczyć, jak było przed C++11): <http://www.gotw.ca/gotw/079.htm>
- Pomoc przy definiowaniu operatorów, `boost/operators.hpp`:
  <http://www.boost.org/doc/libs/1_42_0/libs/utility/operators.htm>
- Typy wyliczeniowe `enum class`:
  <http://www.cprogramming.com/c++11/c++11-nullptr-strongly-typed-enum-class.html>
- Automatyczne ustalanie typu zwracanego z funkcji:
  <http://www.cprogramming.com/c++11/c++11-auto-decltype-return-value-after-function.html>
- Kolejność wywoływania konstruktorów:
  <http://www.cprogramming.com/tutorial/constructor_destructor_ordering.html>
- <http://stackoverflow.com/questions/2227244/what-if-a-constructor-parameter-has-the-same-name-as-a-member-variable-in-c>
- <http://en.cppreference.com/w/cpp/language/move_constructor>

## Która czytanka do którego tygodnia

| Tydzień | Katalog | Czytanki |
| --- | --- | --- |
| 1 | [week-1/](week-1/) | Wartości i referencje, klasy, inicjowanie, `const`, obiekty tymczasowe, operatory i `<=>`, `consteval`, `constinit`, `rational.cc`. |
| 2 | [week-2/](week-2/) | `static`, `inline`, `using`, przenoszenie, konstruktory kopiujące, `constexpr`, rzutowanie, typy całkowite. |

Szczegółowe zestawienie czytanek z plikami przykładów jest w [README.md](README.md).
