# Temat 3 - semantyka wartości

Temat obejmuje zajęcia 5 i 6: definiowanie własnych typów (klasy, enumy), cykl życia obiektu (tworzenie, kopiowanie,
przenoszenie, niszczenie) oraz zasady, które o tym decydują (`const`, referencje, konwersje, obiekty tymczasowe).
Materiał jest podzielony na dwa tygodnie:

| Tydzień | Katalog | O czym |
| --- | --- | --- |
| 1 | [week-1/](week-1/) | Wartości i referencje, klasy i enumy, konstruktory, inicjowanie, `const`, konwersje, obiekty tymczasowe, operatory i `<=>`. |
| 2 | [week-2/](week-2/) | Składowe statyczne, `using` i `inline`, kopiowanie, przenoszenie, operacje generowane przez kompilator, `constexpr`, rzutowania. |

W każdym katalogu jest `README.md` z objaśnieniami i oczekiwanymi wynikami, `Makefile`
(`make`, `make run`, `make broken`, `make clean`) oraz katalog `broken/` z celowo błędnymi programami.
Listę czytanek zbiera [czytanki.md](czytanki.md) (obowiązująca jest wersja z Moodle).

Większość przykładów używa klasy pomocniczej [noisy.hpp](noisy.hpp), która wypisuje komunikat przy każdym tworzeniu,
kopiowaniu, przenoszeniu i niszczeniu obiektu. Dzięki temu widać, co robi kompilator, bez debuggera.
Sposób czytania jej wyniku opisuje początek [week-1/README.md](week-1/README.md).

## Zagadnienia z opisu tematu

| Zagadnienie | Przykłady |
| --- | --- |
| `enum`, `enum class`, `using` | [week-1/02](week-1/02-class-and-enum.cpp), [week-2/02](week-2/02-using-and-inline.cpp) |
| klasy, interfejs publiczny i prywatny | [week-1/02](week-1/02-class-and-enum.cpp) |
| składowe statyczne | [week-2/01](week-2/01-static.cpp) |
| referencje | [week-1/01](week-1/01-value-vs-reference.cpp), [week-1/07](week-1/07-temporaries.cpp) |
| `const` | [week-1/05](week-1/05-const.cpp) |
| konstruktor jawny (`explicit`) | [week-1/06](week-1/06-conversions.cpp) |
| destruktor | [week-1/03](week-1/03-constructors.cpp) |
| konstruktor, inicjowanie składowych | [week-1/03](week-1/03-constructors.cpp), [04](week-1/04-initialization.cpp) |
| konstruktor domyślny | [week-1/03](week-1/03-constructors.cpp) |
| konstruktor kopiujący, operator przypisania | [week-2/03](week-2/03-copy.cpp) |
| konstruktor przenoszący | [week-2/04](week-2/04-move.cpp), [05](week-2/05-special-members.cpp) |
| konwersja przez konstruktor jednoargumentowy, operator konwersji, ciąg konwersji | [week-1/06](week-1/06-conversions.cpp) |
| czas życia i wiązanie wartości tymczasowych | [week-1/07](week-1/07-temporaries.cpp) |
| zmienne lokalne `static` i ich inicjowanie | [week-2/01](week-2/01-static.cpp) |

## Czytanki i przykłady

| Czytanka | Przykłady |
| --- | --- |
| Semantyka wartości a semantyka referencji (isocpp FAQ, napisy przez wartość lub referencję) | [week-1/01](week-1/01-value-vs-reference.cpp) |
| Klasy, podstawy (cplusplus.com, cprogramming.com) | [week-1/02](week-1/02-class-and-enum.cpp), [03](week-1/03-constructors.cpp) |
| Definiowanie operatorów | [week-1/08](week-1/08-operators.cpp) |
| Inicjowanie: zmienne, listy inicjujące, bezpośrednie i przez kopiowanie, konstruktory | [week-1/03](week-1/03-constructors.cpp), [04](week-1/04-initialization.cpp) |
| Const-correctness | [week-1/05](week-1/05-const.cpp) |
| Obiekty tymczasowe | [week-1/07](week-1/07-temporaries.cpp) |
| Operator `<=>` w C++20 | [week-1/08](week-1/08-operators.cpp) |
| `consteval` i `constinit` | [week-1/09](week-1/09-consteval-constinit.cpp) |
| `rational.cc` (Moodle) | zob. koniec [week-1/README.md](week-1/README.md) |
| `static` | [week-2/01](week-2/01-static.cpp) |
| `inline`, `typedef`, `using` | [week-2/02](week-2/02-using-and-inline.cpp) |
| Konstruktory kopiujące | [week-2/03](week-2/03-copy.cpp) |
| Semantyka r-wartości a przenoszenie | [week-2/04](week-2/04-move.cpp), [05](week-2/05-special-members.cpp) |
| Wyrażenia stałe (`constexpr`) | [week-2/06](week-2/06-constexpr-classes.cpp) |
| Dygresje: rzutowanie, typy całkowite o zadanej szerokości | [week-2/07](week-2/07-casts-and-integers.cpp) |
| Uzupełniające: `enum class`, kolejność konstruktorów, operatory | [week-1/02](week-1/02-class-and-enum.cpp), [03](week-1/03-constructors.cpp), [08](week-1/08-operators.cpp) |

## Nowsze wersje języka w przykładach

Przykłady kompilują się w trybie C++20. Poniżej, co pochodzi z kolejnych wersji standardu.

| Wersja | Elementy użyte w przykładach |
| --- | --- |
| C++11 | `enum class`, referencje do r-wartości i `std::move`, `= default` i `= delete`, `noexcept`, `constexpr`, listy inicjujące, `using` jako alias, `static_cast` i typy z `<cstdint>`, składowe z wartościami domyślnymi |
| C++14 | `constexpr` z pętlami i zmiennymi lokalnymi |
| C++17 | gwarantowane pominięcie kopii przy zwracaniu i inicjowaniu wartością tymczasową, zmienne `inline` (w tym `inline static`), `std::as_const`, `auto x{5}` jako `int` |
| C++20 | operator `<=>`, `consteval`, `constinit`, `using enum`, inicjowanie z nazwami pól (`{.x = 1}`), `std::cmp_less`, `std::is_constant_evaluated` |

## Co nie jest tu omawiane

- Wskaźniki, `new` i `delete`, `std::unique_ptr` oraz wyjątki w pełnym zakresie to temat 5.
  Klasy w przykładach przechowują napisy i wektory, które same dbają o pamięć (reguła zera).
- Szablony i ich specjalizacje to temat 4. Alias `using` jako szablon i kontenery generyczne pojawią się tam.
- Dziedziczenie i funkcje wirtualne to temat 6. Z tego powodu nie ma tu destruktorów wirtualnych.
- Operator przypisania w idiomie copy-and-swap (operator Suttera) jest w temacie 5, razem z odpornością na wyjątki.
