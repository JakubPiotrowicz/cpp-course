// Const-poprawność: metody const, przeciążanie po const, składowe const i referencje, mutable.
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

class Document {
public:
    explicit Document(std::string text) : text_(std::move(text)) {}

    std::size_t length() const {
        return text_.size();
    }

    // Dwie wersje metody: dla obiektów const i dla pozostałych.
    const std::string& text() const {
        std::cout << "  text() const\n";
        ++reads_;
        return text_;
    }

    std::string& text() {
        std::cout << "  text() bez const\n";
        return text_;
    }

    std::size_t reads() const {
        return reads_;
    }

private:
    std::string text_;
    // mutable: licznik odczytów nie jest częścią logicznego stanu dokumentu,
    // więc metody const mogą go zmieniać.
    mutable std::size_t reads_ = 0;
};

// Składowe const i referencje trzeba zainicjować na liście inicjującej.
// Taka klasa nie ma operatora przypisania, bo nie da się przypisać do składowej const ani przestawić referencji.
class Excerpt {
public:
    Excerpt(const std::string& source, std::size_t limit) : source_(source), limit_(limit) {}

    std::string text() const {
        return source_.substr(0, limit_);
    }

private:
    const std::string& source_;
    const std::size_t limit_;
};

static_assert(std::is_copy_constructible_v<Excerpt>);
static_assert(!std::is_copy_assignable_v<Excerpt>);

// Przez const& można wywołać tylko metody const.
void show(const Document& document) {
    const std::string& text = document.text();
    std::cout << "  show: " << document.length() << " znaków, tekst: " << text << '\n';
}

int main() {
    Document editable("zmienialny");
    const Document frozen("stały");

    std::cout << "--- Wybór przeciążenia ---\n";
    editable.text() += "!"; // Wersja bez const zwraca referencję, którą można zmienić.
    std::cout << "frozen.text():\n";
    const std::string& from_frozen = frozen.text();
    std::cout << "  " << from_frozen << '\n';
    std::cout << "std::as_const(editable).text():\n";
    const std::string& from_editable = std::as_const(editable).text();
    std::cout << "  " << from_editable << '\n';

    std::cout << "\n--- Przekazanie przez const& ---\n";
    show(editable);
    show(frozen);

    std::cout << "\n--- mutable ---\n";
    std::cout << "odczytów frozen: " << frozen.reads() << '\n';

    std::cout << "\n--- Składowe const i referencje ---\n";
    std::string source = "abcdefghij";
    Excerpt excerpt(source, 4);
    std::cout << "excerpt: " << excerpt.text() << '\n';
    source = "ZMIENIONE";
    std::cout << "po zmianie źródła: " << excerpt.text() << '\n';
}
