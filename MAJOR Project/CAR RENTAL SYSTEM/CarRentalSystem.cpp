#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Structure to store car information
struct Car {
    string brand;
    string model;
    int year;
    bool isRented; // Indicates if the car is currently rented
};

// Function to add a new car to the inventory
void addCar(vector<Car> &cars) {
    Car car;
    cout << "Enter car brand: ";
    cin.ignore(); // Ignore the newline left in the buffer
    getline(cin, car.brand);

    cout << "Enter car model: ";
    getline(cin, car.model);

    cout << "Enter car year: ";
    cin >> car.year;

    car.isRented = false; // Car is available when added
    cars.push_back(car);
    cout << "Car added successfully." << endl;
}

// Function to display all cars and their status
void displayCars(const vector<Car> &cars) {
    if (cars.empty()) {
        cout << "No cars in the inventory." << endl;
        return;
    }

    cout << "\n--- Car Inventory ---" << endl;
    for (int i = 0; i < cars.size(); ++i) {
        cout << i + 1 << ". " << cars[i].brand << " " << cars[i].model << " (" << cars[i].year << ") - ";
        cout << (cars[i].isRented ? "Rented" : "Available") << endl;
    }
    cout << "-----------------------" << endl;
}

// Function to rent a car
void rentCar(vector<Car> &cars) {
    displayCars(cars);
    if (cars.empty()) return;

    int choice;
    cout << "Enter the car number to rent: ";
    cin >> choice;

    if (choice > 0 && choice <= cars.size()) {
        if (!cars[choice - 1].isRented) {
            cars[choice - 1].isRented = true;
            cout << "Car rented successfully." << endl;
        } else {
            cout << "This car is already rented." << endl;
        }
    } else {
        cout << "Invalid car number." << endl;
    }
}

// Function to return a rented car
void returnCar(vector<Car> &cars) {
    displayCars(cars);
    if (cars.empty()) return;

    int choice;
    cout << "Enter the car number to return: ";
    cin >> choice;

    if (choice > 0 && choice <= cars.size()) {
        if (cars[choice - 1].isRented) {
            cars[choice - 1].isRented = false;
            cout << "Car returned successfully." << endl;
        } else {
            cout << "This car is not rented." << endl;
        }
    } else {
        cout << "Invalid car number." << endl;
    }
}

// Function to display the main menu
void displayMenu() {
    cout << "\nCar Rental System" << endl;
    cout << "1. Add Car" << endl;
    cout << "2. Display All Cars" << endl;
    cout << "3. Rent a Car" << endl;
    cout << "4. Return a Car" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    vector<Car> cars;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addCar(cars);
                break;
            case 2:
                displayCars(cars);
                break;
            case 3:
                rentCar(cars);
                break;
            case 4:
                returnCar(cars);
                break;
            case 5:
                cout << "Exiting the program. Thank you for using the Car Rental System!" << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
