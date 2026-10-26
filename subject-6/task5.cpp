#include <iostream>

// --- Abstraction (Interface) ---
class ISwitchable {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual ~ISwitchable() = default;
};

// --- Low-level module ---
class Lamp : public ISwitchable {
public:
    void turnOn() override { std::cout << "Lamp is ON\n"; }
    void turnOff() override { std::cout << "Lamp is OFF\n"; }
};

class Fan : public ISwitchable {
public:
    void turnOn() override { std::cout << "Fan is spinning\n"; }
    void turnOff() override { std::cout << "Fan stopped\n"; }
};

// --- High-level module ---
// Button depends on abstraction (ISwitchable), not concrete Lamp or Fan.
class Button {
public:
    Button(ISwitchable& device) : device_(device) {}

    void press() {
        if (isOn) {
            device_.turnOff();
            isOn = false;
        } else {
            device_.turnOn();
            isOn = true;
        }
    }

private:
    ISwitchable& device_;
    bool isOn = false;
};

int main() {
    Lamp myLamp;
    Fan myFan;

    Button button1(myLamp); // Button works with Lamp
    Button button2(myFan);  // Button works with Fan

    std::cout << "--- Button 1 ---\n";
    button1.press();
    button1.press();

    std::cout << "\n--- Button 2 ---\n";
    button2.press();

    return 0;
}
