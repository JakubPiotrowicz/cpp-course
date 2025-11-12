#include <iostream>

class Example {
    // By default, members are private.
    int secret;
private:
    // This is a private member, it can only be accessed by member functions of Example.
    int secretValue;

public:
    // This is a public member, it can be accessed from anywhere.
    int publicValue;

    // Public method to set the private member's value.
    void setSecret(int value) {
        secretValue = value; // Member functions can access private members.
    }

    // Public method to display the private member's value.
    void displaySecret() const {
        std::cout << "Secret value is: " << secretValue << std::endl;
    }
};

int main() {
    Example ex;
    ex.publicValue = 10;
    // ex.secretValue = 20; // ERROR: secretValue is private.
    // ex.secret = 30; // ERROR: secret is private.

    ex.setSecret(20);

    std::cout << "Public value is: " << ex.publicValue << std::endl;
    ex.displaySecret();

    return 0;
}
