// Konstruktory: lista inicjująca, kolejność składowych, konstruktor domyślny, delegowanie i destruktor.
#include <iostream>
#include <string>
#include <utility>

#include "../noisy.hpp"

// Składowe inicjujemy na liście inicjującej: od razu powstają z właściwą wartością.
class WithInitList {
public:
    explicit WithInitList(const std::string& name) : first_("pierwszy"), second_(name) {
        std::cout << "  ciało konstruktora WithInitList\n";
    }

private:
    Noisy first_; // Składowe powstają w kolejności deklaracji,
    Noisy second_; // a nie w kolejności zapisu na liście inicjującej.
};

// Przypisanie w ciele konstruktora: składowe najpierw powstają jako domyślne,
// a dopiero potem dostają wartość. To praca dwa razy, a dla składowych const lub referencji nie zadziała.
class WithBodyAssignment {
public:
    explicit WithBodyAssignment(const std::string& name) {
        std::cout << "  początek ciała konstruktora WithBodyAssignment\n";
        first_ = Noisy("pierwszy");
        second_ = Noisy(name);
    }

private:
    Noisy first_;
    Noisy second_;
};

// Konstruktor, który można wywołać bez argumentów, jest konstruktorem domyślnym,
// także wtedy, gdy ma parametry z wartościami domyślnymi.
class Label {
public:
    explicit Label(std::string text = "(brak)") : text_(std::move(text)) {}

    const std::string& text() const {
        return text_;
    }

private:
    std::string text_;
};

// Konstruktor delegujący wywołuje inny konstruktor tej samej klasy.
// Składowa frames_ dostaje wartość domyślną z deklaracji.
class Window {
public:
    Window() : Window(640, 480) {}

    Window(int width, int height) : width_(width), height_(height) {
        std::cout << "  Window " << width_ << "x" << height_ << ", klatki: " << frames_ << '\n';
    }

private:
    int width_;
    int height_;
    int frames_ = 0;
};

// Ciało destruktora wykonuje się przed zniszczeniem składowych. Składowe znikają w odwrotnej kolejności.
class Owner {
public:
    Owner() {
        std::cout << "  Owner: ciało konstruktora, składowe już istnieją\n";
    }

    ~Owner() {
        std::cout << "  Owner: ciało destruktora, składowe jeszcze istnieją\n";
    }

private:
    Noisy a_{"a"};
    Noisy b_{"b"};
};

int main() {
    std::cout << "--- Lista inicjująca ---\n";
    {
        WithInitList object("drugi");
        std::cout << "  koniec bloku\n";
    }

    std::cout << "\n--- Przypisanie w ciele konstruktora ---\n";
    {
        WithBodyAssignment object("drugi");
        std::cout << "  koniec bloku\n";
    }

    std::cout << "\n--- Konstruktor domyślny z parametrem domyślnym ---\n";
    Label unnamed;
    Label named("własna");
    std::cout << unnamed.text() << ", " << named.text() << '\n';

    std::cout << "\n--- Konstruktor delegujący ---\n";
    Window standard;
    Window wide(1280, 720);

    std::cout << "\n--- Destruktor i kolejność niszczenia ---\n";
    {
        Owner owner;
        std::cout << "  koniec bloku\n";
    }
}
