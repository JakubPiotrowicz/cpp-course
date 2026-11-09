# Temat 2 - kompilowanie, łączenie i przestrzenie nazw

Temat obejmuje zajęcia 3 i 4: jak z plików źródłowych powstaje program (osobna kompilacja, preprocesor, łączenie),
jak nazwy trafiają między pliki (deklaracje, definicje, powiązanie) oraz jak porządkować nazwy
(przestrzenie nazw) i inicjować obiekty globalne. Materiał jest podzielony na dwa tygodnie:

| Tydzień | Katalog | O czym |
| --- | --- | --- |
| 1 | [week-1/](week-1/) | Osobna kompilacja i łączenie, kompilowanie przyrostowe, preprocesor i osłony nagłówków, deklaracje zapowiadające, przeciążanie i kodowanie nazw, łączenie z C. |
| 2 | [week-2/](week-2/) | `extern` i `static`, `const` a `#define`, inicjowanie obiektów globalnych, deklaracja i dyrektywa `using`, `if constexpr`. |

W każdym katalogu jest `README.md` z objaśnieniami i oczekiwanymi wynikami, `Makefile`
(`make`, `make run`, `make broken`, `make clean`) oraz katalog `broken/` z celowo błędnymi programami.
Listę czytanek zbiera [czytanki.md](czytanki.md) (obowiązująca jest wersja z Moodle).

W przeciwieństwie do tematu 1 część przykładów składa się z kilku plików (katalogi `01-two-files/`, `05-c-linkage/`,
`01-linkage/`), bo osobnej kompilacji nie da się pokazać w jednym pliku. Każdy podkatalog w `broken/` to osobny program.

## Zagadnienia z opisu tematu

| Zagadnienie | Przykłady |
| --- | --- |
| rozłączne kompilowanie modułów, konsolidowanie | [week-1/01](week-1/01-two-files/) |
| kompilowanie przyrostowe | [week-1/01](week-1/01-two-files/) i `Makefile` |
| preprocesor | [week-1/02](week-1/02-preprocessor.cpp) |
| `#include` guards | [week-1/01](week-1/01-two-files/math.hpp), [broken/no-include-guard](week-1/broken/no-include-guard/) |
| deklaracje zapowiadające | [week-1/03](week-1/03-forward.cpp) |
| przeciążanie definicji funkcji i name mangling | [week-1/04](week-1/04-overloading.cpp) |
| łączenie z C (`extern "C"`) | [week-1/05](week-1/05-c-linkage/) |
| `extern`, `static` | [week-2/01](week-2/01-linkage/) |
| `const` a `define` | [week-2/02](week-2/02-constants.cpp) |
| inicjowanie obiektów globalnych | [week-2/03](week-2/03-initialization.cpp), [broken/init-order](week-2/broken/init-order/) |
| deklaracja `using` a dyrektywa `using` | [week-2/04](week-2/04-namespaces.cpp) |

## Czytanki i przykłady

| Czytanka | Przykłady |
| --- | --- |
| ,,One Program or Two?'' (DDJ) | [week-1/01](week-1/01-two-files/) |
| ,,Using #if for Portability'' (DDJ) | [week-1/02](week-1/02-preprocessor.cpp), [week-2/05](week-2/05-if-constexpr.cpp) |
| `if constexpr` | [week-2/05](week-2/05-if-constexpr.cpp) |
| Name mangling, łączenie C i C++ | [week-1/04](week-1/04-overloading.cpp), [05](week-1/05-c-linkage/) |
| Inicjowanie obiektów globalnych (isocpp FAQ, modernescpp) | [week-2/03](week-2/03-initialization.cpp) |
| Header guards (GOTW) | [week-1/01](week-1/01-two-files/) |
| Przestrzenie nazw, GOTW 30 | [week-2/04](week-2/04-namespaces.cpp) |
| `flat_set`, `flat_map`, `bitset` | [week-2/06](week-2/06-bitset.cpp) |

## Nowsze wersje języka w przykładach

Przykłady kompilują się w trybie C++20. Poniżej, co pochodzi z nowszych wersji standardu.

| Wersja | Elementy użyte w przykładach |
| --- | --- |
| C++11 | `constexpr`, `static_assert`, `nullptr`, `std::to_string` |
| C++14 | brak elementów specyficznych dla tej wersji |
| C++17 | `if constexpr`, zagnieżdżona przestrzeń nazw `a::b`, `std::is_integral_v` |
| C++20 | `constinit` |
| C++23 | `flat_set`, `flat_map` (niedostępne w `g++` 13, [week-2/broken/flat-set](week-2/broken/flat-set/)) |

## Co nie jest tu omawiane

- Moduły C++20 (`import`) to temat 6. Podział na nagłówki i pliki `.cpp` z tego tematu jest od nich niezależny.
- Funkcje `inline`, zmienne `inline` i składowe statyczne klas są w [temacie 3](../subject-3/README.md) (tydzień 2).
- Szablony (temat 4) pojawiają się tylko w jednym przykładzie, żeby pokazać `if constexpr`.
- Wyszukiwanie zależne od argumentów (ADL) pokazujemy na jednym przykładzie. Omawia je szerzej temat 8 (rezerwa).
- Osłony kompilatora (pimpl) i zależności kompilacji vs łączenia to temat 9 (rezerwa).
