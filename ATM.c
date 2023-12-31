#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct BankAccount {
    char username[50];
    char password[50];
    int accountNumber;
    float balance;
};

void clearScreen() {
    printf("\033[2J\033[1;1H");
}

void printHeader() {
    printf("**********************\n");
    printf("*  DATE: 19 JULY 2023                                    *\n");
    printf("*                    YOU ARE ACCESSING ATM               *\n");
    printf("*                    DO NOT CLOSE THE WINDOW             *\n");
    printf("*                                                        *\n");
    printf("**********************\n");
}

void printMenu(bool loggedIn) {
    printf("\n");
    printf("********* MENU ***********\n");
    
    if (!loggedIn) {
        printf("* 1. Sign up                                             *\n");
        printf("* 2. Login                                               *\n");
    } else {
        printf("* 3. Access account                                         *\n");
        printf("* 4. Deposit money                                          *\n");
        printf("* 5. Withdraw money                                         *\n");
        printf("* 6. Check bank balance                                     *\n");
        printf("* 7. Request mini statement                                 *\n");
        printf("* 8. Apply for a loan                                       *\n");
        printf("* 9. Log out                                                *\n");
    }
    
    printf("* 0. Exit                                                *\n");
    printf("**********************\n");
}

void printSuccessMessage(const char* message) {
    printf("\n\033[1;32m%s\033[0m\n", message);
}

void printErrorMessage(const char* message) {
    printf("\n\033[1;31m%s\033[0m\n", message);
}

struct BankAccount createAccount() {
    struct BankAccount account;
    
    printf("Enter username: ");
    scanf("%s", account.username);
    
    printf("Enter password: ");
    scanf("%s", account.password);
    
    printf("Enter account number: ");
    scanf("%d", &account.accountNumber);
    
    account.balance = 0.0;
    
    printSuccessMessage("Account created successfully!");
    
    return account;
}

bool authenticateUser(struct BankAccount account) {
    char username[50], password[50];
    
    printf("Enter username: ");
    scanf("%s", username);
    
    printf("Enter password: ");
    scanf("%s", password);
    
    if (strcmp(username, account.username) == 0 && strcmp(password, account.password) == 0) {
        printSuccessMessage("Login successful!");
        return true;
    } else {
        printErrorMessage("Invalid username or password. Login failed.");
        return false;
    }
}

void accessAccount(struct BankAccount account) {
    clearScreen();
    printHeader();
    printf("Username: %s\n", account.username);
    printf("Account Number: %d\n", account.accountNumber);
    printf("Balance: %.2f\n", account.balance);
}

struct BankAccount deposit(struct BankAccount account) {
    float amount;
    printf("Enter the amount to deposit: ");
    scanf("%f", &amount);
    
    account.balance += amount;
    
    printSuccessMessage("Amount deposited successfully!");
    
    return account;
}

struct BankAccount withdraw(struct BankAccount account) {
    float amount;
    printf("Enter the amount to withdraw: ");
    scanf("%f", &amount);
    
    if (amount <= account.balance) {
        account.balance -= amount;
        printSuccessMessage("Amount withdrawn successfully!");
    } else {
        printErrorMessage("Insufficient balance!");
    }
    
    return account;
}

void checkBalance(struct BankAccount account) {
    printf("Balance: %.2f\n", account.balance);
}

void requestMiniStatement(struct BankAccount account) {
    clearScreen();
    printHeader();
    printf("Mini statement for account number %d:\n", account.accountNumber);
    printf("Username: %s\n", account.username);
    printf("Balance: %.2f\n", account.balance);
    printf("Last 5 transactions: ...\n");
    // Print the last 5 transactions from the account's transaction history.
}

void applyLoan(struct BankAccount account) {
    // Implement loan application logic here.
    printSuccessMessage("Loan applied successfully!");
}

int main() {
    struct BankAccount account;
    int choice;
    bool loggedIn = false;
    
    clearScreen();
    printHeader();
    
    do {
        printMenu(loggedIn);
        
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        clearScreen();
        printHeader();
        
        switch (choice) {
            case 1:
                account = createAccount();
                loggedIn = true;
                break;
            case 2:
                loggedIn = authenticateUser(account);
                break;
            case 3:
                if (loggedIn)
                    accessAccount(account);
                else
                    printErrorMessage("Please log in first!");
                break;
            case 4:
                if (loggedIn)
                    account = deposit(account);
                else
                    printErrorMessage("Please log in first!");
                break;
            case 5:
                if (loggedIn)
                    account = withdraw(account);
                else
                    printErrorMessage("Please log in first!");
                break;
            case 6:
                if (loggedIn)
                    checkBalance(account);
                else
                    printErrorMessage("Please log in first!");
                break;
            case 7:
                if (loggedIn)
                    requestMiniStatement(account);
                else
                    printErrorMessage("Please log in first!");
                break;
            case 8:
                if (loggedIn)
                    applyLoan(account);
                else
                    printErrorMessage("Please log in first!");
                break;
            case 9:
                loggedIn = false;
                printSuccessMessage("Logged out successfully!");
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printErrorMessage("Invalid choice!");
        }
    } while (choice != 0);
    
    return 0;
}
