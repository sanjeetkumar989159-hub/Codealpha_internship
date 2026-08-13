#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// Represents one banking transaction
class Transaction {

private:
    string type;
    double amount;
    string description;

public:

    // Constructor to create a transaction
    Transaction(string t, double a, string d)
        : type(t), amount(a), description(d) {}

    // Function to display transaction details
    void display() const {

        cout << left
             << setw(15) << type
             << setw(15) << fixed << setprecision(2) << amount
             << description
             << endl;
    }
};

// Represents a customer's bank account
class Account {

private:
    int accountNumber;
    double balance;

    vector<Transaction> transactions;

public:

    // Constructor to create an account
    Account(int number, double initialBalance = 0)
        : accountNumber(number), balance(initialBalance) {}

    // Returns account number
    int getAccountNumber() const {
        return accountNumber;
    }

    // Returns current account balance
    double getBalance() const {
        return balance;
    }

    // Deposits money into the account
    bool deposit(double amount) {

        if (amount <= 0) {
            cout << "Deposit amount must be greater than 0.\n";
            return false;
        }

        balance += amount;

        transactions.emplace_back(
            "Deposit",
            amount,
            "Money deposited"
        );

        cout << "Deposit successful.\n";
        cout << "New balance: Rs. "
             << fixed << setprecision(2)
             << balance << endl;

        return true;
    }

    // Withdraws money from the account
    bool withdraw(double amount) {

        if (amount <= 0) {

            cout << "Withdrawal amount must be greater than 0.\n";
            return false;
        }

        if (amount > balance) {

            cout << "Insufficient balance!\n";
            return false;
        }

        balance -= amount;

        transactions.emplace_back(
            "Withdrawal",
            amount,
            "Money withdrawn"
        );

        cout << "Withdrawal successful.\n";
        cout << "Remaining balance: Rs. "
             << fixed << setprecision(2)
             << balance << endl;

        return true;
    }

    // Displays account information
    void displayAccount() const {

        cout << "\n========== ACCOUNT INFORMATION ==========\n";

        cout << "Account Number: " << accountNumber << endl;

        cout << "Balance: Rs. "
             << fixed << setprecision(2)
             << balance << endl;
    }

    // Displays transaction history
    void displayTransactions() const {

        cout << "\n========== TRANSACTION HISTORY ==========\n";

        if (transactions.empty()) {

            cout << "No transactions available.\n";
            return;
        }

        cout << left
             << setw(15) << "Type"
             << setw(15) << "Amount"
             << "Description"
             << endl;

        cout << "------------------------------------------\n";

        for (const Transaction& transaction : transactions) {

            transaction.display();
        }
    }
};

// Represents a bank customer
class Customer {

private:
    int customerId;
    string name;
    string phone;

    vector<Account> accounts;

public:

    // Constructor to create a customer
    Customer(int id, string customerName, string customerPhone)
        : customerId(id),
          name(customerName),
          phone(customerPhone) {}

    // Returns customer ID
    int getCustomerId() const {
        return customerId;
    }

    // Creates a new bank account for the customer
    void createAccount(int accountNumber) {

        accounts.emplace_back(accountNumber);

        cout << "Account created successfully!\n";
        cout << "Account Number: " << accountNumber << endl;
    }

    // Finds an account using account number
    Account* findAccount(int accountNumber) {

        for (Account& account : accounts) {

            if (account.getAccountNumber() == accountNumber) {
                return &account;
            }
        }

        return nullptr;
    }

    // Displays customer information
    void displayCustomer() const {

        cout << "\n========== CUSTOMER INFORMATION ==========\n";

        cout << "Customer ID: " << customerId << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;

        cout << "\nAccounts:\n";

        if (accounts.empty()) {

            cout << "No accounts available.\n";
            return;
        }

        for (const Account& account : accounts) {

            cout << "Account Number: "
                 << account.getAccountNumber()
                 << " | Balance: Rs. "
                 << fixed << setprecision(2)
                 << account.getBalance()
                 << endl;
        }
    }
};

// Represents the complete banking system
class Bank {

private:
    vector<Customer> customers;

    int nextCustomerId = 1001;
    int nextAccountNumber = 5001;

public:

    // Creates a new customer
    void createCustomer() {

        string name;
        string phone;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter customer name: ";
        getline(cin, name);

        cout << "Enter phone number: ";
        getline(cin, phone);

        if (name.empty()) {

            cout << "Customer name cannot be empty.\n";
            return;
        }

        if (phone.empty()) {

            cout << "Phone number cannot be empty.\n";
            return;
        }

        customers.emplace_back(
            nextCustomerId,
            name,
            phone
        );

        cout << "\nCustomer created successfully!\n";
        cout << "Customer ID: " << nextCustomerId << endl;

        nextCustomerId++;
    }

    // Finds a customer using customer ID
    Customer* findCustomer(int customerId) {

        for (Customer& customer : customers) {

            if (customer.getCustomerId() == customerId) {
                return &customer;
            }
        }

        return nullptr;
    }

    // Creates an account for a customer
    void createAccount() {

        int customerId;

        cout << "Enter customer ID: ";
        cin >> customerId;

        Customer* customer = findCustomer(customerId);

        if (customer == nullptr) {

            cout << "Customer not found!\n";
            return;
        }

        customer->createAccount(nextAccountNumber);

        nextAccountNumber++;
    }

    // Deposits money into a customer's account
    void depositMoney() {

        int customerId;
        int accountNumber;
        double amount;

        cout << "Enter customer ID: ";
        cin >> customerId;

        Customer* customer = findCustomer(customerId);

        if (customer == nullptr) {

            cout << "Customer not found!\n";
            return;
        }

        cout << "Enter account number: ";
        cin >> accountNumber;

        Account* account = customer->findAccount(accountNumber);

        if (account == nullptr) {

            cout << "Account not found!\n";
            return;
        }

        cout << "Enter amount to deposit: ";
        cin >> amount;

        if (cin.fail()) {

            cout << "Invalid amount!\n";

            cin.clear();
            cin.ignore(10000, '\n');

            return;
        }

        account->deposit(amount);
    }

    // Withdraws money from a customer's account
    void withdrawMoney() {

        int customerId;
        int accountNumber;
        double amount;

        cout << "Enter customer ID: ";
        cin >> customerId;

        Customer* customer = findCustomer(customerId);

        if (customer == nullptr) {

            cout << "Customer not found!\n";
            return;
        }

        cout << "Enter account number: ";
        cin >> accountNumber;

        Account* account = customer->findAccount(accountNumber);

        if (account == nullptr) {

            cout << "Account not found!\n";
            return;
        }

        cout << "Enter amount to withdraw: ";
        cin >> amount;

        if (cin.fail()) {

            cout << "Invalid amount!\n";

            cin.clear();
            cin.ignore(10000, '\n');

            return;
        }

        account->withdraw(amount);
    }

    // Transfers money between two accounts
    void transferMoney() {

        int senderCustomerId;
        int senderAccountNumber;

        int receiverCustomerId;
        int receiverAccountNumber;

        double amount;

        cout << "Enter sender customer ID: ";
        cin >> senderCustomerId;

        Customer* sender =
            findCustomer(senderCustomerId);

        if (sender == nullptr) {

            cout << "Sender customer not found!\n";
            return;
        }

        cout << "Enter sender account number: ";
        cin >> senderAccountNumber;

        Account* senderAccount =
            sender->findAccount(senderAccountNumber);

        if (senderAccount == nullptr) {

            cout << "Sender account not found!\n";
            return;
        }

        cout << "Enter receiver customer ID: ";
        cin >> receiverCustomerId;

        Customer* receiver =
            findCustomer(receiverCustomerId);

        if (receiver == nullptr) {

            cout << "Receiver customer not found!\n";
            return;
        }

        cout << "Enter receiver account number: ";
        cin >> receiverAccountNumber;

        Account* receiverAccount =
            receiver->findAccount(receiverAccountNumber);

        if (receiverAccount == nullptr) {

            cout << "Receiver account not found!\n";
            return;
        }

        // Prevent transferring to the same account
        if (senderAccount == receiverAccount) {

            cout << "Sender and receiver accounts cannot be same.\n";
            return;
        }

        cout << "Enter transfer amount: ";
        cin >> amount;

        if (cin.fail() || amount <= 0) {

            cout << "Invalid transfer amount!\n";

            cin.clear();
            cin.ignore(10000, '\n');

            return;
        }

        // First withdraw from sender
        if (!senderAccount->withdraw(amount)) {
            return;
        }

        // Then deposit into receiver
        if (!receiverAccount->deposit(amount)) {

            // This should normally never happen because amount
            // has already been validated.
            cout << "Transfer failed.\n";
            return;
        }

        cout << "\nTransfer successful!\n";
    }

    // Displays account and transaction details
    void showAccountDetails() {

        int customerId;
        int accountNumber;

        cout << "Enter customer ID: ";
        cin >> customerId;

        Customer* customer = findCustomer(customerId);

        if (customer == nullptr) {

            cout << "Customer not found!\n";
            return;
        }

        cout << "Enter account number: ";
        cin >> accountNumber;

        Account* account =
            customer->findAccount(accountNumber);

        if (account == nullptr) {

            cout << "Account not found!\n";
            return;
        }

        account->displayAccount();
        account->displayTransactions();
    }

    // Displays all customers
    void displayAllCustomers() {

        if (customers.empty()) {

            cout << "No customers available.\n";
            return;
        }

        for (const Customer& customer : customers) {

            customer.displayCustomer();
        }
    }

    // Displays the banking system menu
    void menu() {

        int choice;

        while (true) {

            cout << "\n========================================\n";
            cout << "          BANKING SYSTEM\n";
            cout << "========================================\n";

            cout << "1. Create Customer\n";
            cout << "2. Create Account\n";
            cout << "3. Deposit Money\n";
            cout << "4. Withdraw Money\n";
            cout << "5. Transfer Money\n";
            cout << "6. Account Details & Transactions\n";
            cout << "7. Display All Customers\n";
            cout << "8. Exit\n";

            cout << "Enter your choice: ";

            if (!(cin >> choice)) {

                cout << "Invalid input! Enter a number.\n";

                cin.clear();
                cin.ignore(10000, '\n');

                continue;
            }

            switch (choice) {

                case 1:
                    createCustomer();
                    break;

                case 2:
                    createAccount();
                    break;

                case 3:
                    depositMoney();
                    break;

                case 4:
                    withdrawMoney();
                    break;

                case 5:
                    transferMoney();
                    break;

                case 6:
                    showAccountDetails();
                    break;

                case 7:
                    displayAllCustomers();
                    break;

                case 8:
                    cout << "Thank you for using Banking System!\n";
                    return;

                default:
                    cout << "Invalid choice! Please select 1-8.\n";
            }
        }
    }
};

// Program starts here
int main() {

    Bank bank;

    bank.menu();

    return 0;
}