#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Structure to store expense information
struct Expense {
    string description;
    string category;
    double amount;
};

// Function to add a new expense
void addExpense(vector<Expense> &expenses) {
    Expense expense;
    cout << "Enter expense description: ";
    cin.ignore(); // Ignore the newline left in the buffer
    getline(cin, expense.description);

    cout << "Enter expense category (e.g., Food, Transport, Bills): ";
    getline(cin, expense.category);

    cout << "Enter amount: ";
    cin >> expense.amount;

    expenses.push_back(expense);
    cout << "Expense added successfully." << endl;
}

// Function to display all expenses
void displayExpenses(const vector<Expense> &expenses) {
    if (expenses.empty()) {
        cout << "No expenses recorded." << endl;
        return;
    }

    cout << "\n--- Expense List ---" << endl;
    cout << left << setw(20) << "Description" << setw(15) << "Category" << setw(10) << "Amount" << endl;
    cout << "-------------------------------------------" << endl;

    for (const auto &expense : expenses) {
        cout << left << setw(20) << expense.description << setw(15) << expense.category << "$" << fixed << setprecision(2) << expense.amount << endl;
    }
}

// Function to calculate and display the total amount spent
void displayTotal(const vector<Expense> &expenses) {
    double total = 0;
    for (const auto &expense : expenses) {
        total += expense.amount;
    }
    cout << "\nTotal Amount Spent: $" << fixed << setprecision(2) << total << endl;
}

// Function to display the main menu options
void displayMenu() {
    cout << "\nExpense Tracker" << endl;
    cout << "1. Add Expense" << endl;
    cout << "2. Display All Expenses" << endl;
    cout << "3. Display Total Amount Spent" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    vector<Expense> expenses;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addExpense(expenses);
                break;
            case 2:
                displayExpenses(expenses);
                break;
            case 3:
                displayTotal(expenses);
                break;
            case 4:
                cout << "Exiting the program. Thank you for using the Expense Tracker!" << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
