# Temat 1, tydzień 2 - iteratory i algorytmy

Przegląd całego tematu i zestawienie z czytankami: [../README.md](../README.md).
Lista czytanek: [../czytanki.md](../czytanki.md) (Koenig i Moo, Plauger, lista algorytmów, `sort`, `stable_sort`, `lower_bound`, `upper_bound`).
Tydzień 1 ([../week-1/](../week-1/)) dotyczy kompilatora, napisów, strumieni i kontenerów.

## Uruchomienie

```bash
cd subject-1/week-2
make                 # buduje wszystkie przykłady
make run             # uruchamia je po kolei
```

Pliki wynikowe trafiają do ignorowanego przez Git katalogu `build/`, a `make clean` go usuwa.
Czytaj ten plik po kolei, a przy każdej sekcji zajrzyj do wskazanego pliku `.cpp`. Katalog [broken/](broken/)
zawiera program, który ma się źle zachowywać; buduje go osobno `make broken`, patrz sekcja 3.
Wymagane: `g++` w wersji obsługującej C++20 i GNU Make. Przykłady nie czytają danych z klawiatury.

| Przykład | Plik | Zagadnienie |
| --- | --- | --- |
| 1 | [01-iterators.cpp](01-iterators.cpp) | Iteratory, zakresy, kategorie, unieważnianie. |
| 2 | [02-for-each-transform.cpp](02-for-each-transform.cpp) | `for_each`, `transform`, `count_if`, `find_if`, `accumulate`, lambdy. |
| 3 | [03-copy-inserters.cpp](03-copy-inserters.cpp) | `copy` i `back_inserter`, `front_inserter`, `inserter`. |
| 4 | [04-sort.cpp](04-sort.cpp) | `sort`, `stable_sort`, własne porównania. |
| 5 | [05-bounds.cpp](05-bounds.cpp) | `lower_bound`, `upper_bound`, `equal_range`, `binary_search`. |
| 6 | [06-merge.cpp](06-merge.cpp) | `inplace_merge`, `merge` i sortowanie przez scalanie. |
| 7 | [07-erase-remove.cpp](07-erase-remove.cpp) | `remove_if` z `erase`, `erase_if`, `unique`. |
| 8 | [08-regex.cpp](08-regex.cpp) | Dodatkowo: `regex_match`, `regex_search`, `sregex_iterator`, `regex_replace`. |

## 1. Iteratory

```bash
./build/01-iterators
```

```text
10 20 30 40 50 
50 40 30 20 10 
! d l r o W   , o l l e H 
3 2 1 
*cit = 10
*(begin + 2) = 30
distance = 5
*next(l.begin(), 2) = 3
a -> 1
b -> 2
następny push_back zrobi realokację: true
po erase pierwszy element to 2
```

- Iterator zachowuje się jak wskaźnik: `*it` odczytuje element, `++it` przechodzi do następnego.
  Zakres to para `[begin, end)`, przy czym `end` wskazuje **za** ostatni element i nie wolno go dereferencjonować.
- Szablon `print_reverse` działa dla `vector`, `string` i `list`, bo wszystkie mają `rbegin()` i `rend()`.
  Algorytmy biblioteki standardowej korzystają z tej samej idei: nie znają kontenera, znają tylko iteratory.
- Kategoria iteratora mówi, co wolno: `vector` ma iterator o dostępie swobodnym (`begin() + 2`),
  `list` dwukierunkowy (tylko `++` i `--`), `forward_list` jednokierunkowy. `static_assert` w pliku sprawdza to w czasie kompilacji.
  Funkcje `std::next`, `std::prev`, `std::advance` i `std::distance` działają dla każdej kategorii, ale dla słabszych iteratorów
  przechodzą po elementach po kolei.
- **Unieważnianie iteratorów:** gdy `vector` zabraknie miejsca, `push_back` przenosi elementy do nowej pamięci
  i wszystkie wcześniej pobrane iteratory, wskaźniki i referencje do elementów przestają być ważne.
  W `list` usunięcie elementu unieważnia tylko iterator do niego. Kiedy dokładnie iteratory tracą ważność,
  opisuje dokumentacja każdego kontenera (sekcja *Iterator validity* w cppreference).

## 2. Algorytmy proste i lambdy

```bash
./build/02-for-each-transform
```

Przed uruchomieniem przewidź wynik `accumulate(v.begin(), v.end(), 0.5)` i zastanów się, od czego zależy typ wyniku.

- Algorytmy przyjmują zakres iteratorów i często wywołanie, które mówi, co zrobić z elementem.
  Najwygodniej podać je jako **wyrażenie lambda**: `[](int x) { return x + 1; }`.
  Nawiasy `[]` to lista przechwytywanych zmiennych: `[limit]` kopiuje, `[&limit]` bierze referencję.
  Lambdy wrócą w temacie 7, tutaj wystarczy ich użycie.
- `for_each` z parametrem `int&` zmienia elementy w miejscu. `transform` zapisuje wynik pod iteratorem podanym
  jako trzeci argument (tu nadpisuje wejście, co jest dozwolone).
- `find_if` zwraca iterator, więc wynik zawsze porównujemy z `end()`.
- `accumulate` jest w `<numeric>`, a nie w `<algorithm>`. Typ wyniku wynika z typu wartości początkowej: `0` to `int`, `0.5` to `double`.
- `minmax_element` zwraca parę iteratorów, rozpakowaną przez wiązanie strukturalne.

## 3. Kopiowanie i iteratory wstawiające

```bash
./build/03-copy-inserters
```

```text
ready: 1 2 3 
b: 4 5 6 1 2 3 
front: 3 2 1 0 
s: 1 2 3 10 
odd: 5 1 3 
```

- Algorytm `copy` **nie zmienia rozmiaru** kontenera, tylko zapisuje pod podany iterator.
  Docelowy zakres musi już istnieć. `back_inserter(b)` jest iteratorem, który przy każdym zapisie wywołuje `b.push_back`,
  więc kontener rośnie sam. Analogicznie działają `front_inserter` (`push_front`) i `inserter` (`insert`).
- `front_inserter` odwraca kolejność wstawianych elementów.
- `ostream_iterator` zapisuje elementy do strumienia, co daje krótki sposób wypisania zakresu.

Osobny plik [broken/copy-to-empty.cpp](broken/copy-to-empty.cpp) zawiera celowo błędny wariant:
kopiowanie do **pustego** wektora przez `begin()`.
Standard nie określa, co się stanie (zachowanie nieokreślone). Narzędzie `AddressSanitizer` ujawnia błąd:

```bash
make broken   # Buduje z -g -fsanitize=address.
./build/broken/copy-to-empty
```

Program kończy się komunikatem `AddressSanitizer: SEGV` ze stosem wywołań prowadzącym do `std::copy`.
Bez `-fsanitize=address` ten sam kod może wyglądać na działający, co jest groźniejsze od awarii.

## 4. Sortowanie

```bash
./build/04-sort
```

- `sort` przyjmuje opcjonalne porównanie: funkcję, która odpowiada, czy pierwszy argument ma stać **przed** drugim.
  Porównanie musi być **ścisłe**: dla równych elementów zwraca `false`. Zapis `a <= b` łamie wymaganie i może zakończyć się
  wyjściem poza zakres albo zawieszeniem programu.
- `sort` nie gwarantuje zachowania kolejności elementów równoważnych, `stable_sort` tak. Przykład ze studentami
  w grupach pokazuje, że po `stable_sort` osoby z jednej grupy zostają w kolejności wejściowej.
- `sort` wymaga iteratorów o dostępie swobodnym, więc dla `list` służy metoda `l.sort()`.

## 5. Wyszukiwanie binarne

```bash
./build/05-bounds
```

Przed uruchomieniem przewidź pozycje zwrócone przez `lower_bound(3)` i `upper_bound(3)` dla `{1, 3, 3, 3, 5, 7}`.

```text
lower_bound(3) na pozycji 1
upper_bound(3) na pozycji 4
trójek: 3
```

- `lower_bound` zwraca pierwszy element **nie mniejszy** od wartości, `upper_bound` pierwszy **większy**.
  Różnica iteratorów to liczba elementów równych wartości. `equal_range` zwraca obie granice naraz.
- Dla brakującej wartości granice wskazują miejsce, w które należałoby ją wstawić.
  To daje wstawianie z zachowaniem porządku: `v.insert(std::lower_bound(...), x)`.
- Zakres **musi być posortowany** tym samym porównaniem. Dla niesortowanych danych wynik jest nieokreślony.
- `set::lower_bound` jest metodą i korzysta z drzewa. Algorytm `std::lower_bound` zadziała dla zbioru, ale nie ma
  dostępu swobodnego, więc przechodzi po elementach liniowo. Dla kontenerów z własną metodą wybieramy metodę.

## 6. Scalanie

```bash
./build/06-merge
```

```text
inplace_merge: 1 2 3 4 5 6
merge: 1 2 3 4 7 8 9
merge_sort: 1 2 3 5 7 8 9
```

- `inplace_merge(first, middle, last)` scala dwa sąsiednie posortowane zakresy w jeden, w tym samym kontenerze.
- `merge` zapisuje wynik w osobnym miejscu, a wejścia zostają bez zmian.
- Funkcja `merge_sort` pokazuje, jak złożyć znany algorytm z `inplace_merge`. Działa dla każdego kontenera z iteratorami dwukierunkowymi.

## 7. Usuwanie elementów

```bash
./build/07-erase-remove
```

```text
size po remove_if: 6, elementów do zachowania: 3
size po erase: 3
erase_if: 1 3 5 
unikalne: 1 2 3 
Ths s n xmpl sntnc.
```

- Algorytm nie zna kontenera, więc **nie potrafi zmienić jego rozmiaru**. `remove_if` przesuwa elementy do zachowania
  na początek i zwraca iterator za nimi. Ogon za nim ma nieokreślone wartości, a `size()` się nie zmienia.
  Dopiero metoda `erase(new_end, end)` usuwa ogon. Ten wzorzec to idiom *erase-remove*.
- Od C++20 `std::erase_if(kontener, predykat)` robi to w jednym wywołaniu.
- Czytanka Suttera (Item 2, ,,What remove() Removes'') pokazuje, że `remove(v.begin(), v.end(), 3)` bez `erase`
  jest po cichu błędne, i zadaje pytanie o predykat ze stanem (`FlagNth`, który zlicza wywołania).
  Algorytm może skopiować predykat, więc nie należy zakładać, że działa on na jednym, wspólnym liczniku.
- `unique` usuwa tylko **sąsiadujące** powtórzenia, więc przed usuwaniem duplikatów dane trzeba posortować.
  Po `unique` również potrzebne jest `erase`.

## 8. Dodatkowo: wyrażenia regularne

```bash
./build/08-regex
```

```text
regex_match("2026-11-02"): true
regex_match("2026-11-02 r."): false
pierwsza data: 2026-11-15 (pozycja 8), rok 2026
wszystkie daty: 2026-11-15 2026-12-20
Termin: 15.11.2026, poprawka: 20.12.2026.
```

Ten przykład jest dodatkowy: czytanki wymieniają `regex` jako rzecz, która może się przydać.

- `regex_match` wymaga dopasowania całego napisu, `regex_search` szuka fragmentu. Wynik z grupami trafia do `smatch`.
- `smatch` wskazuje na fragmenty napisu wejściowego, więc napis musi istnieć, dopóki używamy wyniku
  (przekazanie tymczasowego `std::string` do `regex_search` jest zablokowane przy kompilacji).
- `sregex_iterator` przechodzi po wszystkich dopasowaniach jak zwykły iterator. To kolejne zastosowanie iteratorów z przykładu 1.
- Literał surowy `R"(...)"` oszczędza podwajania ukośników we wzorcach.
- Obiekt `std::regex` kompiluje wzorzec w czasie działania programu, a samo dopasowywanie jest zwykle wolne.
  Nie twórz go wielokrotnie w pętli i nie używaj do przetwarzania dużych danych.

## Do omówienia na zajęciach

- Dlaczego algorytmy biblioteki działają na iteratorach, a nie na kontenerach? Co to daje i co utrudnia?
- Które operacje na `vector` unieważniają iteratory? Jak napisać pętlę, która usuwa elementy w trakcie przechodzenia?
- Kiedy `std::copy`, a kiedy `std::back_inserter`? Co zrobić, gdy znamy docelowy rozmiar?
- Jak sprawdzić, że porównanie przekazane do `sort` jest poprawne?
- Jaka jest złożoność `lower_bound` dla `vector`, a jaka dla `list`? Co z `set`?
