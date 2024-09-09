#include <iostream>
#include <string>
#include <vector>
#include <cstddef> // Include the <cstddef> header for nullptr
#include <cstdlib> // Include the <cstdlib> header for rand() and srand()
#include <ctime>   // Include the <ctime> header for time()
using namespace std;

class User {
private:
    string name;
    string phoneNumber;
    string email;
    string username;
    string password;

public:
    User(string name, string phoneNumber, string email, string username, string password)
        : name(name), phoneNumber(phoneNumber), email(email), username(username), password(password) {}

    bool authenticate(string enteredUsername, string enteredPassword) {
        return username == enteredUsername && password == enteredPassword;
    }

    const string& getEmail() const {
        return email;
    }

    const string& getPhoneNumber() const {
        return phoneNumber;
    }
};

class UserManager {
private:
    vector<User> users;

    // Helper function to generate a random OTP
    int generateOTP() {
        srand(time(0)); // Seed for random number generation
        return rand() % 9000 + 1000; // Generate a 4-digit OTP
    }

public:
    void signup(string name, string phoneNumber, string email, string username, string password) {
        // Ask the user where to send the OTP
        char otpDeliveryChoice;
        cout << "Where would you like to receive the OTP? (P for Phone, E for Email): ";
        cin >> otpDeliveryChoice;

        int otp = generateOTP(); // Generate OTP

        if (otpDeliveryChoice == 'P' || otpDeliveryChoice == 'p') {
            cout << "OTP sent to your registered phone number: " << otp << endl;
        } else if (otpDeliveryChoice == 'E' || otpDeliveryChoice == 'e') {
            cout << "OTP sent to your registered email address: " << otp << endl;
        } else {
            cout << "Invalid choice. OTP delivery failed.\n";
            return;
        }

        int enteredOTP;
        cout << "Enter OTP to verify your identity: ";
        cin >> enteredOTP;

        if (enteredOTP == otp) {
            users.push_back(User(name, phoneNumber, email, username, password));
            cout << "Your information has been submitted. An account has been created.\n";
        } else {
            cout << "OTP verification failed. User registration aborted.\n";
        }
    }

    User* login(string username, string password) {
        for (size_t i = 0; i < users.size(); ++i) {
            if (users[i].authenticate(username, password)) {
                cout << "Login successful!\n";
                return &users[i];
            }
        }
        cout << "Invalid username or password. Please try again.\n";
        return 0;
    }
};

class BankSystem {
private:
    string accountNumber;
    string accountHolderName;
    float balance;

public:
    BankSystem(string accNum, string accHolderName, float initialBalance)
        : accountNumber(accNum), accountHolderName(accHolderName), balance(initialBalance) {}

    void deposit(float amount) {
        balance += amount;
        cout << "Deposit of $" << amount << " successful.\n";
    }

    void withdraw(float amount) {
        if (amount > balance) {
            cout << "Insufficient balance. Withdrawal failed.\n";
        } else {
            balance -= amount;
            cout << "Withdrawal of $" << amount << " successful.\n";
        }
    }

    void displayBalance() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: $" << balance << endl;
    }
};

int main() {
    UserManager userManager;
    string name, phoneNumber, email, username, password;
    char choice;

    cout << "-------------------------------------------" << endl;
    cout << "        Welcome to Sahiwal Banking System          " << endl;
    cout << "-------------------------------------------" << endl;

    cout << "Do you have an account? (y/n): ";
    cin >> choice;

    if (choice == 'n' || choice == 'N') {
        cout << "\n----------------- Sign Up -----------------" << endl;
        cout << "Enter your full name: ";
        cin.ignore();
        getline(cin, name);
        
        cout << "Enter your phone number: ";
        cin >> phoneNumber;

        cout << "Enter your email address: ";
        cin >> email;

        cout << "Enter your username: ";
        cin >> username;

        cout << "Enter a strong password: ";
        cin >> password;

        // Call signup function with user details
        userManager.signup(name, phoneNumber, email, username, password);
    } else if (choice == 'y' || choice == 'Y') {
        cout << "\n----------------- Log In -----------------" << endl;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
      
        
    }

string accountNumber, accountHolderName;
    float initialBalance;

    cout << "\n-------------------------------------------" << endl;
    cout << "           Welcome to Your Account          " << endl;
    cout << "-------------------------------------------" << endl;

    cout << "Enter your account number: ";
    cin >> accountNumber;

    cout << "Enter your name: ";
    cin.ignore(); // Ignore newline character from previous input
    getline(cin, accountHolderName);

    cout << "Enter initial balance: $";
    cin >> initialBalance;

    BankSystem bankAccount(accountNumber, accountHolderName, initialBalance);

    string accountChoice;
    do {
        cout << "\nChoose your action:" << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Display Balance" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> accountChoice;

        if (accountChoice == "1") {
            float amount;
            cout << "Enter amount to deposit: $";
            cin >> amount;
            bankAccount.deposit(amount);
        } else if (accountChoice == "2") {
            float amount;
            cout << "Enter amount to withdraw: $";
            cin >> amount;
            bankAccount.withdraw(amount);
        } else if (accountChoice == "3") {
            cout << "\n-------------------------------------------" << endl;
            cout << "           Account Information             " << endl;
            cout << "-------------------------------------------" << endl;
            bankAccount.displayBalance();
        } else if (accountChoice == "4") {
            cout << "Thank you for using our Banking System!\n";
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    } while (true);

    return 0;
}

