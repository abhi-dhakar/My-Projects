#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Bank Account Class
class BankAccount {
private:
    string accountNumber;
    string name;
    double balance;

public:
    // Constructor
    BankAccount(string accNum, string accName, double initialBalance) {
        accountNumber = accNum;
        name = accName;
        balance = initialBalance;
    }

    // Getters
    string getAccountNumber() { return accountNumber; }
    string getName() { return name; }
    double getBalance() { return balance; }

    // Deposit Money
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: $" << amount << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    // Withdraw Money
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: $" << amount << endl;
            return true;
        } else {
            cout << "Insufficient funds or invalid amount!" << endl;
            return false;
        }
    }

    // Display Account Info
    void display() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Balance: $" << balance << endl;
    }

    // Save Account to File
    void saveToFile(ofstream &outFile) {
        outFile << accountNumber << " " << name << " " << balance << endl;
    }
};

// Function to Load Accounts from File
vector<BankAccount> loadAccounts() {
    vector<BankAccount> accounts;
    ifstream inFile("accounts.txt");
    if (!inFile) return accounts;

    string accNum, name;
    double balance;
    while (inFile >> accNum >> name >> balance) {
        accounts.push_back(BankAccount(accNum, name, balance));
    }
    inFile.close();
    return accounts;
}

// Function to Save Accounts to File
void saveAccounts(vector<BankAccount> &accounts) {
    ofstream outFile("accounts.txt");
    for (auto &acc : accounts) {
        acc.saveToFile(outFile);
    }
    outFile.close();
}

int main() {
    vector<BankAccount> accounts = loadAccounts();
    int choice;
    
    do {
        cout << "\n===== Bank Management System =====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Display All Accounts\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string accNum, name;
            double initialBalance;
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Initial Balance: ";
            cin >> initialBalance;
            accounts.push_back(BankAccount(accNum, name, initialBalance));
            saveAccounts(accounts);
            cout << "Account Created Successfully!\n";
        } 
        
        else if (choice == 2) {
            string accNum;
            double amount;
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Deposit Amount: ";
            cin >> amount;
            for (auto &acc : accounts) {
                if (acc.getAccountNumber() == accNum) {
                    acc.deposit(amount);
                    saveAccounts(accounts);
                    break;
                }
            }
        } 
        
        else if (choice == 3) {
            string accNum;
            double amount;
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Withdrawal Amount: ";
            cin >> amount;
            for (auto &acc : accounts) {
                if (acc.getAccountNumber() == accNum) {
                    if (acc.withdraw(amount)) {
                        saveAccounts(accounts);
                    }
                    break;
                }
            }
        } 
        
        else if (choice == 4) {
            string accNum;
            cout << "Enter Account Number: ";
            cin >> accNum;
            for (auto &acc : accounts) {
                if (acc.getAccountNumber() == accNum) {
                    cout << "Balance: $" << acc.getBalance() << endl;
                    break;
                }
            }
        } 
        
        else if (choice == 5) {
            cout << "\n=== All Accounts ===\n";
            for (auto &acc : accounts) {
                acc.display();
                cout << "------------------\n";
            }
        }

    } while (choice != 6);

    cout << "Exiting Bank Management System. Have a nice day!\n";
    return 0;
}
