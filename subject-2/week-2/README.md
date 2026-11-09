# Temat 2, tydzień 2 - powiązanie nazw, stałe, inicjowanie i przestrzenie nazw

Przegląd całego tematu i zestawienie z czytankami: [../README.md](../README.md).
Lista czytanek: [../czytanki.md](../czytanki.md). Tydzień 1 ([../week-1/](../week-1/)) dotyczy osobnej kompilacji,
preprocesora, przeciążania i łączenia z C.

## Uruchomienie

```bash
cd subject-2/week-2
make                 # buduje wszystkie przykłady
make run             # uruchamia je po kolei
```

Pliki wynikowe trafiają do ignorowanego przez Git katalogu `build/`, a `make clean` go usuwa.
Czytaj ten plik po kolei, a przy każdej sekcji zajrzyj do wskazanego pliku lub katalogu.
Katalog [broken/](broken/) zawiera programy, które mają się źle zachowywać (błędy kompilacji i inicjowania).
Buduje je osobno `make broken`, a tabela w sekcji 7 mówi, czego się spodziewać.
Wymagane: `g++` w wersji obsługującej C++20, GNU Make oraz `nm`. Przykłady nie czytają danych z klawiatury.

| Przykład | Pliki | Zagadnienie |
| --- | --- | --- |
| 1 | [01-linkage/](01-linkage/) | `extern`, `static` na poziomie pliku, przestrzeń anonimowa, `static` w funkcji. |
| 2 | [02-constants.cpp](02-constants.cpp) | `const`, `constexpr` i makra. |
| 3 | [03-initialization.cpp](03-initialization.cpp) | Kolejność inicjowania obiektów globalnych, `static` w funkcji, `constinit`. |
| 4 | [04-namespaces.cpp](04-namespaces.cpp) | Deklaracja i dyrektywa `using`, aliasy, ADL. |
| 5 | [05-if-constexpr.cpp](05-if-constexpr.cpp) | Instrukcja warunkowa wyliczana w czasie kompilacji. |
| 6 | [06-bitset.cpp](06-bitset.cpp) | `std::bitset` i uwaga o kontenerach `flat_*`. |

## 1. `extern`, `static` i powiązanie nazw

```bash
./build/01-linkage
```

```text
shared: 12
file_total: main 1, counter 2
hidden_total: main 3, counter 2
ids: 1 2
```

Przed uruchomieniem prześledź, ile razy zmienia się każda zmienna w `main.cpp` i `counter.cpp`.

- `extern int shared_count;` w [counter.hpp](01-linkage/counter.hpp) jest **deklaracją**. Jedyna **definicja**
  (`int shared_count = 0;`) jest w [counter.cpp](01-linkage/counter.cpp). Oba pliki działają na tym samym obiekcie,
  więc dwa wywołania `record_call()` i `+= 10` w `main` dają 12.
- `static int file_total` na poziomie pliku ma **powiązanie wewnętrzne**: nazwa jest widoczna tylko w tym pliku.
  Zmienne `file_total` w `main.cpp` i `counter.cpp` są dwiema różnymi zmiennymi. Bez `static` ta sama nazwa globalna
  zdefiniowana w dwóch plikach dałaby błąd łączenia.
- Przestrzeń anonimowa (`namespace { ... }`) daje ten sam skutek i w nowym kodzie jest zalecana zamiast `static`.
  Można to sprawdzić w tablicy symboli: `nm build/obj/01-linkage/counter.o`.

  ```text
  0000000000000004 b _ZL10file_total
  0000000000000008 b _ZN12_GLOBAL__N_112hidden_totalE
  0000000000000000 B _ZN7counter12shared_countE
  ```

  Wielka litera `B` oznacza symbol widoczny dla innych plików (`shared_count`), mała `b` symbol lokalny dla pliku.
- `static int last_id` **wewnątrz funkcji** to inna rola słowa `static`: zmienna ma zasięg lokalny, a czas życia
  statyczny. Nie znika po wyjściu z funkcji, dlatego kolejne wywołania `next_id()` dają 1 i 2.
  Do składowych statycznych klas wraca [temat 3](../../subject-3/week-2/README.md).
- `extern int shared_count = 0;` byłoby już definicją (bo ma inicjator). `extern` nie znaczy ,,bez definicji''.

## 2. `const`, `constexpr` i makra

```bash
./build/02-constants
```

```text
PI_MACRO = 3.14159, pi_const = 3.14159, geometry::pi = 3.14159
adres pi_const można wziąć: true

wewnątrz bloku: 5
na zewnątrz bloku: 3

computed_later = 5, known_early = 5
exported_limit = 9
```

- Makro to podmiana tekstu: nie ma typu, zasięgu ani adresu, a jego nazwa zastępuje **każde** wystąpienie
  w pliku, także nazwę pola struktury ([broken/macro-collision](broken/macro-collision/main.cpp)).
  Stała (`const`, `constexpr`) jest obiektem o typie i zasięgu: można ją przesłonić w bloku i wziąć jej adres.
  Do stałych liczbowych w C++ używamy `constexpr`, a nie `#define`.
- `const` zabrania modyfikacji, ale wartość początkowa może być obliczona dopiero w czasie działania
  (`computed_later`). `constexpr` wymaga wartości znanej w czasie kompilacji i zarazem oznacza `const`.
  Zwykłe `const int x = 2 + 3;` też bywa stałą w czasie kompilacji, ale to zależy od inicjatora, a nie od samego `const`.
- `const` na poziomie pliku ma **powiązanie wewnętrzne** (każdy plik ma własny egzemplarz), w przeciwieństwie do
  zwykłych zmiennych globalnych. Dopiero `extern const int exported_limit = 9;` daje powiązanie zewnętrzne:

  ```bash
  nm build/02-constants | grep -E "pi_const|exported_limit"
  ```

  ```text
  0000000000002018 R exported_limit
  0000000000002008 r _ZL8pi_const
  ```

  Zwykle nie piszemy tego ręcznie. Wspólną stałą w nagłówku definiuje się jako `inline constexpr`
  ([temat 3](../../subject-3/week-2/README.md), sekcja 2).

## 3. Inicjowanie obiektów globalnych

```bash
./build/03-initialization
```

```text
  konstruktor: globalny pierwszy
  konstruktor: globalny drugi
main się zaczyna
constinit counter: 1
pierwsze wywołanie registry():
  konstruktor Registry
drugie wywołanie registry():
count: 2, ten sam obiekt: true
main się kończy
  destruktor: globalny drugi
  destruktor: globalny pierwszy
```

- Obiekty globalne powstają **przed** `main`, w kolejności definicji w pliku, a niszczone są **po** zakończeniu `main`,
  w kolejności odwrotnej.
- Standard **nie określa** kolejności inicjowania obiektów globalnych z różnych plików. Jeśli konstruktor
  jednego obiektu używa obiektu zdefiniowanego w innym pliku, wynik zależy od kolejności łączenia
  (ang. static initialization order fiasco). Przykład w [broken/init-order](broken/init-order/second.cpp)
  buduje się bez błędu i działa:

  ```bash
  make broken
  ./build/broken/init-order
  ```

  ```text
  first.cpp: liczę wartość
  value = 42, copy_of_value = 42
  ```

  Po zmianie kolejności plików w poleceniu łączenia wynik jest inny, choć kod się nie zmienił:

  ```bash
  g++ -std=c++20 broken/init-order/second.cpp broken/init-order/first.cpp -o build/init-order-reversed
  ./build/init-order-reversed
  ```

  ```text
  first.cpp: liczę wartość
  value = 42, copy_of_value = 0
  ```

  Zmienna `value` przed inicjowaniem dynamicznym ma wartość 0 (obiekty statyczne są najpierw zerowane),
  więc `copy_of_value` kopiuje zero. Błąd jest groźny, bo wynik zależy od narzędzi, a nie od kodu. Dokładny wynik
  w drugim wariancie zależy od konsolidatora.
- Lekarstwo: **inicjowanie przy pierwszym użyciu**. Zmienna lokalna `static` w funkcji (`registry()`) jest inicjowana
  przy pierwszym przejściu przez deklarację. Każdy, kto potrzebuje obiektu, wywołuje funkcję, więc nigdy nie zobaczy go
  przed inicjowaniem. Konstruktor `Registry` wykonuje się raz, dopiero po `main się zaczyna`.
  Rozwiązanie nie usuwa cyklicznych zależności ani problemów z kolejnością niszczenia.
- `constinit` (C++20) wymaga, żeby zmienna była zainicjowana w czasie kompilacji (stałym inicjatorem).
  Taka zmienna nie bierze udziału w problemie kolejności, bo jest gotowa, zanim cokolwiek się wykona.
  `constinit` **nie oznacza niezmienności**, dlatego `++counter` działa. Inicjator, którego nie da się policzyć w czasie
  kompilacji, jest błędem ([broken/constinit-dynamic](broken/constinit-dynamic/main.cpp)).

## 4. Przestrzenie nazw

```bash
./build/04-namespaces
```

```text
metric::step: 1, imperial::step: 3
step: 1
step: 3
ct::version() = 7
okrąg o promieniu 4
```

- Nazwa kwalifikowana (`metric::step`) wskazuje przestrzeń jawnie.
- **Deklaracja** `using metric::step;` wprowadza jedną nazwę do bieżącego bloku.
- **Dyrektywa** `using namespace imperial;` udostępnia nazwy z przestrzeni przy wyszukiwaniu. Niczego nie kopiuje
  ani nie scala przestrzeni. Dwie dyrektywy z tą samą nazwą dają niejednoznaczne użycie tej nazwy
  ([broken/ambiguous-using](broken/ambiguous-using/main.cpp)). Wpisanie obu dyrektyw nie jest jeszcze błędem,
  błędem jest użycie nazwy bez kwalifikacji.
- Dyrektywy `using namespace` nie umieszczamy w nagłówkach ani na poziomie pliku w kodzie wielu autorów: wpływa na
  wyszukiwanie nazw we wszystkich plikach, które nagłówek włączą. W pliku `.cpp` lepsza jest deklaracja `using`
  dla pojedynczej nazwy albo nazwa kwalifikowana.
- Przestrzeń zagnieżdżoną można zapisać w jednym wierszu (`namespace company::tools`, C++17).
  Alias (`namespace ct = company::tools;`) skraca długie nazwy.
- **ADL** (wyszukiwanie zależne od argumentów): wywołanie `print(circle)` bez `shapes::` działa, bo kompilator szuka funkcji
  także w przestrzeni nazw typu argumentu. Dzięki temu działa na przykład `std::cout << x` dla typów
  z własnym `operator<<` zdefiniowanym obok typu. Zasady ADL i interfejs klasy omawia też temat 8 (rezerwa).
  O kwestiach interfejsu przestrzeni nazw mówią czytanki z listy.

## 5. `if constexpr`

```bash
./build/05-if-constexpr
```

```text
liczba całkowita 42
liczba zmiennoprzecinkowa 2.500000
napis tekst
wskaźnik ma 8 bajtów
```

- `if constexpr (warunek)` oblicza warunek w czasie kompilacji i **kompiluje tylko wybraną gałąź**. W szablonie
  druga gałąź dla danego typu w ogóle nie jest tworzona. Dlatego `std::string(value)` nie przeszkadza w wersji
  dla `int`. Zwykłe `if` sprawdza obie gałęzie i program się nie kompiluje
  ([broken/if-instead-of-if-constexpr](broken/if-instead-of-if-constexpr/main.cpp)).
- To bezpieczna alternatywa dla wyboru kodu przez `#if` (tydzień 1, sekcja 2): warunek używa typów i stałych C++, a nie
  podmiany tekstu. Poza szablonem `if constexpr` też działa, ale wtedy obie gałęzie muszą być poprawne.
- Szablony wyjaśnia temat 4. Tu wystarczy wiedzieć, że kompilator tworzy osobną wersję funkcji dla każdego użytego typu.
  Przy błędzie w szablonie komunikat jest długi: najważniejszy jest pierwszy, w którym jest ,,error''.

## 6. `std::bitset` i kontenery `flat_*`

```bash
./build/06-bitset
```

```text
flags = 00101010, ustawionych bitów: 3
test(3): true, test(4): false
po flip() = 11010101
z napisu: 00001011, z liczby: 00001010
and: 00001010, or: 00001011, xor: 00000001, << 2: 00101100
jako liczba: 11
uprawnienia (Execute, Write, Read): 101
```

- `std::bitset<N>` to zbiór `N` flag, których liczba jest znana w czasie kompilacji. Ma operacje bitowe (`&`, `|`, `^`, `~`,
  `<<`), `set`, `reset`, `flip`, `test`, `count` oraz konwersje z napisu i liczby. Bit o numerze 0 jest ostatni w zapisie.
- Czytanki wymieniają też kontenery `flat_set`, `flat_map`, `flat_multiset` i `flat_multimap` z C++23.
  Przechowują elementy w posortowanym wektorze: mniej pamięci i szybszy odczyt, ale wolniejsze wstawianie.
  W `g++` 13 nagłówków `<flat_set>` i `<flat_map>` nie ma ([broken/flat-set](broken/flat-set/main.cpp)),
  a według Moodle nie wszystkie są dostępne na `students`. Sprawdź `g++ --version` na swoim komputerze.
  Do pracy na zajęciach wystarczą `set` i `map` z tematu 1.

## 7. Celowo błędne warianty (`broken/`)

```bash
make broken
```

Polecenie kompiluje po kolei każdy podkatalog `broken/` jako osobny program. Błędy są tu oczekiwane,
więc `make` nie przerywa pracy. Programy, które się zbudują, trafiają do `build/broken/`.

| Katalog | Czego się spodziewać |
| --- | --- |
| [macro-collision](broken/macro-collision/main.cpp) | Błąd kompilacji: `expected unqualified-id before numeric constant`. |
| [constinit-dynamic](broken/constinit-dynamic/main.cpp) | Błąd kompilacji: `'constinit' variable 'counter' does not have a constant initializer`. |
| [init-order](broken/init-order/second.cpp) | Buduje się bez błędu. Wynik zależy od kolejności plików, patrz sekcja 3. |
| [ambiguous-using](broken/ambiguous-using/main.cpp) | Błąd kompilacji: `call of overloaded 'step()' is ambiguous`. |
| [if-instead-of-if-constexpr](broken/if-instead-of-if-constexpr/main.cpp) | Błąd kompilacji (długi, szablonowy): `no matching function for call to 'std::__cxx11::basic_string<char>::basic_string(const int&)'`. |
| [flat-set](broken/flat-set/main.cpp) | Błąd kompilacji: `flat_set: No such file or directory` (w `g++` 13). |

Uruchomienie wariantu, który się zbudował:

```bash
./build/broken/init-order
```

## Do omówienia na zajęciach

- Czym różni się `static` na poziomie pliku od `static` w funkcji? Co mają wspólnego?
- Po co deklaracja `extern` i dlaczego `extern int x = 0;` jest definicją?
- Dlaczego stała `const` w nagłówku nie powoduje błędu wielokrotnej definicji, a zwykła zmienna globalna tak?
- Co daje `constexpr` w porównaniu z `const` i z `#define`?
- W jakiej kolejności powstają i znikają obiekty globalne? Co jest niezdefiniowane dla obiektów z różnych plików?
- Dlaczego lokalna `static` rozwiązuje problem kolejności, a `constinit` go omija?
- Czym różni się deklaracja `using` od dyrektywy `using`? Dlaczego dyrektywa nie należy do nagłówków?
- Kiedy `if constexpr`, a kiedy `#if`?
