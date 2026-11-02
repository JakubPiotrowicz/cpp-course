// Operatory: wypisywanie, dodawanie, ++ w dwóch wersjach oraz porównania z <=> (C++20).
#include <algorithm>
#include <compare>
#include <iostream>
#include <limits>
#include <set>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// Wystarczy jeden zapis, żeby dostać ==, !=, <, <=, > i >=. Porównanie jest leksykograficzne:
// po kolei major, minor, patch, w kolejności deklaracji składowych.
struct Version {
    int major;
    int minor;
    int patch;

    auto operator<=>(const Version&) const = default;
};

std::ostream& operator<<(std::ostream& out, const Version& version) {
    return out << version.major << '.' << version.minor << '.' << version.patch;
}

void compare(const Version& left, const Version& right) {
    std::cout << left << " vs " << right << ":";
    std::cout << (left < right ? " <" : "") << (left > right ? " >" : "") << (left == right ? " ==" : "")
              << (left != right ? " !=" : "") << '\n';
}

// Własny operator <=>: zadania o większym priorytecie są "mniejsze", czyli idą pierwsze.
// operator== porównuje wszystkie składowe, więc jest spójny z <=>, który rozstrzyga remisy nazwą.
class Task {
public:
    Task(int priority, std::string name) : priority_(priority), name_(std::move(name)) {}

    std::strong_ordering operator<=>(const Task& other) const {
        if (auto by_priority = other.priority_ <=> priority_; by_priority != 0) {
            return by_priority;
        }
        return name_ <=> other.name_;
    }

    bool operator==(const Task&) const = default;

    const std::string& name() const {
        return name_;
    }

private:
    int priority_;
    std::string name_;
};

// Dla double wynik porównania to std::partial_ordering: wartości mogą być nieporównywalne (NaN).
struct Measurement {
    double value;

    auto operator<=>(const Measurement&) const = default;
};

static_assert(std::is_same_v<decltype(Measurement{} <=> Measurement{}), std::partial_ordering>);

class Money {
public:
    Money(long long cents) : cents_(cents) {} // Niejawna konwersja z liczby groszy.

    Money& operator+=(const Money& other) {
        cents_ += other.cents_;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Money& money) {
        return out << money.cents_ / 100 << ',' << (money.cents_ % 100 < 10 ? "0" : "") << money.cents_ % 100
                   << " zł";
    }

private:
    long long cents_;
};

// Operator dwuargumentowy jako funkcja niebędąca metodą: obie strony przechodzą te same konwersje,
// więc działa zarówno money + 50, jak i 50 + money.
Money operator+(Money left, const Money& right) {
    left += right;
    return left;
}

class Counter {
public:
    Counter& operator++() { // Przedrostkowy: zwiększa i zwraca ten sam obiekt.
        ++value_;
        return *this;
    }

    Counter operator++(int) { // Przyrostkowy: zwraca kopię sprzed zmiany, więc jest droższy.
        Counter before = *this;
        ++value_;
        return before;
    }

    int value() const {
        return value_;
    }

private:
    int value_ = 0;
};

int main() {
    std::cout << "--- Domyślny <=> ---\n";
    compare({1, 2, 3}, {1, 2, 4});
    compare({1, 10, 0}, {1, 9, 9});
    compare({2, 0, 0}, {2, 0, 0});

    std::vector<Version> versions = {{2, 0, 0}, {1, 10, 0}, {1, 9, 9}};
    std::sort(versions.begin(), versions.end()); // Korzysta z operator< wygenerowanego z <=>.
    std::cout << "posortowane:";
    for (const Version& version : versions) {
        std::cout << ' ' << version;
    }
    std::cout << '\n';

    std::cout << "\n--- Własny <=> i zbiór uporządkowany ---\n";
    std::set<Task> queue;
    queue.insert(Task(1, "sprzątanie"));
    queue.insert(Task(5, "naprawa awarii"));
    queue.insert(Task(5, "kopia zapasowa"));
    std::cout << "kolejka:";
    for (const Task& task : queue) {
        std::cout << " [" << task.name() << ']';
    }
    std::cout << '\n';

    std::cout << "\n--- Porządek częściowy: NaN ---\n";
    Measurement nan{std::numeric_limits<double>::quiet_NaN()};
    Measurement one{1.0};
    std::cout << std::boolalpha << "NaN < 1: " << (nan < one) << ", NaN > 1: " << (nan > one)
              << ", NaN == NaN: " << (nan == nan) << '\n';

    std::cout << "\n--- Operatory arytmetyczne ---\n";
    Money price(1999);
    std::cout << "cena + 50 gr: " << price + 50 << ", 50 gr + cena: " << 50 + price << '\n';

    Counter counter;
    int after = (++counter).value();
    int before = (counter++).value();
    std::cout << "++counter daje " << after << ", counter++ daje " << before << ", teraz " << counter.value()
              << '\n';
}
