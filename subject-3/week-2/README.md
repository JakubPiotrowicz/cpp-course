# Temat 3, tydzień 2 - statyki, kopiowanie, przenoszenie i `constexpr`

Przegląd całego tematu i zestawienie z czytankami: [../README.md](../README.md).
Lista czytanek: [../czytanki.md](../czytanki.md). Tydzień 1 ([../week-1/](../week-1/)) dotyczy klas, inicjowania,
`const`, konwersji i obiektów tymczasowych.

## Uruchomienie

```bash
cd subject-3/week-2
make                 # buduje wszystkie przykłady
make run             # uruchamia je po kolei
```

Pliki wynikowe trafiają do ignorowanego przez Git katalogu `build/`, a `make clean` go usuwa.
Czytaj ten plik po kolei, a przy każdej sekcji zajrzyj do wskazanego pliku `.cpp`. Katalog [broken/](broken/)
zawiera programy, które mają się źle zachowywać (błędy kompilacji i łączenia, ostrzeżenie).
Buduje je osobno `make broken`, a tabela w sekcji 8 mówi, czego się spodziewać.
Wymagane: `g++` w wersji obsługującej C++20 i GNU Make. Przykłady nie czytają danych z klawiatury.
Wyniki klasy `Noisy` objaśnia początek [../week-1/README.md](../week-1/README.md).

| Przykład | Plik | Zagadnienie |
| --- | --- | --- |
| 1 | [01-static.cpp](01-static.cpp) | Składowe statyczne klasy, zmienne lokalne `static`. |
| 2 | [02-using-and-inline.cpp](02-using-and-inline.cpp) | `typedef` i `using`, aliasy w klasie, `inline`. |
| 3 | [03-copy.cpp](03-copy.cpp) | Konstruktor kopiujący, przypisanie kopiujące, `= delete`. |
| 4 | [04-move.cpp](04-move.cpp) | `std::move`, r-referencje, przeciążanie, `noexcept`. |
| 5 | [05-special-members.cpp](05-special-members.cpp) | Które operacje kompilator generuje (reguły zera, trzech i pięciu). |
| 6 | [06-constexpr-classes.cpp](06-constexpr-classes.cpp) | `constexpr` w klasach, funkcjach i tablicach. |
| 7 | [07-casts-and-integers.cpp](07-casts-and-integers.cpp) | Dygresje: `static_cast` i typy całkowite o zadanej szerokości. |

## 1. Składowe statyczne i zmienne lokalne `static`

```bash
./build/01-static
```

```text
otwartych na starcie: 0
sizeof(Connection) = 8, sizeof(size_t) = 8 (składowe statyczne nie powiększają obiektu)
  połączenie 1 otwarte
  połączenie 2 otwarte
otwartych: 2, limit: 3
...
po zamknięciu drugiego: 1, można otworzyć kolejne: true
bilety: 101, 102, 103
pierwsze wywołanie cached_value():
  obliczam wartość początkową
drugie wywołanie cached_value():
wartości: 42, 42
```

- Składowa `static` należy do klasy, nie do obiektu: jest jedna, wspólna, i nie zwiększa `sizeof`.
  Metoda `static` nie ma wskaźnika `this`, więc widzi tylko składowe statyczne i wywołujemy ją przez
  `Connection::alive()` (zapis przez obiekt też działa, ale myli).
- Od C++17 składową statyczną można zdefiniować w klasie jako `inline static`. Bez `inline` definicja musi stać
  dokładnie raz w jednym pliku `.cpp` (`int Counter::count = 0;`), inaczej linker zgłosi `undefined reference`
  ([broken/static-member-undefined.cpp](broken/static-member-undefined.cpp)). `static constexpr` jest domyślnie `inline`.
- Zmienna lokalna `static` jest inicjowana **raz**, przy pierwszym przejściu przez jej deklarację, i zachowuje wartość
  między wywołaniami (`next_ticket`). W metodzie jest wspólna dla wszystkich obiektów (`log()`).
  Inicjator wykonuje się tylko za pierwszym razem, więc kosztowne obliczenie (`cached_value`) nie powtarza się.
- Zmienne `static` na poziomie pliku i inicjowanie przy pierwszym użyciu omawia [temat 2](../../subject-2/week-2/README.md).

## 2. `typedef`, `using` i `inline`

```bash
./build/02-using-and-inline
```

```text
id = 42, index = 42
operation(2, 3) = 5
row ma 3 elementy
playlista: pierwszy drugi
twice(21) = 42, max_users = 8, visits = 2
```

- `typedef` i `using` robią to samo, ale `using Nazwa = typ;` czyta się jak przypisanie, a przy typach funkcji
  i tablic jest dużo czytelniejsze (`using Operation = int (*)(int, int);`). W nowym kodzie piszemy `using`.
  Tylko `using` może być szablonem (temat 4).
- Alias **nie tworzy nowego typu**. `Id` i `Index` to ten sam typ (`static_assert(std::is_same_v<...>)`),
  więc kompilator nie pomoże pilnować, żeby ich nie pomylić. Do tego potrzebna jest osobna klasa lub `enum class`.
- Aliasy w klasie (`Track`, `Tracks`, `const_iterator`) ukrywają reprezentację. Metody `begin()` i `end()` wystarczą,
  żeby pętla `for (x : playlist)` działała.
- Słowo `using` ma kilka znaczeń: alias typu (tu), deklaracja i dyrektywa `using` dla przestrzeni nazw (temat 2),
  `using enum` (tydzień 1, sekcja 2).
- `inline` nie prosi o wstawianie kodu w miejscu wywołania. Oznacza, że definicja funkcji lub zmiennej może wystąpić
  w wielu plikach (np. w nagłówku), jeśli wszędzie jest taka sama, i program ma jeden egzemplarz. Funkcje zdefiniowane
  w ciele klasy są domyślnie `inline`. Temat 2 (sekcja 1) pokazuje, że definicja zwykłej funkcji w nagłówku, bez `inline`, kończy się błędem łączenia.

## 3. Kopiowanie

```bash
./build/03-copy
```

```text
Noisy copy = original (inicjowanie):
  #2 "original": kopiowanie z #1
other = original (przypisanie do istniejącego obiektu):
  #3 "original": przypisanie kopiujące z #1
...
Bundle copy_of_bundle = bundle:
  #8 "first": kopiowanie z #6
  #9 "second": kopiowanie z #7
copy_of_bundle = bundle:
  #8 "first": przypisanie kopiujące z #6
  #9 "second": przypisanie kopiujące z #7
...
  Document: kopiowanie, historia kopii zaczyna się od zera
  Document: przypisanie kopiujące
  Document: przypisanie do samego siebie, nic do zrobienia
historia: first = 0, second = 1
```

- Konstruktor kopiujący tworzy **nowy** obiekt z istniejącego (inicjowanie, przekazanie przez wartość, `push_back`).
  Operator przypisania kopiującego zmienia **już istniejący** obiekt. To dwie różne operacje, choć obie zapisujemy
  ze znakiem `=`. Rozróżnia je to, czy po lewej stronie jest nowa deklaracja.
- Parametr konstruktora kopiującego musi być referencją (`const T&`). Gdyby był wartością, jego utworzenie
  wymagałoby kopiowania, czyli wywołania tego samego konstruktora w nieskończoność.
- Bez własnych operacji kompilator kopiuje składowe po kolei, w kolejności deklaracji, za pomocą ich operacji kopiujących
  (`Bundle`). Dla klas, które składają się z napisów i kontenerów, to w zupełności wystarcza (reguła zera).
- Własne operacje piszemy, gdy kopia nie ma być dosłownym powieleniem (`Document` zaczyna własną historię)
  albo gdy klasa pilnuje zasobu. Operator przypisania zwraca `*this` przez referencję i zwykle sprawdza `this == &other`,
  żeby przypisanie do samego siebie niczego nie psuło.
- `= delete` zabrania operacji. Klasa `Token` nie jest kopiowalna: można ją tylko przekazywać przez referencję.
  Próba skopiowania kończy się błędem kompilacji ([broken/copy-deleted.cpp](broken/copy-deleted.cpp)).
- Zwalnianie zasobów ręcznie (`new`, `delete`) i idiom copy-and-swap to temat 5.

## 4. Przenoszenie

```bash
./build/04-move
```

```text
  #1 "source": konstruktor
  #2 "source": przenoszenie z #1
etykieta source po przeniesieniu: []
etykieta target: [source]
...
accept(lvalue):
  accept(const Noisy&)
accept(std::move(lvalue)):
  accept(Noisy&&)
etykieta lvalue po wywołaniu: [lvalue]
...
  #7 "fixed": konstruktor
  #8 "fixed": kopiowanie z #7
...
Careful:
  Careful: przeniesienie
  Careful: przeniesienie
  Careful: przeniesienie
Careless:
  Careless: kopia
  Careless: kopia
  Careless: kopia
```

- **l-wartość** ma nazwę i adres (zmienna), **r-wartość** to wartość tymczasowa, która za chwilę zniknie.
  Referencja `T&&` wiąże się tylko z r-wartościami. Konstruktor przenoszący `T(T&&)` może więc bezpiecznie
  ,,ukraść'' zawartość argumentu zamiast ją kopiować. Próba powiązania `T&&` z nazwanym obiektem kończy się błędem
  kompilacji ([broken/rvalue-from-lvalue.cpp](broken/rvalue-from-lvalue.cpp)).
- `std::move` niczego nie przenosi. To tylko rzutowanie na r-wartość, które pozwala wybrać przeciążenie `T&&`.
  Przenosi dopiero kod w środku tego przeciążenia (konstruktor, operator przypisania). Samo `accept(std::move(x))`
  zostawia `x` nietknięte.
- Obiekt po przeniesieniu jest w stanie **poprawnym, ale nieokreślonym**: można go zniszczyć lub mu coś przypisać,
  ale nie wolno zakładać, co zawiera. `Noisy` zeruje etykietę, ale dla innych klas nie ma takiej gwarancji.
- `std::move` na obiekcie `const` kończy się kopiowaniem, bo konstruktor przenoszący wymaga obiektu zmienialnego.
- Wektor przy powiększaniu przenosi elementy tylko wtedy, gdy konstruktor przenoszący jest `noexcept`. W przeciwnym razie
  kopiuje, żeby zachować gwarancję, że wyjątek w trakcie nie zniszczy danych. Dlatego przenoszenie warto oznaczać `noexcept`.
- Nie piszemy `return std::move(local);` przy zwracaniu zmiennej lokalnej. Zwykłe `return local;` pozwala pominąć
  przeniesienie, a `std::move` temu przeszkadza ([broken/pessimizing-move.cpp](broken/pessimizing-move.cpp),
  ostrzeżenie `-Wpessimizing-move`).

## 5. Operacje generowane przez kompilator

```bash
./build/05-special-members
```

```text
--- RuleOfZero ---
  #1 "reguła zera": konstruktor
kopiowanie:
  #2 "reguła zera": kopiowanie z #1
przenoszenie:
  #3 "reguła zera": przenoszenie z #1

--- WithDestructor ---
  #4 "destruktor": konstruktor
przenoszenie:
  #5 "destruktor": kopiowanie z #4
...
--- WithMoveConstructor ---
  #8 "konstruktor przenoszący": konstruktor
przenoszenie:
  #9 "konstruktor przenoszący": przenoszenie z #8
```

Sześć operacji specjalnych: konstruktor domyślny, destruktor, konstruktor kopiujący, operator przypisania kopiującego,
konstruktor przenoszący i operator przypisania przenoszącego. Co generuje kompilator, zależy od tego, co zadeklarujemy:

| Zadeklarowane przez nas | Kopiowanie | Przenoszenie |
| --- | --- | --- |
| nic (reguła zera) | generowane | generowane |
| destruktor | generowane (przestarzałe) | **nie** generowane, przenoszenie kopiuje |
| konstruktor kopiujący lub przypisanie kopiujące | generowane drugie (przestarzałe) | **nie** generowane, przenoszenie kopiuje |
| konstruktor przenoszący lub przypisanie przenoszące | **usunięte** | zadeklarowane jest, drugie nie |
| dowolny konstruktor | bez zmian | bez zmian, ale **nie ma** konstruktora domyślnego |

- **Reguła zera:** jeśli klasa składa się z członków, które same dbają o siebie (`std::string`, `std::vector`),
  nie deklarujemy żadnej z sześciu operacji.
- **Reguła pięciu:** jeśli deklarujemy własny destruktor, konstruktor kopiujący lub przenoszący albo jeden z operatorów
  przypisania, to zwykle trzeba zadeklarować (jawnie, `= default` lub `= delete`) wszystkie pięć. Reguła trzech to
  wersja sprzed C++11, bez operacji przenoszących.
- Zmiana zasad, która zaskakuje: dopisanie pustego destruktora w klasie wyłącza przenoszenie i po cichu zamienia je
  na kopiowanie. Kod nadal się kompiluje, tylko robi się wolniejszy.

## 6. `constexpr`

```bash
./build/06-constexpr-classes
```

```text
buffer ma 4 elementy
squares: 0 1 4 9 16 25
dynamic.length() = 3, factorial(runtime_end) = 6
dynamic.contains(2) = true
```

- Klasa z konstruktorem `constexpr` i metodami `constexpr` (typ literalny) pozwala tworzyć obiekty w czasie kompilacji
  i używać ich w `static_assert` oraz jako rozmiar tablicy (`std::array<int, window.length()>`).
- Od C++14 funkcja `constexpr` może mieć pętle i zmienne lokalne, więc `make_squares` buduje całą tablicę w czasie
  kompilacji.
- `constexpr` nie znaczy ,,zawsze w czasie kompilacji''. Te same funkcje i klasy działają też z wartościami
  znanymi dopiero w czasie działania (`dynamic`). W czasie kompilacji wykonują się, gdy tego wymaga kontekst
  (`constexpr` zmienna, `static_assert`, rozmiar tablicy) i argumenty są stałe.
- Zmienna `constexpr` musi być zainicjowana wyrażeniem stałym. Wywołanie zwykłej funkcji lub użycie zmiennej
  niestałej jest błędem ([broken/constexpr-nonconstant.cpp](broken/constexpr-nonconstant.cpp)).
- `consteval` i `constinit` są w [tygodniu 1](../week-1/README.md), sekcja 9.

## 7. Dygresje: rzutowanie i typy całkowite

```bash
./build/07-casts-and-integers
```

```text
static_cast<int>(3.99) = 3, (int)3.99 = 3
7 / 2 = 3, ale static_cast<double>(7) / 2 = 3.5
Level::High jako liczba: 9
int8_t o wartości 65 wypisany wprost: A, po rzutowaniu: 65
uint8_t 255 + 1 = 0
size_t 2 - 3 = 18446744073709551615
-1 < 1u po zamianie na unsigned: false
std::cmp_less(-1, 1u): true
```

- `static_cast<T>(x)` jest jawne, łatwe do znalezienia w kodzie (`grep`) i dopuszcza tylko sensowne konwersje.
  Rzutowanie w stylu C `(T)x` robi to samo, ale może też po cichu zrobić `reinterpret_cast` lub `const_cast`.
  Najczęściej `static_cast` potrzebny jest do konwersji liczb i `enum class` na `int` oraz do dzielenia ułamkowego.
- `<cstdint>` daje typy o dokładnie określonej szerokości (`std::int32_t`, `std::uint64_t`), a `std::size_t` jest typem
  rozmiarów i indeksów. Rozmiary `int`, `long` i `wchar_t` zależą od platformy, więc dla formatów i protokołów
  używamy typów z `<cstdint>`.
- `std::int8_t` i `std::uint8_t` są zwykle `char`, więc `cout` wypisuje je jako znaki.
- Arytmetyka na typach bez znaku zawija się modulo `2^n` (dobrze określone zachowanie). Odjęcie większego `size_t`
  od mniejszego daje ogromną liczbę, co jest częstym źródłem błędów w pętlach do tyłu (`i >= 0` jest zawsze prawdziwe).
  Przepełnienie typu ze znakiem to zachowanie niezdefiniowane.
- Porównanie `int` z typem bez znaku zamienia liczbę ujemną na ogromną dodatnią (ostrzeżenie `-Wsign-compare`).
  Funkcje `std::cmp_less` i pokrewne z `<utility>` (C++20) porównują zgodnie z wartościami.

## 8. Celowo błędne warianty (`broken/`)

```bash
make broken
```

Polecenie kompiluje po kolei każdy plik z katalogu `broken/`. Błędy kompilacji i łączenia są tu oczekiwane,
więc `make` nie przerywa pracy. Pliki, które się zbudują, trafiają do `build/broken/`.

| Plik | Czego się spodziewać |
| --- | --- |
| [static-member-undefined.cpp](broken/static-member-undefined.cpp) | Błąd łączenia: `undefined reference to 'Counter::count'`. |
| [copy-deleted.cpp](broken/copy-deleted.cpp) | Dwa błędy: `use of deleted function 'Token::Token(const Token&)'`. |
| [rvalue-from-lvalue.cpp](broken/rvalue-from-lvalue.cpp) | Błąd: `cannot bind rvalue reference of type 'std::string&&' to lvalue of type 'std::string'`. |
| [pessimizing-move.cpp](broken/pessimizing-move.cpp) | Ostrzeżenie `-Wpessimizing-move`. Program działa, ale w `make_with_move` pojawia się dodatkowe przeniesienie. |
| [constexpr-nonconstant.cpp](broken/constexpr-nonconstant.cpp) | Dwa błędy: `call to non-'constexpr' function` i `the value of 'runtime_value' is not usable in a constant expression`. |

Uruchomienie wariantu, który się zbudował:

```bash
./build/broken/pessimizing-move
```

## Do omówienia na zajęciach

- Ile obiektów `Connection` istnieje po wyjściu z bloku i skąd to wiemy? Co jest wspólne dla wszystkich obiektów klasy?
- Kiedy zmienna lokalna `static` jest inicjowana i co się stanie, jeśli jej inicjator rzuci wyjątek?
- Czym różni się konstruktor kopiujący od operatora przypisania? Dlaczego pierwszy ma parametr tylko przez referencję?
- Czemu `std::move` nie przenosi? Co jest przenoszone i gdzie?
- Kiedy klasa nie potrzebuje żadnej z pięciu operacji? Skąd wiemy, że reguła zera wystarczy?
- Dlaczego wektor kopiuje elementy `Careless`, a przenosi `Careful`? Co przez to zyskujemy lub tracimy?
- Czym różni się `const` od `constexpr` i kiedy zmienna `const` jest stałą w czasie kompilacji?
- Co się stanie z pętlą `for (std::size_t i = v.size() - 1; i >= 0; --i)`?
