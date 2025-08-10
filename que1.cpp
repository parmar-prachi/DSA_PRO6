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
    BankAccount(int accNo, string name, double bal = 0)   // Constructor
        : accountNumber(accNo), accountHolderName(name), balance(bal)
    {}

    virtual void deposit(double amount)  // Deposit Method
    {
        balance += amount;
        cout << "Deposited: " << amount << " New Balance: " << balance << endl;
    }

    virtual void withdraw(double amount) // Withdraw Method
    {
        if (amount <= balance)
        {
            balance -= amount;
            cout << "Withdrawn: " << amount << " New Balance: " << balance << endl;
        }
        else
        {
            cout << "Insufficient balance!" << endl;
        }
    }

    double getBalance() const { return balance; } // Balance Getter

    virtual void displayAccountInfo() const
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
        : BankAccount(accNo, name, bal), overdraftLimit(limit) {}

    void withdraw(double amount) // Overload withdraw method
    {
        if (amount <= balance + overdraftLimit)
        {
            balance -= amount; // Withdraw from balance
            cout << "Withdrawn: " << amount << " New Balance: " << balance << endl;
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
        : BankAccount(accNo, name, bal), duration(dur), interestRate(rate) {}

    void calculateInterest() // Fixed Deposit Account Interest Calculation
    {
        double interest = balance * interestRate * duration / (12 * 100);
        cout << "FD Interest: " << interest << endl;
    }
};

// Main Menu
int main()
{
    SavingsAccount sa(101, "Prachi", 5000, 4);  // 4% interest
    CheckingAccount ca(102, "Sakshi", 2000, 1000); // overdraft limit of 1000
    FixedDepositAccount fda(103, "Dhara", 10000, 3, 4);  // 3 months, 4% interest

    BankAccount *accounts[] = {&sa, &ca, &fda}; // Array of BankAccount pointers
    int choice, accType; 
    double amount; // Variable to store amount

    do
    {
        cout << "--- Banking System Menu --- " << endl;
        cout << "1. Deposit " << endl << "2. Withdraw " << endl << "3. Display Info" << endl << "4. Calculate Interest" << endl << "0. Exit " << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 0)
            break;

        cout << "Select Account (0: Savings, 1: Checking, 2: Fixed Deposit): ";
        cin >> accType;

        switch (choice)
        {
        case 1:
            cout << "Enter amount to deposit: ";
            cin >> amount;
            accounts[accType]->deposit(amount);
            break;
        case 2:
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            accounts[accType]->withdraw(amount);
            break;
        case 3:
            accounts[accType]->displayAccountInfo();
            break;
        case 4:
            accounts[accType]->calculateInterest();
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    return 0;
}
/* output : -

   --- Banking System Menu ---

1. Deposit
2. Withdraw
3. Display Info
4. Calculate Interest
0. Exit

---->> Enter choice: 1

Select Account (0: Savings, 1: Checking, 2: Fixed Deposit): 0

Enter amount to deposit: 3000

Deposited: 3000 New Balance: 8000 

------------------------------------------------------------------

---->> Enter choice: 2

Select Account (0: Savings, 1: Checking, 2: Fixed Deposit): 1

Enter amount to withdraw: 500

Withdrawn: 500 New Balance: 1500 

------------------------------------------------------------------

---->> Enter choice: 2

Select Account (0: Savings, 1: Checking, 2: Fixed Deposit): 1

Enter amount to withdraw: 8000

Overdraft limit exceeded! 

------------------------------------------------------------------

---->> Enter choice: 3

Select Account (0: Savings, 1: Checking, 2: Fixed Deposit): 2

Account Number: 103

Account Holder: Dhara

Balance: 10000 

------------------------------------------------------------------

---->> Enter choice: 4

Select Account (0: Savings, 1: Checking, 2: Fixed Deposit): 2

FD Interest: 100  // ->>  10,000 * 4 * 3 / (12 * 100) = 1,20,000 / 1,200 //

*/