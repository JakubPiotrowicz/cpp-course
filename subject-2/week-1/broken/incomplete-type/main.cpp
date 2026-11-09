// Błąd kompilacji: pole typu niepełnego. Zob. README, sekcja 3.
struct Node; // Deklaracja zapowiadająca: kompilator zna nazwę, ale nie zna rozmiaru ani pól.

struct Link {
    Node* target; // Wskaźnik wystarcza: jego rozmiar nie zależy od Node.
};

struct Broken {
    Node target; // Błąd: pole musi być pełnego typu, bo kompilator musi znać rozmiar Broken.
};

int main() {
    Link link{nullptr};
    return link.target == nullptr ? 0 : 1;
}
