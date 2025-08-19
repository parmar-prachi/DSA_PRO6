#include <iostream>
#include <string>
using namespace std;

// Base Class
class BankAccount
{
protected:
    int accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount(int accNo, string name, double bal = 0) // Constructor
        : accountNumber(accNo), accountHolderName(name), balance(bal)
    {
    }

    virtual void deposit(double amount) // Deposit Method
    {
        balance += amount;
    }

    virtual void withdraw(double amount) // Withdraw Method
    {
        if (amount <= balance)
        {
            balance -= amount;
        }
        else
        {
            cout << "Insufficient balance!" << endl;
        }
    }

    double getBalance() const { return balance; } // Balance Getter

    virtual void displayAccountInfo() const // account info display
    {
        cout << "Account Number: " << accountNumber << endl
             << "Account Holder: " << accountHolderName << endl
             << "Balance: " << balance << endl;
    }

    virtual void calculateInterest()
    {
        // Empty default for polymorphism
    }
};

// Derived Class - Savings Account

class SavingsAccount : public BankAccount
{
    double interestRate;

public:
    SavingsAccount(int accNo, string name, double bal, double rate) // Constructor
        : BankAccount(accNo, name, bal), interestRate(rate)
    {
    }

    void calculateInterest() // Savings Account Interest Calculation
    {
        double interest = balance * interestRate / 100;
        cout << "Interest: " << interest << endl;
    }
};

// Derived Class - Checking Account / Current Account

class CheckingAccount : public BankAccount
{
    double overdraftLimit;

public:
    CheckingAccount(int accNo, string name, double bal, double limit) // Constructor
        : BankAccount(accNo, name, bal), overdraftLimit(limit)
    {
    }

    void withdraw(double amount) // Overload withdraw method
    {
        if (amount <= balance + overdraftLimit)
        {
            balance -= amount; // Withdraw from balance
        }
        else
        {
            cout << "Overdraft limit exceeded!" << endl;
        }
    }
};

// Derived Class - Fixed Deposit Account

class FixedDepositAccount : public BankAccount
{
    int duration; // in months
    double interestRate;

public:
    FixedDepositAccount(int accNo, string name, double bal, int dur, double rate) // Constructor
        : BankAccount(accNo, name, bal), duration(dur), interestRate(rate)
    {
    }

    void calculateInterest() // Fixed Deposit Account Interest Calculation
    {
        double interest = balance * interestRate * duration / (12 * 100);
        cout << "FD Interest: " << interest << endl;
    }
};

// Main Menu
int main()
{
    int accNum;
    string accName;
    double balance;

    cout << "Enter details for Savings Account:\n";
    cout << "Account Number: ";
    cin >> accNum;
    cout << "Account Holder Name: ";
    cin >> accName;
    cout << "Initial Balance: ";
    cin >> balance;
    double sRate;
    cout << "Interest Rate (%): ";
    cin >> sRate;
    SavingsAccount sa(accNum, accName, balance, sRate);

    cout << "\nEnter details for Checking Account:\n";
    cout << "Account Number: ";
    cin >> accNum;
    cout << "Account Holder Name: ";
    cin >> accName;
    cout << "Initial Balance: ";
    cin >> balance;
    double limit;
    cout << "Overdraft Limit: ";
    cin >> limit;
    CheckingAccount ca(accNum, accName, balance, limit);

    cout << "\nEnter details for Fixed Deposit Account:\n";
    cout << "Account Number: ";
    cin >> accNum;
    cout << "Account Holder Name: ";
    cin >> accName;
    cout << "Initial Balance: ";
    cin >> balance;
    int term;
    double fRate;
    cout << "Term (in months): ";
    cin >> term;
    cout << "Interest Rate (%): ";
    cin >> fRate;
    FixedDepositAccount fda(accNum, accName, balance, term, fRate);

    BankAccount *accounts[] = {&sa, &ca, &fda};
    int choice, accTypes;

    do
    {
        cout << "---- Banking System Menu ----" << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Display Account Info" << endl;
        cout << "4. Calculate Interest" << endl;
        cout << "0. Exit" << endl;

        cout << " Enter your choice: ";
        cin >> choice;
        int amount;

        if (choice == 0)
            break;

        cout << "Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):";
        cin >> accTypes;

        switch (choice)
        {
        case 1:
            cout << "Enter amount to deposit: ";
            cin >> amount;
            accounts[accTypes]->deposit(amount);
            break;

        case 2:
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            accounts[accTypes]->withdraw(amount);
            break;

        case 3:
            accounts[accTypes]->displayAccountInfo();
            break;

        case 4:
            accounts[accTypes]->calculateInterest();
            break;

        default:
            cout << "Invalid choice" << endl;
        }

    } while (choice != 0);

    return 0;
}
/*output  :---

Enter details for Savings Account:
Account Number: 123
Account Holder Name: prachi
Initial Balance: 50000
Interest Rate (%): 4

Enter details for Checking Account:
Account Number: 124
Account Holder Name: sakshi
Initial Balance: 60000
Overdraft Limit: 3000

Enter details for Fixed Deposit Account:
Account Number: 125
Account Holder Name: palak
Initial Balance: 80000
Term (in months): 3
Interest Rate (%): 4
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 1
Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):0
Enter amount to deposit: 2000 
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 2
Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):0
Enter amount to withdraw: 1000
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 3
Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):0
Account Number: 123
Account Holder: prachi
Balance: 51000
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 4
Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):0
Interest: 2040
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 2
Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):1
Enter amount to withdraw: 2000
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 1
Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):1
Enter amount to deposit: 5000
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 3
Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):1
Account Number: 124
Account Holder: sakshi
Balance: 63000
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 1
Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):2
Enter amount to deposit: 5000
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 2
Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):2
Enter amount to withdraw: 6000
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 3
Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):2
Account Number: 125
Account Holder: palak
Balance: 79000
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 4
Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):2
FD Interest: 790
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 0
*/