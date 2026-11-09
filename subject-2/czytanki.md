# Temat 2 - czytanki

Obowiązujący spis czytanek jest na stronie kursu w Moodle (zakładka ,,Czytanki'' przy Temacie 2).
Poniższa lista to kopia linków z 2 listopada 2026 (wersja z Moodle zmieniona ostatnio 16 października).
Jeśli Moodle się zmieni, wiążąca jest wersja z Moodle.

## Obowiązkowe

Osobna kompilacja i preprocesor:

- Punkty ,,One Program or Two?'' oraz ,,Using #if for Portability'' w <http://www.ddj.com/cpp/184401419>,
  kopia: <http://web.archive.org/web/20091108031154/http://www.ddj.com/cpp/184401419>
- Header guards: <http://www.gotw.ca/gotw/032.htm>

Instrukcja warunkowa wyliczana w trakcie kompilowania:

- `if constexpr`: <https://en.cppreference.com/w/cpp/language/if>

Łączenie z C:

- Punkt ,,Handling of C symbols when linking from C++'' w <http://en.wikipedia.org/wiki/Name_mangling>
- Łączenie kodu C i C++: <https://isocpp.org/wiki/faq/mixing-c-and-cpp>

Inicjowanie obiektów globalnych:

- Punkty od <https://isocpp.org/wiki/faq/ctors#static-init-order>
  do <https://isocpp.org/wiki/faq/ctors#static-init-order-on-intrinsics>
- Przed C++20 i w C++20: <https://www.modernescpp.com/index.php/c-20-static-initialization-order-fiasco>

Przestrzenie nazw:

- <http://www.cprogramming.com/tutorial/namespaces.html>
- GOTW 30: <http://www.gotw.ca/gotw/030.htm>
- ,,Migrating to namespaces'': <http://www.gotw.ca/publications/migrating_to_namespaces.htm>
- ,,Namespaces and the Interface Principles'': <http://www.gotw.ca/publications/mill08.htm>

Nowe kontenery w C++23 (według Moodle nie wszystkie są dostępne na `students`):

- `flat_set`: <https://en.cppreference.com/w/cpp/container/flat_set.html>
- `flat_map`: <https://en.cppreference.com/w/cpp/container/flat_map.html>
- `flat_multiset`: <https://en.cppreference.com/w/cpp/container/flat_multiset.html>
- `flat_multimap`: <https://en.cppreference.com/w/cpp/container/flat_multimap.html>
- `bitset`: <https://en.cppreference.com/w/cpp/utility/bitset.html>

## Uzupełniające

- <http://www.gotw.ca/gotw/077.htm>
- Dobre praktyki pisania komentarzy: <https://stackoverflow.blog/2021/12/23/best-practices-for-writing-code-comments>
- `info gcc`, `info make`, `info cpp`, `info nm`

## Dla ciekawskich

- Inicjowanie standardowych strumieni wejścia-wyjścia: <http://www.cplusplus.com/reference/ios/ios_base/Init/>

## Która czytanka do którego tygodnia

| Tydzień | Katalog | Czytanki |
| --- | --- | --- |
| 1 | [week-1/](week-1/) | ,,One Program or Two?'', ,,Using #if for Portability'', header guards, name mangling, łączenie C i C++. |
| 2 | [week-2/](week-2/) | `if constexpr`, inicjowanie obiektów globalnych, przestrzenie nazw, `bitset` i kontenery `flat_*`. |

Szczegółowe zestawienie czytanek z plikami przykładów jest w [README.md](README.md).
