// Błąd kompilacji: makro zastępuje każdą nazwę o tym samym brzmieniu. Zob. README, sekcja 2.
#define count 5

struct Stats {
    int count; // Błąd: po podstawieniu powstaje "int 5;".
};

int main() {
    Stats stats{1};
    return stats.count;
}
