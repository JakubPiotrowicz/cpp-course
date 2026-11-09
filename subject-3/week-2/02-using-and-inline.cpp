// Aliasy typów (typedef i using) oraz funkcje i zmienne inline.
#include <array>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

typedef unsigned long Id; // Starszy zapis: nowa nazwa na końcu.
using Index = unsigned long; // Nowszy zapis: nowa nazwa po lewej, jak przypisanie.

typedef int (*OldStyleOperation)(int, int);
using Operation = int (*)(int, int); // Ten sam typ (wskaźnik do funkcji), ale czytelniej.

using Row = std::array<int, 3>;

// Alias nie tworzy nowego typu, tylko drugą nazwę. Kompilator nie odróżni Id od Index.
static_assert(std::is_same_v<Id, Index>);
static_assert(std::is_same_v<OldStyleOperation, Operation>);

// Aliasy w klasie ukrywają szczegóły reprezentacji. Dzięki begin() i end() klasę można przeglądać pętlą.
class Playlist {
public:
    using Track = std::string;
    using Tracks = std::vector<Track>;
    using const_iterator = Tracks::const_iterator;

    void add(Track track) {
        tracks_.push_back(std::move(track));
    }

    const_iterator begin() const {
        return tracks_.begin();
    }

    const_iterator end() const {
        return tracks_.end();
    }

private:
    Tracks tracks_;
};

// inline pozwala umieścić definicję w nagłówku i dołączyć ją do wielu plików .cpp
// bez błędu "multiple definition". Nie jest to polecenie wstawiania kodu w miejscu wywołania.
inline int twice(int value) {
    return 2 * value;
}

inline constexpr int max_users = 8; // Zmienna inline: jedna na cały program, mimo definicji w nagłówku.
inline int visits = 0;

int add(int left, int right) {
    return left + right;
}

int main() {
    std::cout << "--- typedef i using ---\n";
    Id id = 42;
    Index index = id; // To ten sam typ, więc nie ma konwersji.
    std::cout << "id = " << id << ", index = " << index << '\n';

    Operation operation = add;
    std::cout << "operation(2, 3) = " << operation(2, 3) << '\n';

    Row row = {1, 2, 3};
    std::cout << "row ma " << row.size() << " elementy\n";

    Playlist playlist;
    playlist.add("pierwszy");
    playlist.add("drugi");
    std::cout << "playlista:";
    for (const Playlist::Track& track : playlist) {
        std::cout << ' ' << track;
    }
    std::cout << '\n';

    std::cout << "\n--- inline ---\n";
    ++visits;
    ++visits;
    std::cout << "twice(21) = " << twice(21) << ", max_users = " << max_users << ", visits = " << visits << '\n';
}
