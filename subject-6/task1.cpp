#include <iostream>
#include <string>

// Base class
class Entity {
public:
    Entity(const std::string& name) : name_(name) {
        std::cout << "Entity ctor: " << name_ << "\n";
    }

    // Virtual destructor is crucial for polymorphism!
    virtual ~Entity() {
        std::cout << "Entity dtor: " << name_ << "\n";
    }

    const std::string& getName() const { return name_; }

protected: // Accessible to derived classes
    std::string name_;
};

// Derived class
class Player : public Entity {
public:
    // Using initialization list to construct the base part
    Player(const std::string& name, int score) 
        : Entity(name), score_(score) {
        std::cout << "Player ctor: " << score_ << "\n";
    }

    ~Player() {
        std::cout << "Player dtor: " << name_ << "\n";
    }

    void printStats() const {
        std::cout << "Player: " << name_ << ", Score: " << score_ << "\n";
    }

private:
    int score_;
};

void inspectEntity(const Entity& e) {
    std::cout << "Inspecting entity: " << e.getName() << "\n";
}

int main() {
    std::cout << "--- Construction ---\n";
    Player p1("Hero", 100);

    std::cout << "\n--- Is-a Relationship ---\n";
    // Implicit Derived-to-Base conversion
    inspectEntity(p1); 

    std::cout << "\n--- Destruction ---\n";
    return 0;
}
