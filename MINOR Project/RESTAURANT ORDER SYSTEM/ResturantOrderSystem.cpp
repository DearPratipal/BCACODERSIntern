#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Structure to store menu items
struct MenuItem {
    string name;
    double price;
};

// Function to display the menu
void displayMenu(const vector<MenuItem> &menu) {
    cout << "\n--- Restaurant Menu ---" << endl;
    for (int i = 0; i < menu.size(); ++i) {
        cout << i + 1 << ". " << menu[i].name << " - $" << menu[i].price << endl;
    }
    cout << "-----------------------" << endl;
}

// Function to take an order from the customer
void takeOrder(const vector<MenuItem> &menu, vector<MenuItem> &order) {
    int choice;
    displayMenu(menu);

    while (true) {
        cout << "Enter the item number to order (0 to finish): ";
        cin >> choice;

        if (choice == 0) break;

        if (choice > 0 && choice <= menu.size()) {
            order.push_back(menu[choice - 1]);
            cout << "Added " << menu[choice - 1].name << " to your order." << endl;
        } else {
            cout << "Invalid choice, please try again." << endl;
        }
    }
}

// Function to display the bill
void displayBill(const vector<MenuItem> &order) {
    if (order.empty()) {
        cout << "No items ordered." << endl;
        return;
    }

    double total = 0;
    cout << "\n--- Your Bill ---" << endl;
    for (const auto &item : order) {
        cout << item.name << " - $" << item.price << endl;
        total += item.price;
    }
    cout << "------------------" << endl;
    cout << "Total Amount: $" << total << endl;
}

// Function to display the main menu options
void displayMainMenu() {
    cout << "\nRestaurant Order System" << endl;
    cout << "1. Display Menu" << endl;
    cout << "2. Take Order" << endl;
    cout << "3. Display Bill" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    vector<MenuItem> menu = {
        {"Burger", 5.99},
        {"Pizza", 8.99},
        {"Pasta", 7.99},
        {"Salad", 4.99},
        {"Coffee", 2.49},
        {"Tea", 1.99}
    };

    vector<MenuItem> order;
    int choice;

    do {
        displayMainMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                displayMenu(menu);
                break;
            case 2:
                takeOrder(menu, order);
                break;
            case 3:
                displayBill(order);
                break;
            case 4:
                cout << "Thank you for visiting our restaurant!" << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
