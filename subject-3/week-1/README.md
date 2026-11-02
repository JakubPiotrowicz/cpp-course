# Temat 3, tydzień 1 - wartości, klasy, inicjowanie, `const` i obiekty tymczasowe

Przegląd całego tematu i zestawienie z czytankami: [../README.md](../README.md).
Lista czytanek: [../czytanki.md](../czytanki.md). Tydzień 2 ([../week-2/](../week-2/)) dotyczy statyków,
kopiowania, przenoszenia i `constexpr`.

## Uruchomienie

Z głównego katalogu repozytorium przejdź do katalogu z przykładami:

```bash
cd subject-3/week-1
make                 # buduje wszystkie przykłady
make run             # uruchamia je po kolei
```

Wszystkie dalsze polecenia wykonuj z katalogu `week-1`.
Wymagane: `g++` w wersji obsługującej C++20 (sprawdź: `g++ --version`) i GNU Make.
Pliki wynikowe trafiają do ignorowanego przez Git katalogu `build/`, a `make clean` go usuwa.
Czytaj ten plik po kolei, a przy każdej sekcji zajrzyj do wskazanego pliku `.cpp`. Katalog [broken/](broken/)
zawiera programy, które mają się źle zachowywać (błędy kompilacji, ostrzeżenia, błąd pamięci).
Buduje je osobno `make broken`, a tabela w sekcji 10 mówi, czego się spodziewać.

| Przykład | Plik | Zagadnienie |
| --- | --- | --- |
| 1 | [01-value-vs-reference.cpp](01-value-vs-reference.cpp) | Kopia a referencja, przekazywanie do funkcji, pętla po kontenerze. |
| 2 | [02-class-and-enum.cpp](02-class-and-enum.cpp) | `enum`, `enum class`, klasa z interfejsem publicznym i prywatnym, niezmiennik. |
| 3 | [03-constructors.cpp](03-constructors.cpp) | Lista inicjująca, konstruktor domyślny i delegujący, destruktor, kolejność. |
| 4 | [04-initialization.cpp](04-initialization.cpp) | Nawiasy okrągłe i klamrowe, `initializer_list`, zawężanie, `auto`. |
| 5 | [05-const.cpp](05-const.cpp) | Metody `const`, przeciążanie po `const`, `mutable`, składowe `const` i referencje. |
| 6 | [06-conversions.cpp](06-conversions.cpp) | Konstruktor jednoargumentowy, `explicit`, operator konwersji, ciąg konwersji. |
| 7 | [07-temporaries.cpp](07-temporaries.cpp) | Czas życia wartości tymczasowych i wiązanie z referencją. |
| 8 | [08-operators.cpp](08-operators.cpp) | `<<`, `+`, `++`, operator `<=>` i porównania. |
| 9 | [09-consteval-constinit.cpp](09-consteval-constinit.cpp) | `constexpr`, `consteval` i `constinit`. |

## Jak czytać wyniki klasy `Noisy`

Przykłady 1, 3, 4, 7 (a w tygodniu 2 także 3, 4 i 5) używają klasy [../noisy.hpp](../noisy.hpp).
Każda jej operacja wypisuje wiersz w postaci:

```text
  #3 "original": kopiowanie z #1
```

`#3` to numer obiektu nadawany w chwili powstania (każda kopia dostaje nowy numer), w cudzysłowie jest etykieta,
a po dwukropku nazwa operacji: `konstruktor`, `kopiowanie`, `przenoszenie`, `przypisanie kopiujące`,
`przypisanie przenoszące` lub `destruktor`. Po przeniesieniu etykieta obiektu źródłowego jest pusta
(widać to w jego destruktorze: `#1 "": destruktor`). Przenoszenie omawiamy dokładnie w tygodniu 2.
Na razie czytaj je tak: ,,obiekt powstał z tymczasowego, bez kopiowania wszystkich danych''.

## 1. Wartości i referencje

```bash
./build/01-value-vs-reference
```

```text
a = (1, 2)
b = (100, 2)
first[0] = 1, second[0] = 99
...
alias to ten sam obiekt co a: true
...
a po shift_copy = (100, 2)
a po shift_in_place = (110, 2)
```

Przed uruchomieniem przewidź, ile razy zostanie wywołany konstruktor kopiujący w sekcjach o `Noisy`.

- Semantyka wartości: `Point b = a;` tworzy niezależny obiekt. To samo dotyczy `std::vector` i `std::string`:
  kopia ma własne elementy. Dlatego w C++ przekazanie przez wartość nigdy nie zmienia oryginału.
- Referencja jest drugą nazwą istniejącego obiektu. Musi być zainicjowana i nie da się jej przestawić:
  `alias = b` kopiuje wartość `b` do `a`, a `&alias == &a` pozostaje prawdą.
- Parametr przekazany przez wartość wywołuje konstruktor kopiujący, a `const T&` nie. Wyjątek: argument będący
  wartością zwróconą z funkcji (`take_by_value(make_noisy())`) powstaje od razu w parametrze, bez kopii (C++17).
- `for (auto item : items)` kopiuje każdy element. Zwykle chcemy `for (const auto& item : items)`.
- Porównaj z przekazywaniem napisów w [temacie 1](../../subject-1/week-1/README.md) (sekcja 3).

## 2. Klasy i enumy

```bash
./build/02-class-and-enum
```

```text
North == 0: true
Scale::Kelvin jako liczba: 1
sizeof(Scale) = 1, sizeof(Direction) = 4
woda wrze: 373.15 K, 212 F
pokój: 68 F
błąd: poniżej zera absolutnego
błąd: poniżej zera absolutnego
po nieudanej zmianie nadal: 100 C
```

- Stary `enum` wprowadza nazwy do otaczającego zasięgu i zamienia się na `int`. `enum class` ma nazwy w zasięgu
  typu (`Scale::Kelvin`) i nie zamienia się niejawnie na liczbę; konwersja wymaga `static_cast`.
  Typ bazowy można wybrać (`: unsigned char`).
- `using enum Scale;` (C++20) pozwala w jednym bloku pisać `Celsius` zamiast `Scale::Celsius`.
- W `struct` składowe są domyślnie publiczne, w `class` prywatne. Poza domyślnym sposobem dziedziczenia to jedyna różnica między nimi.
- Interfejs klasy to jej część publiczna. Reprezentacja jest prywatna, więc tylko metody klasy mogą ją zepsuć
  i tylko one muszą pilnować niezmiennika (`kelvin_ >= 0`). Zmiana `change_by` najpierw sprawdza nową wartość,
  a dopiero potem ją zapisuje, więc po błędzie obiekt się nie zmienia.
- `using Degrees = double;` wewnątrz klasy to alias zagnieżdżony, dostępny jako `Temperature::Degrees`.
- Wyjątki (`throw`, `try`, `catch`) omawia temat 5. Tu służą tylko do zgłoszenia, że warunek nie został spełniony.

## 3. Konstruktory i destruktor

```bash
./build/03-constructors
```

```text
--- Lista inicjująca ---
  #1 "pierwszy": konstruktor
  #2 "drugi": konstruktor
  ciało konstruktora WithInitList
  koniec bloku
  #2 "drugi": destruktor
  #1 "pierwszy": destruktor

--- Przypisanie w ciele konstruktora ---
  #3 "domyślny": konstruktor
  #4 "domyślny": konstruktor
  początek ciała konstruktora WithBodyAssignment
  #5 "pierwszy": konstruktor
  #3 "pierwszy": przypisanie przenoszące z #5
  #5 "": destruktor
  ...
```

- Lista inicjująca buduje składowe od razu z właściwą wartością. Przypisanie w ciele konstruktora robi to dwa razy:
  najpierw konstruktor domyślny, potem wartość tymczasowa i przypisanie. Składowych `const` i referencji w ten sposób
  w ogóle nie da się ustawić.
- Składowe powstają w kolejności **deklaracji w klasie**, a nie w kolejności na liście inicjującej.
  Niszczone są w kolejności odwrotnej. Kompilator ostrzega o niezgodności (`-Wreorder`), patrz sekcja 10.
- Konstruktor, który można wywołać bez argumentów, jest konstruktorem domyślnym, także gdy ma parametry
  z wartościami domyślnymi (`Label`). Jeśli nie napiszemy żadnego konstruktora, kompilator wygeneruje domyślny.
  Jeśli napiszemy jakikolwiek, nie wygeneruje (zob. tydzień 2, sekcja 5).
- Konstruktor delegujący (`Window()` wywołuje `Window(640, 480)`) pozwala nie powtarzać kodu inicjującego.
- Wartość domyślna składowej (`int frames_ = 0;` i `Noisy a_{"a"};`) jest używana przez każdy konstruktor,
  który nie podaje własnej.
- Ciało destruktora wykonuje się przed zniszczeniem składowych, a ciało konstruktora po ich zbudowaniu.

## 4. Inicjowanie

```bash
./build/04-initialization
```

```text
Noisy b = Noisy("b"):
  #2 "b": konstruktor
Noisy c = a:
  #3 "a": kopiowanie z #1
...
vector(3, 7) ma 3 elementy, vector{3, 7} ma 2
  Stack(size, value)
  Stack(initializer_list)
rozmiary: 3 i 2
int truncated = 3.9 daje 3
```

- `Noisy b = Noisy("b");` nie kopiuje: od C++17 obiekt powstaje od razu w `b`. Zapis `Noisy c = a;` i `Noisy c(a);`
  to w tym przypadku to samo, bo `a` jest tego samego typu (jedna kopia). Różnica między zapisami `T x = y;` i `T x(y);`
  ujawnia się dopiero przy konstruktorach `explicit` (sekcja 6).
- Klamry wybierają w pierwszej kolejności konstruktor z `std::initializer_list`, dlatego `vector{3, 7}` to dwa
  elementy, a `vector(3, 7)` to trzy siódemki. To najczęstsza pułapka przy przejściu na klamry.
- Klamry zabraniają zawężania (`int{3.9}` jest błędem kompilacji), a znak `=` je dopuszcza (`int x = 3.9;` daje 3).
- Puste klamry (`int zero{}`, `Point origin{}`) dają wartość zerową. Zmienna zadeklarowana bez inicjatora
  (`int x;`) ma wartość nieokreśloną, a jej odczyt to zachowanie niezdefiniowane.
- Struktury można inicjować wprost (`Point{1, 2}`), a w C++20 także z nazwami pól (`Point{.x = 5, .y = 6}`),
  co razem z wartościami domyślnymi pól (`Config`) daje czytelne ustawienia opcji.
- `auto x = {5}` ma typ `std::initializer_list<int>`, a `auto x{5}` ma typ `int`.
- Pusty nawias okrągły przy deklaracji (`std::string text();`) to deklaracja funkcji, nie obiektu
  (ang. most vexing parse). Zob. sekcja 10.

## 5. `const`

```bash
./build/05-const
```

```text
--- Wybór przeciążenia ---
  text() bez const
frozen.text():
  text() const
  stały
std::as_const(editable).text():
  text() const
  zmienialny!
...
--- mutable ---
odczytów frozen: 2
--- Składowe const i referencje ---
excerpt: abcd
po zmianie źródła: ZMIE
```

- Metoda oznaczona `const` obiecuje nie zmieniać obiektu i tylko takie metody można wywołać na obiekcie `const`
  oraz przez `const&`. Obie wersje `text()` mogą istnieć jednocześnie: kompilator wybiera ją po `const`
  obiektu. `std::as_const` pozwala wymusić wersję `const` na zwykłym obiekcie.
- `mutable` oznacza składową, którą wolno zmieniać także w metodach `const`. Stosujemy ją do rzeczy niewidocznych
  dla użytkownika klasy (liczniki, pamięć podręczna), a nie do obchodzenia `const`.
- Składowe `const` i referencje trzeba zainicjować na liście inicjującej, a klasa przestaje mieć operator przypisania
  (`static_assert(!std::is_copy_assignable_v<Excerpt>)`). `Excerpt` pokazuje też, że referencja widzi późniejszą zmianę
  napisu, do którego się odnosi. Nie wolno jej jednak powiązać z obiektem, który zniknie wcześniej (sekcja 7).
- `const` przy parametrze przekazywanym przez wartość nie zmienia interfejsu funkcji. Sensowne jest dopiero `const&`.

## 6. Konwersje

```bash
./build/06-conversions
```

```text
--- Konstruktor jednoargumentowy ---
  Meters(5.5)
walk(100):
  Meters(100)
  walk: 100 m
...
double: 0.5, int: 0, half + 1 = 1.5
if (valid): tak, if (invalid): nie
static_cast<bool>(valid) = true
```

- Konstruktor wywoływalny z jednym argumentem, jeśli nie jest `explicit`, definiuje **niejawną konwersję** z typu
  argumentu na typ klasy. Wywołanie `walk(100)` działa, bo `int` przechodzi w `double` (konwersja standardowa),
  a `double` w `Meters` (konwersja zdefiniowana przez użytkownika).
- W jednym ciągu konwersji może wystąpić **co najwyżej jedna konwersja zdefiniowana przez użytkownika**.
  Dlatego `greet("Ala")` nie działa dla `Name(const std::string&)`: `const char*` -> `std::string` to pierwsza
  konwersja, `std::string` -> `Name` druga. Zob. sekcja 10.
- `explicit` przy konstruktorze blokuje niejawne konwersje: `Seconds s = 5;` i `wait(10)` się nie kompilują,
  a `Seconds s(5)` i `Seconds{10}` tak. Dobry domyślny wybór dla konstruktorów jednoargumentowych.
- Operator konwersji (`operator double() const`) działa w drugą stronę: obiekt można użyć jak `double`.
  Skutki bywają zaskakujące (`half + 1` to nagle liczba, `int as_int = half` obcina do 0), więc stosuj go oszczędnie.
- `explicit operator bool()` działa w warunkach (`if`, `!`, `&&`, `||`, `?:`) i w `static_cast<bool>`,
  ale nie w `bool b = handle;`. Tak poprawiono w C++11 stary idiom safe bool (czytanka uzupełniająca).
- Operator konwersji jest `const`, bo konwertowanie obiektu nie powinno go zmieniać i musi działać na obiektach `const`.

## 7. Wartości tymczasowe

```bash
./build/07-temporaries
```

```text
--- Tymczasowy obiekt żyje do końca pełnego wyrażenia ---
  #1 "tymczasowy": konstruktor
  używam tymczasowy
  #1 "tymczasowy": destruktor
po średniku

--- Wiązanie z const& przedłuża życie do końca zasięgu referencji ---
  #3 "przedłużony": konstruktor
  w bloku nadal istnieje: przedłużony
  #3 "przedłużony": destruktor
po bloku
```

- Wartość tymczasowa (np. wynik funkcji zwracającej przez wartość) żyje do końca **pełnego wyrażenia**, czyli zwykle
  do średnika. Można więc bezpiecznie użyć jej w tym samym wyrażeniu (`make("abcdef").label().size()`).
- Wiązanie wartości tymczasowej z lokalną referencją `const T&` (lub `T&&`) **przedłuża jej życie** do końca zasięgu
  tej referencji. Dlatego przekazanie stałej przez `const&` nie tworzy wiszącej referencji.
- Przedłużenie życia działa tylko przy bezpośrednim wiązaniu. Jeśli tymczasowy argument przejdzie przez funkcję
  zwracającą referencję (`first_of`), a wynik zapiszemy w referencji, to po średniku wskazuje ona na zniszczony obiekt.
  Przykład jest w [broken/dangling-reference.cpp](broken/dangling-reference.cpp).
- To samo dotyczy referencji będących składowymi klasy: wiązanie z parametrem konstruktora, który jest tymczasowy,
  nie przedłuża życia:

  ```cpp
  Excerpt excerpt("abcdef", 3); // Niepoprawne: "abcdef" to tymczasowy std::string, znika po średniku.
  ```
- Zwracanie obiektu z funkcji przez wartość zwykle nie kosztuje kopii: wartość tymczasową kompilator buduje od razu
  w miejscu docelowym (od C++17 to obowiązek), a zmienną lokalną często też (NRVO).

## 8. Operatory i `<=>`

```bash
./build/08-operators
```

```text
1.2.3 vs 1.2.4: < !=
1.10.0 vs 1.9.9: > !=
2.0.0 vs 2.0.0: ==
posortowane: 1.9.9 1.10.0 2.0.0
kolejka: [kopia zapasowa] [naprawa awarii] [sprzątanie]
NaN < 1: false, NaN > 1: false, NaN == NaN: false
cena + 50 gr: 20,49 zł, 50 gr + cena: 20,49 zł
++counter daje 1, counter++ daje 1, teraz 2
```

- `auto operator<=>(const Version&) const = default;` generuje porównanie leksykograficzne po kolejnych składowych
  i zarazem `==`. Z niego kompilator zapisuje `<`, `<=`, `>`, `>=`, a z `==` także `!=`.
  Wystarczy to do `std::sort` i do `std::set`.
- Własny `<=>` (klasa `Task`) pozwala ustalić inny porządek, tu: większy priorytet idzie pierwszy. Własny `<=>` **nie**
  generuje `==`, więc dopisujemy go osobno. Pilnujemy, żeby oba były spójne: remisy rozstrzygamy nazwą,
  a `==` porównuje wszystkie składowe.
- Typ wyniku `<=>` mówi o rodzaju porządku: `std::strong_ordering` (równe elementy są nieodróżnialne),
  `std::weak_ordering`, `std::partial_ordering` (są pary nieporównywalne). Dla `double` jest to ten ostatni,
  bo `NaN` nie jest ani mniejsze, ani większe, ani równe.
- Operator dwuargumentowy napisany jako zwykła funkcja (`operator+(Money, const Money&)`) przepuszcza przez konwersje
  oba argumenty, więc działa też `50 + price`. Jako metoda działałby tylko z obiektem po lewej stronie.
- `operator<<` do wypisywania piszemy zwykle jako funkcję niebędącą metodą klasy, zwracającą strumień przez referencję.
- Przedrostkowe `++x` zwraca referencję do zmienionego obiektu, a przyrostkowe `x++` kopię sprzed zmiany,
  więc jest droższe. Dlatego dla iteratorów i licznika w pętli wolimy `++x`.

## 9. `consteval` i `constinit`

```bash
./build/09-consteval-constinit
```

```text
limit = 16, counter = 9
po ++counter: 10

--- Gdzie wykonuje się funkcja ---
constexpr const char* z where(): kompilacji
zwykła zmienna z where(): działania programu
square(runtime_value) = 49
```

- Funkcja `constexpr` może zostać wykonana w czasie kompilacji (gdy jest tego wymagane i argumenty są stałe) lub
  w czasie działania programu (`std::is_constant_evaluated()` pozwala to rozróżnić).
- Funkcja `consteval` musi być wykonana w czasie kompilacji: wywołanie jej z wartością niestałą jest błędem
  ([broken/consteval-runtime-value.cpp](broken/consteval-runtime-value.cpp)).
- `constexpr` na zmiennej oznacza także `const`. `constinit` wymaga tylko, żeby inicjowanie odbyło się
  w czasie kompilacji (bez problemów z kolejnością inicjowania zmiennych globalnych), a zmienną nadal można zmieniać.
  Kolejność inicjowania obiektów globalnych omawia też [temat 2](../../subject-2/week-2/README.md) (sekcja 5).
- Klasy `constexpr` i obiekty w czasie kompilacji są w tygodniu 2, sekcja 6.

## 10. Celowo błędne warianty (`broken/`)

```bash
make broken
```

Polecenie kompiluje po kolei każdy plik z katalogu `broken/`. Błędy kompilacji są tu oczekiwane,
więc `make` nie przerywa pracy. Pliki, które się skompilują, trafiają do `build/broken/`.

| Plik | Czego się spodziewać |
| --- | --- |
| [private-access.cpp](broken/private-access.cpp) | Błąd: `'int Account::balance_' is private within this context`. |
| [enum-class-to-int.cpp](broken/enum-class-to-int.cpp) | Błąd: `cannot convert 'Scale' to 'int' in initialization`. |
| [member-init-order.cpp](broken/member-init-order.cpp) | Ostrzeżenia `-Wreorder` i `-Wuninitialized`. Program się uruchamia i wypisuje nieokreślone wartości. |
| [narrowing.cpp](broken/narrowing.cpp) | Błąd: `narrowing conversion of '3.9' from 'double' to 'int'`. |
| [vexing-parse.cpp](broken/vexing-parse.cpp) | Ostrzeżenie `-Wvexing-parse`: puste nawiasy zostały uznane za deklarację funkcji. |
| [const-method.cpp](broken/const-method.cpp) | Dwa błędy: `passing 'const ...' as 'this' argument discards qualifiers`. |
| [explicit-constructor.cpp](broken/explicit-constructor.cpp) | Błędy: `conversion from 'int' to non-scalar type 'Seconds' requested` i `could not convert '10' from 'int' to 'Seconds'`. |
| [two-user-conversions.cpp](broken/two-user-conversions.cpp) | Błąd: `invalid initialization of reference of type 'const Name&' from expression of type 'const char [4]'`. |
| [dangling-reference.cpp](broken/dangling-reference.cpp) | Ostrzeżenie `-Wdangling-reference`, a po uruchomieniu `AddressSanitizer: heap-use-after-free`. |
| [consteval-runtime-value.cpp](broken/consteval-runtime-value.cpp) | Błąd: `the value of 'runtime_value' is not usable in a constant expression`. |

Uruchomienie wariantów, które się skompilowały:

```bash
./build/broken/member-init-order
./build/broken/dangling-reference
./build/broken/vexing-parse
```

Przy `dangling-reference` AddressSanitizer pokazuje stos wywołań i miejsce, w którym pamięć została zwolniona.
Bez niego ten sam program może wypisać poprawny wynik, co jest groźniejsze od awarii.

## Program `rational.cc` z Moodle

Do tego tygodnia należy też program `rational.cc` (zasób ,,Przykład'' w Temacie 3 na Moodle). Wypisuje komunikaty
podobne do `Noisy`, a na początku pliku zawiera pytania. Warto go uruchomić po przerobieniu sekcji 1 do 7 i spróbować
odpowiedzieć, zanim przeczytasz wyjaśnienia w komentarzach.

## Do omówienia na zajęciach

- Czym różni się przekazanie `Noisy` przez wartość, przez `const&` i przez `&`? Kiedy każde z nich?
- Dlaczego `vector(3, 7)` i `vector{3, 7}` to różne wektory? Kiedy używać klamer?
- Co zmieni się w sekcji 3, jeśli zamienimy kolejność deklaracji składowych `first_` i `second_`?
- Dlaczego składowych `const` i referencji nie można ustawić w ciele konstruktora?
- Kiedy konstruktor jednoargumentowy ma być `explicit`? Czy `explicit` stosować domyślnie?
- Co się stanie z `const std::string& r = std::string("abc");`, a co z `const char* p = std::string("abc").c_str();`?
- Dlaczego własny `<=>` nie wystarcza do `==` i czemu powinny być spójne?
- Co zyskujemy na `consteval` w porównaniu z `constexpr`, a co na `constinit` w porównaniu z `constexpr`?
