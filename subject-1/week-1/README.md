# Temat 1, tydzień 1 - kompilator, napisy, strumienie i kontenery

Przegląd całego tematu i zestawienie z czytankami: [../README.md](../README.md).
Lista czytanek: [../czytanki.md](../czytanki.md). Tydzień 2 ([../week-2/](../week-2/)) dotyczy iteratorów i algorytmów.

## Uruchomienie

Z głównego katalogu repozytorium przejdź do katalogu z przykładami:

```bash
cd subject-1/week-1
make                 # buduje wszystkie przykłady
make run             # uruchamia je po kolei
```

Wszystkie dalsze polecenia wykonuj z katalogu `week-1`.
Czytaj ten plik po kolei, a przy każdej sekcji zajrzyj do wskazanego pliku `.cpp`. Katalog [broken/](broken/)
zawiera programy, które mają się źle zachowywać (ostrzeżenia, błąd); buduje je osobno `make broken`, patrz sekcja 0.
Wymagane: `g++` w wersji obsługującej C++20 (sprawdź: `g++ --version`) i GNU Make.
Pliki wynikowe trafiają do ignorowanego przez Git katalogu `build/`, a `make clean` go usuwa.

| Przykład | Plik | Zagadnienie |
| --- | --- | --- |
| 0 | [00-hello.cpp](00-hello.cpp) | Budowa programu, uruchamianie kompilatora, ostrzeżenia, kod wyjścia. |
| 1 | [01-io.cpp](01-io.cpp) | `cin`, `cout`, `cerr`, `getline`, stan strumienia. |
| 2 | [02-string-basics.cpp](02-string-basics.cpp) | `std::string`: dostęp, wyszukiwanie, porównania, modyfikacje. |
| 3 | [03-string-params.cpp](03-string-params.cpp) | Przekazywanie napisów: wartość, `const&`, `string_view`. |
| 4 | [04-reserve.cpp](04-reserve.cpp) | Pojemność napisu, `reserve`, `ostringstream`. |
| 5 | [05-sequences.cpp](05-sequences.cpp) | `vector` (pojemność), `deque`, `list`, `array`, `pair`, `tuple`. |
| 6 | [06-associative.cpp](06-associative.cpp) | `map`, `set`, `multiset`, `multimap`. |
| 7 | [07-unordered.cpp](07-unordered.cpp) | `unordered_set`, `unordered_multiset`, `unordered_map`, `unordered_multimap`. |
| 8 | [08-streams.cpp](08-streams.cpp) | `istringstream`, `ostringstream`, `ifstream`, `ofstream`. |
| 9 | [09-utf8.cpp](09-utf8.cpp) | `std::string` to bajty, `wstring`, `u32string`. |

Przykłady 3 i 4 korzystają z [alloc_counter.hpp](alloc_counter.hpp), który zlicza alokacje na stercie.
Dzięki temu widać liczbami, ile kosztuje kopiowanie. Dokładne liczby zależą od implementacji biblioteki
standardowej (podajemy wyniki z `g++` 13 i `libstdc++`), ale wnioski są takie same.

## 0. Pierwszy program i kompilator

```bash
g++ -std=c++20 -Wall -Wextra -Wpedantic 00-hello.cpp -o build/00-hello
./build/00-hello
echo $?
```

Wynik: dwa wiersze tekstu i `0`. `echo $?` pokazuje kod wyjścia ostatniego polecenia.
Zero oznacza sukces. Funkcja `main` jest wyjątkowa: bez `return` kompilator sam dodaje `return 0`.

Flagi, które będą wracały na każdych zajęciach:

| Flaga | Znaczenie |
| --- | --- |
| `-std=c++20` | Wersja języka. |
| `-Wall -Wextra -Wpedantic` | Ostrzeżenia. Warto je czytać i usuwać, a nie ignorować. |
| `-o plik` | Nazwa pliku wynikowego (bez niej powstaje `a.out`). |
| `-O0`, `-O2` | Poziom optymalizacji. Przykłady używają `-O0`, żeby wyniki były przewidywalne. |
| `-g` | Informacje dla debuggera. |

Kompilator wykonuje po kolei kilka kroków. Każdy można zatrzymać i obejrzeć wynik:

```bash
g++ -std=c++20 -E 00-hello.cpp | wc -l          # Sam preprocesor.
g++ -std=c++20 -S 00-hello.cpp -o build/hello.s # Kod w asemblerze.
g++ -std=c++20 -c 00-hello.cpp -o build/hello.o # Plik obiektowy, jeszcze bez łączenia.
```

Pierwsze polecenie wypisuje kilkadziesiąt tysięcy wierszy: `#include <iostream>` wstawia do pliku
całą zawartość nagłówka. Temat 2 omawia osobną kompilację, łączenie i nagłówki dokładniej.

Katalog [broken/](broken/) zawiera dwa osobne programy, które celowo wywołują ostrzeżenie albo błąd wykonania.
`make broken` buduje je do `build/broken/` (nie wchodzą do `make` ani `make run`):

```bash
make broken
./build/broken/hello-exit-code; echo $?
```

[broken/hello-warnings.cpp](broken/hello-warnings.cpp) kompiluje się, ale zgłasza dwa ostrzeżenia: `-Wsign-compare` (porównanie `unsigned` z `-1`: liczba `-1`
zamienia się w ogromną wartość bez znaku, więc `3 < -1` byłoby prawdziwe) i `-Wunused-variable`.
[broken/hello-exit-code.cpp](broken/hello-exit-code.cpp) kończy program kodem `3`, który widać w `echo $?`.

## 1. Wejście i wyjście

Przed uruchomieniem sprawdź, co zrobi `getline` zaraz po `cin >> ...`.

```bash
printf 'Ala 3\nAla ma kota\nostatni wiersz\n' | ./build/01-io
```

```text
cout: zwykłe wyjście.
cerr: komunikaty o błędach.
Imię: Ala, liczba: 3
Reszta pierwszego wiersza: []
Kolejne wiersze:
  [Ala ma kota]
  [ostatni wiersz]
Po końcu danych: eof=1 fail=1
```

- `>>` pomija białe znaki i czyta jedno słowo albo liczbę. Znak nowego wiersza zostaje w strumieniu,
  dlatego pierwszy `getline` zwraca pustą resztę pierwszego wiersza. To częsta pułapka przy mieszaniu `>>` i `getline`.
- `cout` i `cerr` to osobne strumienie. Komunikaty o błędach można ukryć lub zapisać oddzielnie:
  `./build/01-io 2> errors.txt` albo `2>/dev/null`.
- Warunek `while (std::getline(...))` sprawdza stan strumienia po odczycie. Po końcu danych ustawiają się `eof` i `fail`.
- Uruchom program bez potoku i wpisz dane z klawiatury. Koniec danych to Ctrl+D (Linux).

## 2. `std::string`: podstawy

```bash
./build/02-string-basics
```

Przed uruchomieniem przewidź, co zwrócą `rfind("ra")`, `find_last_of("kd")` i `"Z" < "a"`.

- `operator[]` nie sprawdza zakresu, `at()` rzuca `std::out_of_range`.
  Komunikat wyjątku zależy od implementacji, więc nie opieraj na nim programu.
- Wyszukiwanie zwraca indeks albo `std::string::npos` (największa wartość typu `size_t`).
  Wynik trzeba porównać z `npos`, a nie z `-1` ani z zerem.
- Porównania `==`, `<`, `>` są leksykograficzne, bajt po bajcie. Dlatego `"Z" < "a"`.
- `"ab" + "cd"` się nie skompiluje: to dodawanie dwóch wskaźników. Wystarczy, że jeden z operandów jest `std::string`.

## 3. Przekazywanie napisów do funkcji

```bash
./build/03-string-params
```

```text
alokacje:
  by_value(text)          1
  by_value(shorter)       0
  by_const_ref(text)      0
  by_const_ref(literal)   1
  by_view(text)           0
  by_view(literal)        0
part = xxxxx
```

- Przekazanie przez wartość kopiuje napis, a więc dla długiego napisu alokuje pamięć.
- `const std::string&` nie kopiuje, ale gdy przekażemy literał (`const char*`), kompilator **tworzy tymczasowy
  `std::string`** i alokacja wraca.
- `std::string_view` to wskaźnik i długość. Przyjmuje `std::string`, literał i fragment napisu bez kopiowania.
- Krótkie napisy (w `libstdc++` do 15 znaków) mieszczą się w samym obiekcie. Ta optymalizacja nazywa się SSO
  i dlatego przykład używa napisu o długości 40.
- `string_view` nie jest właścicielem danych. Poniższy kod jest **niepoprawny**: tymczasowy `std::string`
  znika po średniku, a `view` wskazuje na zwolnioną pamięć:

  ```cpp
  std::string_view view = std::string("abcdef").substr(1, 3); // Wiszący widok.
  ```
- Do tego, co ma być zmienione w funkcji, służy `std::string&` (bez `const`). Ten temat wraca w temacie 3.

## 4. Pojemność napisu i `reserve`

```bash
./build/04-reserve
```

```text
alokacje przy 10000 dopisaniach:
  zwykle dopisywanie   11
  po reserve           1
  ostringstream        8
capacity na początku: 15
  size = 16, capacity = 30
  size = 31, capacity = 60
  size = 61, capacity = 120
  size = 121, capacity = 240
```

- Napis ma `size()` (ile znaków) i `capacity()` (na ile znaków jest miejsce). Gdy miejsca brakuje,
  zwiększa pojemność (tu dwukrotnie) i przenosi zawartość.
- Dopisywanie 10000 razy po trzy znaki daje tylko kilkanaście alokacji dzięki wzrostowi geometrycznemu.
  `reserve` z góry zmniejsza to do jednej, o ile znamy rozmiar.
- `ostringstream` jest wygodny przy składaniu napisu z różnych typów. Jego `str()` kopiuje wynik, więc nie jest darmowe.

## 5. `vector`, `deque`, `list`, `array`, `pair`, `tuple`

```bash
./build/05-sequences
```

Zwróć uwagę na trzy rzeczy:

- `std::vector<int>(5, 1)` to pięć jedynek, a `std::vector<int>{5, 1}` to dwa elementy: 5 i 1.
- `clear()` usuwa elementy, ale **nie zwalnia pamięci** (`capacity()` zostaje). Prośbę o zwolnienie składa
  `shrink_to_fit()`. Jest niewiążąca, ale w praktyce zwykle wykonywana (przykład wypisuje `capacity = 0`).
- Usuwanie elementów z listy w pętli wymaga zapisania wyniku `erase`: `it = l.erase(it)`.
  Po `erase` stary iterator jest już nieważny.

`vector` trzyma elementy w jednym ciągłym bloku (szybki dostęp przez indeks, wstawianie w środku przesuwa elementy),
`deque` trzyma je w blokach (szybkie wstawianie na początku i końcu, indeks nadal działa, ale nie ma `capacity`
ani `reserve`), `list` trzyma osobne węzły (stałe wstawianie i usuwanie, brak dostępu przez indeks),
`array` ma rozmiar znany w czasie kompilacji.
Czytanka GOTW 54 omawia, kiedy wybrać `vector`, a kiedy `deque`. Standard mówi, że `vector` jest wyborem domyślnym,
a autor czytanki namawia do rozważenia `deque`, jeśli ciągłość pamięci nie jest potrzebna.
`pair` i `tuple` grupują wartości różnych typów. Do rozpakowania służą wiązania strukturalne:
`auto [name, age, height] = t;`.

## 6. Kontenery asocjacyjne uporządkowane

```bash
./build/06-associative
```

Przed uruchomieniem przewidź, ile elementów będzie miała mapa po odczycie `counts["zebra"]`.

- `map` jest uporządkowana po kluczu i przechowuje pary. `operator[]` **wstawia** brakujący klucz z wartością domyślną.
  Do samego sprawdzenia służą `find` i `contains` (od C++20).
- `set` trzyma unikalne elementy, `multiset` dopuszcza powtórzenia. `insert` zwraca parę: iterator i flagę, czy coś dodano.
- `multimap` pozwala, by jeden klucz miał kilka wartości. Nie ma `operator[]`, a wszystkie wpisy o danym kluczu
  daje `equal_range`. Wartości o równych kluczach zostają w kolejności wstawiania.
- Trzeci parametr szablonu zmienia porządek, na przykład `std::greater<int>`.
- Kontenery `flat_set` i `flat_map` (C++23) są wymienione w czytankach, ale na serwerze `students` nie są dostępne.

## 7. Kontenery z haszowaniem

```bash
./build/07-unordered
```

```text
różnych słów: 4, powtórzone: ala ma
ile trójek: 3, elementów: 6
Ela ma 22 lat, elementów: 3
ocen Ali: 2
oceny Ali po sortowaniu: 3 5
load_factor <= max_load_factor: true
```

- Warianty `unordered_set`, `unordered_multiset`, `unordered_map` i `unordered_multimap` mają ten sam interfejs
  co ich uporządkowane odpowiedniki, ale wyszukiwanie jest średnio w stałym czasie.
- **Kolejność elementów jest nieokreślona** i może się zmienić po dodaniu kolejnych (kontener zwiększa liczbę kubełków).
  Nie wolno jej zakładać w programie ani w testach. Przykład kopiuje wartości do wektora i sortuje je przed wypisaniem.
- `insert` zwraca parę z flagą, więc to prosty sposób na wykrywanie powtórzeń w jednym przejściu.
- Własny typ jako klucz wymaga funkcji haszującej. Wróci to w temacie 4 (szablony).
- Wybór: uporządkowane (`map`, `set`), gdy potrzebny jest porządek lub zakresy (`lower_bound`),
  haszowane (`unordered_*`), gdy liczy się szybkie wyszukiwanie po kluczu.

## 8. Strumienie napisowe i plikowe

```bash
./build/08-streams
```

```text
suma = 60, strumień w stanie błędu: 1
pi = 3.142, id = 00042
1: pierwszy wiersz
2: drugi wiersz
nieistniejący plik otwarty: false
```

- `istringstream` czyta z napisu tak jak `cin`. Pętla `while (in >> x)` kończy się na pierwszym tekście, który nie jest liczbą.
- Manipulatory z `<iomanip>` (`setprecision`, `setw`, `setfill`) formatują wyjście. `fixed` ustawia zapis dziesiętny.
- Plik zamyka destruktor strumienia, a blok `{ ... }` w przykładzie pokazuje, że zapis kończy się przy wyjściu z bloku.
  To pierwsza styczność z RAII (temat 5).
- Nieudane otwarcie pliku **nie rzuca wyjątku**. Trzeba sprawdzić `is_open()` albo stan strumienia.

## 9. UTF-8, `wstring` i `u32string`

```bash
./build/09-utf8
```

```text
zażółć: size() = 10 bajtów, 6 znaków
bajty: 7a 61 c5 bc c3 b3 c5 82 c4 87
substr(0, 3) kończy się w połowie znaku, więc nie jest poprawnym UTF-8
wstring: size() = 6, sizeof(wchar_t) = 4
kod trzeciej litery (ż): U+017C
u32string: size() = 6
```

- `std::string` to ciąg bajtów. `size()`, indeksy, `substr` i `find` działają na bajtach, a nie na znakach.
  Litery polskie w UTF-8 zajmują po dwa bajty.
- Dlatego funkcje takie jak `std::toupper` czy odwracanie napisu bajt po bajcie psują tekst spoza ASCII.
- `std::wstring` składa się z `wchar_t`, którego rozmiar zależy od platformy: 4 bajty na Linuksie
  (jeden element to jeden punkt kodowy), 2 bajty w Windows (UTF-16, część znaków zajmuje dwa elementy).
  Do wypisywania służy osobny strumień `wcout`, którego nie wolno swobodnie mieszać z `cout`, więc przykład
  wypisuje tylko rozmiary i kody.
- `std::u32string` ma jeden element na punkt kodowy, ale nie rozwiązuje wszystkiego (znak może składać się z kilku punktów kodowych).
- Do poważnej obróbki tekstu Unicode zalecana jest biblioteka ICU.

## Do omówienia na zajęciach

- Dlaczego `at()` i `operator[]` różnią się zachowaniem i kiedy wybrać które?
- Kiedy `const std::string&`, a kiedy `std::string_view`? Co jest ryzykiem widoku?
- Który kontener wybrać do: kolejki zdarzeń, słownika, zbioru bez powtórzeń, listy z częstym usuwaniem ze środka?
- Kiedy `map`, a kiedy `unordered_map`? Co się traci przy haszowaniu?
- Dlaczego `map::operator[]` nie działa na `const map`?
- Co się stanie, jeśli wczytamy liczbę z tekstu, który nią nie jest, i nie sprawdzimy strumienia?
- Co mówi ostrzeżenie `-Wsign-compare` i dlaczego warto kompilować z `-Wall -Wextra`?
