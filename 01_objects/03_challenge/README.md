```cpp

#include <iostream>

class BankAccount {
public:
    BankAccount(double initial_balance) : balance(initial_balance) {}

    void deposit(double amount) {
        balance += amount;
        std::cout << balance << std::endl;
    }

    void withdraw(double amount) {
        if (amount > balance) {
            std::cout << "Insufficient balance!" << std::endl;
        } else {
            balance -= amount;
            std::cout << balance << std::endl;
        }
    }

    double get_balance() const {
        return balance;
    }

private:
    double balance;
};

int main() {
    BankAccount bank_account(100);
    bank_account.deposit(50);
    bank_account.withdraw(30);
    bank_account.withdraw(150);
    return 0;
}

```