# Dział 2 — kompilowanie i przestrzenie nazw

## Uruchomienie

Z głównego katalogu repozytorium przejdź do katalogu z przykładami:

```bash
cd subject-2/week-2
make                 # buduje wszystkie poprawne przykłady
make run             # uruchamia je po kolei
```

Wszystkie dalsze polecenia wykonuj z katalogu `week-2`.
Wymagane: `g++`, `gcc`, GNU Make; do podglądu symboli `nm`.
Przykłady korzystają z C++20 i C17 i nie wymagają danych z klawiatury.
Pliki wynikowe trafiają do ignorowanego przez Git `build/`.
`make clean` usuwa ten katalog. Aby zmienić kompilatory, wykonaj
`make clean`, a następnie `make CXX=clang++ CC=clang`.
Po zmianie flag kompilacji też zacznij od `make clean`.

Niektóre polecenia włączają celowo niepoprawne warianty kodu przez makra `DEMO_...`.
Opis przy każdym z nich wyjaśnia, czy błąd powinien wystąpić podczas kompilacji, czy podczas łączenia.
Zwykłe `make` nie włącza tych wariantów.

| Przykład | Pliki | Zagadnienie |
| --- | --- | --- |
| 1 | [01-build/](01-build/) | Osobna kompilacja, łączenie, nagłówki i przeciążanie funkcji. |
| 2 | [02-state/](02-state/) | `extern`, powiązanie nazw i trwałość zmiennych `static`. |
| 3 | [03-macros.cpp](03-macros.cpp) | Preprocesor, `const` i `constexpr`. |
| 4 | [04-using.cpp](04-using.cpp) | Przestrzenie nazw, deklaracja i dyrektywa `using`. |
| 5 | [05-initialization.cpp](05-initialization.cpp) | Inicjalizacja przy pierwszym użyciu i `constinit`. |
| 6 | [06-c-linkage/](06-c-linkage/) | Łączenie kodu C i C++ przez interfejs z `extern "C"`. |
| 7 | [07-forward.cpp](07-forward.cpp) | Deklaracje zapowiadające i niepełne typy. |

## 1. Dwa pliki źródłowe, kompilator i linker

W `01-build/main.cpp` znajdują się dwa wywołania `math::add`:
dla dwóch liczb oraz dla dwóch punktów. Struktura `Point` przechowuje parę współrzędnych.

```bash
./build/01-build-demo
```

Wynik:

```text
5
4 6
```

Podział między `math.hpp` a `math.cpp` pozwala kompilować pliki osobno:

- Nagłówek opisuje typ i deklaruje funkcje. Samo `int add(int, int);` nie jest definicją funkcji.
- `math.cpp` zawiera definicje, czyli ciała funkcji. Włącza własny nagłówek, więc kompilator może sprawdzić ich zgodność z deklaracjami.
- Kompilator wybiera przeciążenie na podstawie typów argumentów. Sam typ wyniku nie wystarczyłby do przeciążenia.
- Każdy `.cpp` po przetworzeniu dyrektyw preprocesora, w tym rozwinięciu `#include`, tworzy osobną jednostkę translacji. Taki podział na pliki i nagłówki jest niezależny od modułów C++20 korzystających z `import`.

### Osobne kompilowanie i łączenie

```bash
mkdir -p build/manual
g++ -std=c++20 -Wall -Wextra -Wpedantic -c 01-build/main.cpp -o build/manual/main.o
g++ -std=c++20 -Wall -Wextra -Wpedantic -c 01-build/math.cpp -o build/manual/math.o
g++ build/manual/main.o build/manual/math.o -o build/manual/demo
./build/manual/demo
```

`-c` zatrzymuje sterownik po utworzeniu pliku obiektowego. `.o` nie jest gotowym programem.
Ostatnia komenda `g++` uruchamia łączenie i dołącza biblioteki potrzebne C++.

Do skompilowania `main.cpp` wystarczają deklaracje funkcji z nagłówka — tak powstaje `main.o`.
Do utworzenia całego programu potrzebne są też definicje funkcji z `math.o`.
Pominięcie tego pliku powoduje błąd linkera:

```bash
g++ build/manual/main.o -o build/manual/missing-definition
```

Linker zgłasza `undefined reference` dla `math::add`. Kompilacja wywołań już się udała;
teraz brakuje definicji przy łączeniu. Zwróć uwagę na etap, na którym występuje błąd.
Dokładne brzmienie komunikatu zależy od narzędzi.

### Kompilowanie przyrostowe

```bash
make build/01-build-demo
make build/01-build-demo
touch 01-build/math.cpp
make build/01-build-demo
touch 01-build/math.hpp
make build/01-build-demo
```

Drugie `make` nic nie kompiluje. Po zmianie czasu modyfikacji `math.cpp` powstaje
tylko nowy `math.o`, a następnie program. Po zmianie nagłówka kompilują się **oba**
pliki źródłowe i znów następuje łączenie. `touch` symuluje zapis pliku, bez zmiany jego treści.

W `Makefile` reguła `build/%.o: %.cpp` opisuje kompilowanie pliku źródłowego do obiektowego.
Osobne reguły określają, które pliki obiektowe należy połączyć w program.
`-MMD -MP` generuje pliki `.d`, a `-include` wczytuje zapisane w nich zależności od nagłówków.
To dzięki nim `make` wie, że zmiana `math.hpp` dotyczy obu `.o`.
Wygenerowane zależności można odczytać poleceniem:

```bash
cat build/01-build/main.d
```

### Osłony nagłówków i wielokrotne definicje

W `main.cpp` celowo dwa razy włączamy ten sam nagłówek. `#ifndef` / `#define` / `#endif`
sprawiają, że jego zawartość trafia do tej jednostki translacji tylko raz.
Bez osłony dwie definicje `Point` w jednej jednostce spowodowałyby błąd kompilacji.
Same powtórzone zgodne deklaracje funkcji byłyby dozwolone.

Osłona działa w obrębie jednej jednostki translacji. Nie zapobiega umieszczeniu definicji
zwykłej funkcji z nagłówka w dwóch różnych jednostkach: każdy plik jest przetwarzany osobno.
Makro `DEMO_HEADER_DEFINITION` włącza taką definicję w `math.hpp`:

```bash
g++ -std=c++20 -DDEMO_HEADER_DEFINITION 01-build/main.cpp 01-build/math.cpp -o build/duplicate-definition
```

Linker zgłasza `multiple definition` dla `math::header_bonus`.
Typowe rozwiązanie: deklaracja w `.hpp`, definicja w jednym `.cpp`.
Funkcje `inline` podlegają innym zasadom: ich identyczne definicje mogą występować
w wielu jednostkach translacji przy spełnieniu reguły jednej definicji (ODR).

### Przeciążanie funkcji i name mangling

```bash
nm build/01-build/math.o
nm -C build/01-build/math.o
```

Znajdź dwa symbole `math::add`. Pierwszy widok pokazuje nazwy zakodowane dla linkera,
drugi je odkodowuje. Name mangling pozwala tu odróżnić przestrzeń nazw i typy parametrów.
Dokładna postać zakodowanej nazwy zależy od ABI, czyli reguł współpracy skompilowanych fragmentów programu.
Zwróć uwagę na to, że oba przeciążenia mają osobne symbole.

## 2. `extern` i dwa znaczenia `static`

Pliki w `02-state` pokazują trzy sposoby przechowywania liczników.
Przed uruchomieniem prześledź zmiany `shared_count`, obu zmiennych `file_count` oraz `last_id`.

```bash
./build/02-state-demo
```

```text
shared: 12
main private: 1
counter private: 2
ids: 1 2
```

`extern int shared_count;` jest deklaracją. Jedna definicja `int shared_count = 0;`
znajduje się w `counter.cpp`. Dwa wywołania zwiększają licznik do 2,
a `main` dodaje 10 do **tego samego obiektu**.
Nagłówek pozwala kompilować oba pliki niezależnie, a linker łączy odwołania z definicją.

`static int file_count` na poziomie pliku ma wewnętrzne powiązanie:
obiekty z obu `.cpp` są osobne. W `main.cpp` zwiększamy jego licznik raz,
w `counter.cpp` — dwa razy. Bez `static` te dwie definicje tej samej nazwy globalnej
naruszałyby regułę jednej definicji. W nowym kodzie podobną prywatność nazw
często zapisuje się anonimową przestrzenią `namespace { ... }`.

`static int last_id` **wewnątrz funkcji** ma zakres lokalny i trwałość statyczną.
Nie znika po wyjściu z funkcji, dlatego drugie wywołanie zwraca 2.
To inna rola słowa `static` niż ograniczenie powiązania nazwy na poziomie pliku.

Zwróć uwagę, że `extern int shared_count = 0;` byłoby już definicją z powodu inicjalizatora.
Dla zwykłej zmiennej włączanej do wielu `.cpp`
wróciłby problem wielu definicji. `extern` nie oznacza automatycznie „bez definicji”.

## 3. Preprocesor, `const` i `constexpr`

W `03-macros.cpp` makro i dwie stałe wyglądają podobnie, ale zachowują się inaczej.
Przed uruchomieniem przewidź wynik wyrażenia `4 * SCALE`:

```bash
./build/03-macros
```

```text
macro: 11
const: 20
constexpr: 20
parenthesized macro: 20
```

`SCALE` rozwija się do `2 + 3`, zatem dostajemy `4 * 2 + 3`.
Makro jest podmianą tokenów, bez własnego typu ani reguł zakresu jak dla zwykłej zmiennej.
Nawiasy naprawiają tę konkretną pułapkę. Dla stałej liczbowej zwykle prościej użyć typowanego obiektu.

`const` zakazuje modyfikowania obiektu, ale ogólnie może mieć inicjalizator obliczony podczas działania.
`constexpr` wymaga stałego inicjalizatora. Tutaj również `const int scale = 2 + 3`
może wystąpić w wyrażeniu stałym. Samo `const` nie rozstrzyga, kiedy zostanie obliczony inicjalizator.

Makro `DEMO_VERBOSE` pozwala zmienić kod programu podczas kompilacji:

```bash
g++ -std=c++20 -Wall -Wextra -Wpedantic -DDEMO_VERBOSE=1 03-macros.cpp -o build/macros-verbose
./build/macros-verbose
```

Dojdzie linia `verbose mode is enabled`. `#if` wybiera źródło przed właściwą kompilacją.
`-D` definiuje makro z wiersza poleceń. Sam wynik preprocesora można podejrzeć tak:

```bash
g++ -std=c++20 -E -P 03-macros.cpp | rg 'macro:|verbose mode'
```

Zobaczymy rozwinięte `4 * 2 + 3`, a bez `-D` linia z `verbose mode` zniknie.
Polecenie używa `rg`; jeśli go nie ma, można użyć `grep -E` z tym samym wzorcem.

Zwróć uwagę na różnicę między `#if` a `#ifdef`:
`#if DEMO_VERBOSE` sprawdza wartość, więc `-DDEMO_VERBOSE=0` nie włącza wypisywania.
`#ifdef DEMO_VERBOSE` sprawdzałoby tylko istnienie makra, także z wartością 0.

## 4. Przestrzenie nazw i `using`

```bash
./build/04-using
```

```text
metric::step: 1
imperial::step: 3
using-declaration: 1
using-directive: 1
qualified again: 1
```

W `04-using.cpp` występują trzy sposoby odwoływania się do nazwy:

- `metric::step` jawnie wskazuje wybraną przestrzeń nazw.
- `using metric::step;` to **deklaracja using** — wprowadza wybraną nazwę do bloku.
- `using namespace metric;` to **dyrektywa using** — pozwala uwzględniać nazwy z tej przestrzeni przy wyszukiwaniu. Nie kopiuje obiektów ani nie scala przestrzeni.

Makro `DEMO_AMBIGUOUS` włącza drugi wpis `using namespace` w tym samym bloku:

```bash
g++ -std=c++20 -DDEMO_AMBIGUOUS -fsyntax-only 04-using.cpp
```

Kompilator nie może wybrać między `metric::step` i `imperial::step`.
Wadliwe jest użycie nazwy po drugiej dyrektywie; samo wpisanie obu dyrektyw nie musi jeszcze być błędem.
`-fsyntax-only` sprawdza kod bez tworzenia programu.

Użycie `metric::step` albo `imperial::step` usuwa niejednoznaczność nawet przy zachowaniu obu dyrektyw.
Unikaj globalnego `using namespace ...` w nagłówkach: taka dyrektywa wpływa na wyszukiwanie
nazw także w plikach, które je włączają.

## 5. Inicjalizacja przy pierwszym użyciu i `constinit`

W `05-initialization.cpp` struktura `Registry` ma licznik i konstruktor,
który wypisuje komunikat. Funkcja `registry()` zwraca referencję do jednego obiektu.

```bash
./build/05-initialization
```

```text
main started
constinit counter: 1
Registry initialized
first count: 1
second count: 2
same object: true
```

Dwie wizyty w `registry()` dają tylko jedno wywołanie konstruktora.
Lokalny `static Registry instance` jest dynamicznie inicjalizowany przy pierwszym dojściu do deklaracji.
Referencje `first` i `second` odnoszą się do tego samego obiektu, co potwierdza porównanie adresów.

Jeżeli konstruktor globalnego obiektu w `a.cpp`
korzysta z obiektu dynamicznie inicjalizowanego w `b.cpp`, nie wolno po prostu zakładać,
że ten drugi jest już gotowy. Akcesor z lokalnym `static` pozwala zainicjalizować potrzebny
obiekt przy jego pierwszym użyciu. Zwróć uwagę, że `Registry initialized` pojawia się
dopiero po `main started`, a przy drugim wywołaniu `registry()` konstruktor nie wykonuje się ponownie.
To rozwiązanie nie usuwa automatycznie cyklicznych zależności inicjalizacji ani problemów kolejności niszczenia obiektów.

`constinit` wymaga statycznej inicjalizacji, ale **nie oznacza niezmienności**.
Dlatego `++counter` działa. Makro `DEMO_BAD_CONSTINIT` włącza inicjalizator,
który nie spełnia wymagania `constinit`:

```bash
g++ -std=c++20 -DDEMO_BAD_CONSTINIT -fsyntax-only 05-initialization.cpp
```

Kompilator zgłasza błąd: inicjalizator `bad_counter` wywołuje funkcję bez `constexpr`.
Zwykłe `const int x = initial_value();` byłoby dozwolone, lecz nie zapewniałoby statycznej inicjalizacji.

## 6. Łączenie kodu C i C++: `extern "C"`

W `06-c-linkage/api.c` znajduje się funkcja `triple`, a w `main.cpp` — jej wywołanie z C++.
Wspólny nagłówek `api.h` deklaruje funkcję dla obu języków.

```bash
./build/06-c-linkage-demo
```

Wynik: `triple(7) = 21`. W `Makefile` plik `.c` kompilujemy przez `gcc`,
a `.cpp` przez `g++`; gotowe obiekty łączymy sterownikiem C++, który dołącza jego biblioteki.
`#ifdef __cplusplus` sprawia, że kompilator C nie zobaczy składni `extern "C"`.

Teraz wyłącz otoczkę wyłącznie po stronie C++:

```bash
g++ -std=c++20 -DDEMO_CPP_LINKAGE -c 06-c-linkage/main.cpp -o build/cpp-linkage.o
g++ build/cpp-linkage.o build/06-c-linkage/api.o -o build/cpp-linkage-broken
```

Pierwsza komenda przechodzi, druga ma dać `undefined reference` do `triple(int)`.
W GCC i Clangu przy użyciu ABI na Linuksie kod C eksportuje `triple`,
a kod C++ bez `extern "C"` żąda zakodowanej nazwy uwzględniającej typ parametru.

```bash
nm build/06-c-linkage/api.o
nm build/cpp-linkage.o | rg triple
nm -C build/cpp-linkage.o | rg triple
```

W tym ABI polecenia pokazują odpowiednio `T triple`, `U _Z6triplei` i `U triple(int)`.
`T` oznacza tu definicję funkcji, `U` — odwołanie wymagające definicji.
`extern "C"` określa językowe powiązanie interfejsu, dzięki czemu odwołanie pasuje do funkcji C.
`extern int shared_count;` z przykładu 2 deklaruje zmienną — to inne zastosowanie słowa `extern`.

Zwróć uwagę, że `extern "C"` nie tłumaczy kodu C++ na C.
Każdy plik nadal kompilujemy we właściwym języku; uzgadniamy interfejs między nimi.

## 7. Deklaracje zapowiadające i niepełne typy

W `07-forward.cpp` zapis `struct Node;` zapowiada istnienie typu.
Wskaźnik `Node*` może być polem `Link` jeszcze przed pełną definicją `Node`.
Po zobaczeniu definicji można utworzyć `Node node{42}` i odczytać `value`.

```bash
./build/07-forward
g++ -std=c++20 -DDEMO_INCOMPLETE -fsyntax-only 07-forward.cpp
```

Pierwsze polecenie wypisuje `42`. Drugie celowo nie przechodzi:
pole `Node target` potrzebuje pełnego typu już w miejscu definicji `BrokenLink`.
Sama deklaracja funkcji również może używać niepełnego typu jako parametru przez wartość;
przy definiowaniu takiej funkcji i jej wywoływaniu potrzebna będzie pełna definicja.

Wskaźnik wystarcza, ponieważ układ `Link` nie musi zawierać całego `Node`.
Kompilator zna sposób przechowywania wskaźnika bez znajomości pól wskazywanego typu.
Zwróć uwagę na różnicę między przechowywaniem adresu obiektu a przechowywaniem samego obiektu jako pola.
