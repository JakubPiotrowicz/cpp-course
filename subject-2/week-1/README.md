# Temat 2, tydzień 1 - osobna kompilacja, preprocesor, przeciążanie i łączenie z C

Przegląd całego tematu i zestawienie z czytankami: [../README.md](../README.md).
Lista czytanek: [../czytanki.md](../czytanki.md). Tydzień 2 ([../week-2/](../week-2/)) dotyczy powiązania nazw,
stałych, inicjowania obiektów globalnych i przestrzeni nazw.

## Uruchomienie

Z głównego katalogu repozytorium przejdź do katalogu z przykładami:

```bash
cd subject-2/week-1
make                 # buduje wszystkie przykłady
make run             # uruchamia je po kolei
```

Wszystkie dalsze polecenia wykonuj z katalogu `week-1`.
Wymagane: `g++` w wersji obsługującej C++20, `gcc`, GNU Make oraz `nm` (do podglądu symboli).
Pliki wynikowe trafiają do ignorowanego przez Git katalogu `build/`, a `make clean` go usuwa.
Czytaj ten plik po kolei, a przy każdej sekcji zajrzyj do wskazanego pliku lub katalogu.
Katalog [broken/](broken/) zawiera programy, które mają się źle zachowywać (błędy kompilacji i łączenia).
Buduje je osobno `make broken`, a tabela w sekcji 6 mówi, czego się spodziewać.
Każdy podkatalog w `broken/` to osobny program.

| Przykład | Pliki | Zagadnienie |
| --- | --- | --- |
| 1 | [01-two-files/](01-two-files/) | Nagłówek i plik źródłowy, osobna kompilacja, łączenie, osłona nagłówka. |
| 2 | [02-preprocessor.cpp](02-preprocessor.cpp) | Makra, ich pułapki, `#if`, makra predefiniowane. |
| 3 | [03-forward.cpp](03-forward.cpp) | Deklaracje zapowiadające i typy niepełne. |
| 4 | [04-overloading.cpp](04-overloading.cpp) | Przeciążanie funkcji i kodowanie nazw. |
| 5 | [05-c-linkage/](05-c-linkage/) | Łączenie kodu C i C++ przez `extern "C"`. |

## 1. Dwa pliki źródłowe, kompilator i linker

```bash
./build/01-two-files
```

```text
5
4 6
```

Katalog `01-two-files` zawiera nagłówek [math.hpp](01-two-files/math.hpp) oraz dwa pliki źródłowe:

- Nagłówek opisuje typ `Point` i **deklaruje** funkcje. Samo `int add(int, int);` mówi, że funkcja istnieje,
  ale nie jest jej ciałem. **Definicja** (ciało) jest w `math.cpp`.
- Każdy plik `.cpp` razem ze wszystkim, co wciągnęły dyrektywy `#include`, tworzy osobną **jednostkę translacji**
  i jest kompilowany niezależnie od pozostałych. Kompilator widzi tylko deklaracje, więc `main.cpp` kompiluje się
  bez znajomości ciała funkcji.
- Kompilator wybiera przeciążenie po typach argumentów (`add(int, int)` albo `add(Point, Point)`).
  Sam typ wyniku nie wystarczy do odróżnienia funkcji.
- Ten podział na nagłówki i pliki źródłowe nie ma nic wspólnego z modułami C++20 (słowo `import`), które omawia temat 6.

### Osobne kompilowanie i łączenie

```bash
mkdir -p build/manual
g++ -std=c++20 -Wall -Wextra -Wpedantic -c 01-two-files/main.cpp -o build/manual/main.o
g++ -std=c++20 -Wall -Wextra -Wpedantic -c 01-two-files/math.cpp -o build/manual/math.o
g++ build/manual/main.o build/manual/math.o -o build/manual/demo
./build/manual/demo
```

`-c` zatrzymuje kompilator po utworzeniu pliku obiektowego `.o`. Plik obiektowy zawiera kod maszynowy własnych
funkcji i listę odwołań do cudzych symboli, więc nie jest jeszcze programem. Ostatnie polecenie `g++` uruchamia
**konsolidator** (linker): dopasowuje każde odwołanie do definicji i dołącza biblioteki C++.

Pominięcie `math.o` pokazuje różnicę między błędem kompilacji a błędem łączenia:

```bash
g++ build/manual/main.o -o build/manual/missing
```

```text
main.cpp:(.text+0x1a): undefined reference to `math::add(int, int)'
```

Kompilacja `main.cpp` się udała, a brakuje definicji dopiero przy łączeniu. To samo pokazuje
[broken/missing-definition](broken/missing-definition/main.cpp). Brzmienie komunikatów zależy od narzędzi.

### Kompilowanie przyrostowe

```bash
make clean           # Zaczynamy od czystego katalogu.
make build/01-two-files
make build/01-two-files
touch 01-two-files/math.cpp
make build/01-two-files
touch 01-two-files/math.hpp
make build/01-two-files
```

Pierwsze `make` kompiluje oba pliki i łączy program. Drugie mówi `up to date` i nic nie kompiluje. Po zmianie czasu modyfikacji `math.cpp` kompiluje się tylko ten
plik i program jest łączony od nowa. Po zmianie nagłówka kompilują się **oba** pliki, bo oba go włączają.
`touch` symuluje zapis pliku bez zmiany jego treści.

Skąd `make` wie o nagłówkach? Opcje `-MMD -MP` kompilatora zapisują zależności w plikach `.d`, które `Makefile` wczytuje:

```bash
cat build/obj/01-two-files/main.d
```

```text
build/obj/01-two-files/main.o: 01-two-files/main.cpp \
 01-two-files/math.hpp
01-two-files/math.hpp:
```

### Osłona nagłówka i wielokrotne definicje

W `main.cpp` nagłówek `math.hpp` jest włączony dwa razy. Osłona (`#ifndef` / `#define` / `#endif`) sprawia, że jego treść
trafia do jednostki translacji tylko raz. Bez niej dwa razy zdefiniowalibyśmy `struct Point`
([broken/no-include-guard](broken/no-include-guard/main.cpp)). Powtórzone zgodne **deklaracje** funkcji byłyby dozwolone,
ale powtórzonej **definicji** typu kompilator nie przyjmie.

Osłona działa w obrębie jednej jednostki translacji. Nie chroni przed tym, żeby zwykła funkcja zdefiniowana
w nagłówku trafiła do dwóch różnych plików `.cpp`: każdy jest kompilowany osobno. Wtedy konsolidator widzi dwie definicje tego
samego symbolu ([broken/header-definition](broken/header-definition/util.hpp)). Zasada: deklaracje w nagłówku, definicje
funkcji w jednym pliku `.cpp`. Wyjątkiem są funkcje `inline` (tydzień 2 tematu 3) i szablony.

Zamiast osłony `#ifndef` wiele kompilatorów rozumie `#pragma once`. To wygodne, ale niestandardowe,
dlatego kurs używa osłon.

## 2. Preprocesor

```bash
./build/02-preprocessor
```

```text
4 * SCALE = 11 (rozwija się do 4 * 2 + 3)
SQUARE(n + 1) = 7 (rozwija się do n + 1 * n + 1)
SQUARE_SAFE(n + 1) = 16
SQUARE_SAFE(n) + 1 = 10

MAX(i++, 2) = 6, i = 7
std::max(j++, 2) = 5, j = 6

__FILE__ = 02-preprocessor.cpp, __LINE__ = 35
__cplusplus = 202002
BUILD_NAME = domyślna

platforma: Linux
kompilacja w trybie C++20 lub nowszym
```

Przed uruchomieniem przewidź wartość `SQUARE(n + 1)` dla `n = 3`.

- Preprocesor działa **przed** kompilatorem i podmienia tekst. Nie zna typów ani zasięgów, dlatego `SCALE` rozwija się do
  `2 + 3`, a nie do `5`, i `4 * SCALE` daje 11. Nawiasy w definicji (`((x) * (x))`) naprawiają tę pułapkę.
- Argument makra funkcyjnego może zostać obliczony wiele razy. `MAX(i++, 2)` wykonuje `i++` dwukrotnie,
  a zwykła funkcja (`std::max`) tylko raz. W C++ do takich zadań służą funkcje i stałe.
- Operator `#` zamienia argument makra na napis z jego tekstem (makro `SHOW`).
- `__FILE__`, `__LINE__`, `__cplusplus` i `__linux__` są definiowane przez kompilator.
- `#if`, `#elif`, `#else`, `#endif` wybierają kod **przed kompilacją**. Gałąź, która nie wchodzi do programu,
  w ogóle nie jest przez kompilator widziana. Edytor (na przykład VS Code) pokazuje ją jako wyszarzoną. To nie
  jest błąd, tylko ta sama podmiana tekstu. Do wyboru kodu zależnego od typów w C++ lepsze jest `if constexpr` (tydzień 2).
- Makro `BUILD_NAME` ma wartość domyślną, którą można zmienić z wiersza poleceń:

  ```bash
  g++ -std=c++20 -DBUILD_NAME='"test"' 02-preprocessor.cpp -o build/preprocessor-test
  ./build/preprocessor-test
  ```

  Wiersz `BUILD_NAME = test` pokazuje, że `-D` zadziałało. Sam wynik preprocesora można obejrzeć poleceniem
  `g++ -std=c++20 -E 02-preprocessor.cpp`. Daje ono kilkadziesiąt tysięcy wierszy, bo `#include <iostream>`
  wstawia całą zawartość nagłówka. Po dodaniu `-P` łatwo znaleźć rozwinięte `4 * 2 + 3`.

## 3. Deklaracje zapowiadające i typy niepełne

```bash
./build/03-forward
```

```text
węzeł 1
węzeł 2
sizeof(Link) = 8, sizeof(Node) = 16
is_even(10): true, is_odd(7): true
```

- `struct Node;` to **deklaracja zapowiadająca**: kompilator zna nazwę, ale nie zna rozmiaru ani pól (typ niepełny).
  Typ niepełny wolno wskazać wskaźnikiem lub referencją i użyć w samej deklaracji funkcji.
  Nie wolno go użyć jako pola, utworzyć obiektu ani odczytać pola, bo do tego potrzebny jest rozmiar
  ([broken/incomplete-type](broken/incomplete-type/main.cpp)).
- Wskaźnik wystarcza do zbudowania listy: `Link` zawiera tylko adres `Node`, a `Node` zawiera `Link`.
  Rozmiar wskaźnika nie zależy od tego, na co wskazuje, więc `sizeof(Link)` jest znany wcześniej.
- Deklaracja funkcji bez ciała (`is_even`) pozwala na wzajemną rekurencję. Definicja funkcji, która używa pól `Node`,
  musi już stać po definicji `Node`.
- Zależności między nagłówkami warto zrywać deklaracjami zapowiadającymi zamiast kolejnych `#include`. Skraca to
  kompilację i pozwala uniknąć cyklicznych włączeń.

## 4. Przeciążanie funkcji i kodowanie nazw

```bash
./build/04-overloading
```

```text
describe(int)
describe(long)
describe(double)
describe(const char*)
describe(const std::string&)

describe(int)
describe(int)
describe(double)
```

- Kompilator wybiera wersję funkcji według typów argumentów w kolejności: **dokładne dopasowanie**, **promocja**
  (`char` i `short` na `int`, `float` na `double`), **konwersja standardowa**, **konwersja zdefiniowana przez użytkownika**.
  Dlatego `describe('a')` wybiera `int`, a nie `long` ani `double`.
- Jeśli kilka wersji pasuje równie dobrze (kilka konwersji tego samego rzędu), wywołanie jest niejednoznaczne
  i program się nie kompiluje ([broken/ambiguous-call](broken/ambiguous-call/main.cpp)).
- Typ wyniku nie bierze udziału w wyborze przeciążenia.
- Linker nie zna typów, więc kompilator zapisuje typy parametrów w nazwie symbolu (**name mangling**):

  ```bash
  nm build/04-overloading | grep describe
  ```

  ```text
  0000000000002300 T _Z8described
  00000000000022a9 T _Z8describei
  00000000000022d4 T _Z8describel
  000000000000232d T _Z8describePKc
  0000000000002359 T _Z8describeRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
  ```

  Końcówka nazwy koduje typ parametru: `i` to `int`, `l` to `long`, `d` to `double`, `PKc` to `const char*`.
  Adresy i dokładna postać nazw zależą od platformy i kompilatora. Polecenie `nm -C` odkodowuje nazwy
  do czytelnej postaci. Litera `T` oznacza definicję w sekcji kodu.
- Nazwy w przestrzeni nazw też są kodowane (`_ZN4math3addEii` to `math::add(int, int)`), co pozwala odróżnić
  `math::add` od `add`.

## 5. Łączenie kodu C i C++

```bash
./build/05-c-linkage
```

```text
triple(7) = 21
```

W [05-c-linkage/api.c](05-c-linkage/api.c) funkcja `triple` jest napisana w C, a [main.cpp](05-c-linkage/main.cpp)
wywołuje ją z C++. `Makefile` kompiluje plik `.c` przez `gcc`, a `.cpp` przez `g++`, a potem łączy
obiekty sterownikiem C++, który dołącza biblioteki C++.

Kompilator C nie koduje nazw, więc w pliku obiektowym C funkcja nazywa się po prostu `triple`.
Kompilator C++ bez dodatkowej informacji szukałby symbolu z zakodowanym typem parametru:

```bash
nm build/obj/05-c-linkage/api.o | grep triple
nm build/obj/05-c-linkage/main.o | grep triple
```

```text
0000000000000000 T triple
                 U triple
```

Litera `T` to definicja, a `U` to odwołanie czekające na definicję. Nazwy są takie same dzięki deklaracji
`extern "C"` w [api.h](05-c-linkage/api.h), która każe C++ używać powiązania języka C dla tej funkcji.
Nagłówek jest wspólny dla obu języków, więc `extern "C"` jest osłonięte makrem `__cplusplus`: kompilator C nie zna tej składni
i makro jest zdefiniowane tylko w C++.

Jeśli deklaracja w C++ pominie `extern "C"`, kompilacja się powiedzie, a łączenie nie
([broken/cpp-linkage-mismatch](broken/cpp-linkage-mismatch/main.cpp)): C++ żąda symbolu `triple(int)`
(w kodowaniu `_Z6triplei`), którego nikt nie eksportuje.
`extern "C"` nie tłumaczy kodu C++ na C. Każdy plik nadal kompiluje się we właściwym języku,
a deklaracja tylko uzgadnia sposób nazywania symbolu na styku.

## 6. Celowo błędne warianty (`broken/`)

```bash
make broken
```

Polecenie kompiluje po kolei każdy podkatalog `broken/` jako osobny program. Błędy są tu oczekiwane,
więc `make` nie przerywa pracy. Programy, które się zbudują, trafiają do `build/broken/`.

| Katalog | Czego się spodziewać |
| --- | --- |
| [missing-definition](broken/missing-definition/main.cpp) | Błąd łączenia: `undefined reference to 'add(int, int)'`. |
| [no-include-guard](broken/no-include-guard/main.cpp) | Błąd kompilacji: `redefinition of 'struct Point'`. |
| [header-definition](broken/header-definition/util.hpp) | Błąd łączenia: `multiple definition of 'bonus(int)'`. |
| [incomplete-type](broken/incomplete-type/main.cpp) | Błąd kompilacji: `field 'target' has incomplete type 'Node'`. |
| [ambiguous-call](broken/ambiguous-call/main.cpp) | Błąd kompilacji: `call of overloaded 'describe(unsigned int)' is ambiguous`. |
| [cpp-linkage-mismatch](broken/cpp-linkage-mismatch/main.cpp) | Błąd łączenia: `undefined reference to 'triple(int)'`. |

Warto zwrócić uwagę na **etap**, na którym pojawia się błąd. Błędy kompilacji dotyczą jednego pliku i składni lub typów.
Błędy łączenia (`undefined reference`, `multiple definition`) pojawiają się, gdy wszystkie pliki skompilowały się poprawnie,
a nie zgadzają się symbole między nimi.

## Do omówienia na zajęciach

- Czym różni się deklaracja od definicji? Co można zadeklarować wielokrotnie, a co zdefiniować tylko raz?
- Dlaczego zmiana pliku `.cpp` kompiluje jeden plik, a zmiana `.hpp` kilka?
- Czemu osłona nagłówka nie wystarcza, żeby umieścić zwykłą funkcję w nagłówku?
- Czemu `SQUARE(n + 1)` daje 7 i co by się stało, gdyby `SQUARE` było funkcją?
- Dlaczego wskaźnik do typu niepełnego jest dozwolony, a pole tego typu nie?
- Który z dwóch błędów, `undefined reference` czy `ambiguous`, pojawia się w kompilatorze, a który w linkerze?
- Po co `#ifdef __cplusplus` w nagłówku współdzielonym z C?
