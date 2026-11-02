// Błąd kompilacji: dostęp do składowej prywatnej spoza klasy. Zob. README, sekcja 2.
class Account {
public:
    void deposit(int amount) {
        balance_ += amount;
    }

private:
    int balance_ = 0;
};

int main() {
    Account account;
    account.deposit(10);
    account.balance_ = 1000000; // Błąd: balance_ jest prywatne.
}
