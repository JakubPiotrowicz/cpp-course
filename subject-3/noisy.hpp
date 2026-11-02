// Klasa pomocnicza do przykładów tematu 3. Każda operacja specjalna wypisuje komunikat,
// więc widać, kiedy obiekt powstaje, jest kopiowany, przenoszony i niszczony.
// Zapis #3 to numer obiektu (nadawany przy tworzeniu), a w cudzysłowie jest etykieta.
// Ten sam plik współdzielą oba tygodnie, dlatego leży o poziom wyżej.
#pragma once

#include <iostream>
#include <string>
#include <utility>

class Noisy {
public:
    Noisy() : Noisy("domyślny") {}

    explicit Noisy(std::string label) : id_(++last_id_), label_(std::move(label)) {
        log("konstruktor");
    }

    Noisy(const Noisy& other) : id_(++last_id_), label_(other.label_) {
        log("kopiowanie z #" + std::to_string(other.id_));
    }

    // Po przeniesieniu obiekt źródłowy ma pustą etykietę. To widać w jego destruktorze.
    Noisy(Noisy&& other) noexcept : id_(++last_id_), label_(std::exchange(other.label_, "")) {
        log("przenoszenie z #" + std::to_string(other.id_));
    }

    Noisy& operator=(const Noisy& other) {
        label_ = other.label_;
        log("przypisanie kopiujące z #" + std::to_string(other.id_));
        return *this;
    }

    Noisy& operator=(Noisy&& other) noexcept {
        label_ = std::exchange(other.label_, "");
        log("przypisanie przenoszące z #" + std::to_string(other.id_));
        return *this;
    }

    ~Noisy() {
        log("destruktor");
    }

    int id() const {
        return id_;
    }

    const std::string& label() const {
        return label_;
    }

private:
    void log(const std::string& what) const {
        std::cout << "  #" << id_ << " \"" << label_ << "\": " << what << '\n';
    }

    static inline int last_id_ = 0;
    int id_;
    std::string label_;
};
