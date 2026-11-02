# Temat 1 - podstawy i biblioteka standardowa

Temat obejmuje zajęcia 1 i 2: uruchamianie kompilatora oraz przykładowe elementy biblioteki standardowej
(napisy, kontenery, iteratory i algorytmy). Materiał jest podzielony na dwa tygodnie:

| Tydzień | Katalog | O czym |
| --- | --- | --- |
| 1 | [week-1/](week-1/) | Kompilator, wejście i wyjście, napisy, kontenery, strumienie, UTF-8. |
| 2 | [week-2/](week-2/) | Iteratory, algorytmy, wyszukiwanie binarne, scalanie, usuwanie elementów. |

W każdym katalogu jest `README.md` z objaśnieniami i oczekiwanymi wynikami oraz `Makefile`
(`make`, `make run`, `make clean`). Listę czytanek zbiera [czytanki.md](czytanki.md) (obowiązująca jest wersja z Moodle).

## Zagadnienia z opisu tematu

| Zagadnienie | Przykłady |
| --- | --- |
| uruchamianie kompilatora | [week-1/00-hello.cpp](week-1/00-hello.cpp) i sekcja 0 w README |
| napisy (`string`, `wstring`) | [week-1/02](week-1/02-string-basics.cpp), [03](week-1/03-string-params.cpp), [04](week-1/04-reserve.cpp), [09](week-1/09-utf8.cpp) |
| kontenery `pair`, `vector`, `list`, `map` | [week-1/05](week-1/05-sequences.cpp), [06](week-1/06-associative.cpp) |
| iteratory | [week-2/01](week-2/01-iterators.cpp) |
| `for_each` | [week-2/02](week-2/02-for-each-transform.cpp) |
| `copy` z `back_inserter` | [week-2/03](week-2/03-copy-inserters.cpp) |
| `lower_bound`, `upper_bound` | [week-2/05](week-2/05-bounds.cpp) |
| `inplace_merge` | [week-2/06](week-2/06-merge.cpp) |
| itd.: `sort`, `stable_sort`, erase-remove | [week-2/04](week-2/04-sort.cpp), [07](week-2/07-erase-remove.cpp) |

## Czytanki i przykłady

| Czytanka | Przykłady |
| --- | --- |
| Structure of a program, Basic Input/Output | [week-1/00](week-1/00-hello.cpp), [01](week-1/01-io.cpp) |
| `vector`, `pair`, `tuple`, `array` | [week-1/05](week-1/05-sequences.cpp) |
| `set`, `multiset`, `map`, `multimap` | [week-1/06](week-1/06-associative.cpp) |
| `unordered_set`, `unordered_multiset`, `unordered_map`, `unordered_multimap` | [week-1/07](week-1/07-unordered.cpp) |
| `string` | [week-1/02](week-1/02-string-basics.cpp), [03](week-1/03-string-params.cpp), [04](week-1/04-reserve.cpp), [09](week-1/09-utf8.cpp) |
| `stringstream`, `fstream` | [week-1/08](week-1/08-streams.cpp) (także [04](week-1/04-reserve.cpp), [06](week-1/06-associative.cpp)) |
| GOTW 54: vector i deque | [week-1/04](week-1/04-reserve.cpp), [05](week-1/05-sequences.cpp) |
| Koenig i Moo: algorytmy biblioteki | cały [week-2/](week-2/), szczególnie [02](week-2/02-for-each-transform.cpp) i [03](week-2/03-copy-inserters.cpp) |
| Lista algorytmów, `sort`, `stable_sort` | [week-2/04](week-2/04-sort.cpp) |
| `lower_bound`, `upper_bound` | [week-2/05](week-2/05-bounds.cpp) |
| Plauger: iteratory | [week-2/01](week-2/01-iterators.cpp) |
| Sutter, Item 2: What remove() Removes | [week-2/07](week-2/07-erase-remove.cpp) |
| `regex` (może się przydać) | [week-2/08](week-2/08-regex.cpp) |
| C++11, C++14, C++17 | zob. tabelę poniżej |

## Nowsze wersje języka w przykładach

Przykłady kompilują się w trybie C++20. Poniżej, co pochodzi z kolejnych wersji standardu.

| Wersja | Elementy użyte w przykładach |
| --- | --- |
| C++11 | `auto`, pętla `for (x : kontener)`, lista inicjalizacyjna, lambdy, `emplace_back`, `array`, `tuple`, kontenery `unordered_*`, `constexpr`, `u32string`, `regex`, literał surowy `R"(...)"`, `std::next`, `all_of`, `any_of`, `none_of`, `copy_if`, `minmax_element`, `shrink_to_fit` |
| C++14 | lambda z parametrem `auto` ([week-2/03](week-2/03-copy-inserters.cpp)) |
| C++17 | wiązania strukturalne, `std::string_view`, `std::filesystem`, zmienne `inline` ([alloc_counter.hpp](week-1/alloc_counter.hpp)), `is_same_v` |
| C++20 | `contains` w kontenerach asocjacyjnych, `std::erase_if` |

## Co nie jest tu omawiane

- `std::span` i `std::ranges` nie są częścią tego tematu.
- `flat_set`, `flat_map` i pokrewne (C++23) są wymienione w czytankach, ale według Moodle nie wszystkie są dostępne na `students`.
