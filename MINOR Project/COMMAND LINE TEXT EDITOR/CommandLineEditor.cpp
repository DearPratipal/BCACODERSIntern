#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<string> buffer; // Stores the lines of the file being edited

// Function to display the buffer (text)
void displayBuffer() {
    cout << "---------- File Content ----------" << endl;
    for (int i = 0; i < buffer.size(); ++i) {
        cout << i + 1 << ": " << buffer[i] << endl;
    }
    cout << "----------------------------------" << endl;
}

// Function to open and read a file into the buffer
void openFile(const string &filename) {
    ifstream file(filename);
    if (!file) {
        cout << "File not found. Starting with an empty file." << endl;
        return;
    }

    string line;
    buffer.clear();
    while (getline(file, line)) {
        buffer.push_back(line);
    }
    file.close();
    cout << "File loaded successfully." << endl;
}

// Function to save the buffer to a file
void saveFile(const string &filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error saving file." << endl;
        return;
    }

    for (const string &line : buffer) {
        file << line << endl;
    }
    file.close();
    cout << "File saved successfully." << endl;
}

// Function to add a line to the buffer
void addLine() {
    cout << "Enter the line to add (type 'done' on a new line to stop):" << endl;
    string line;
    while (true) {
        getline(cin, line);
        if (line == "done") break;
        buffer.push_back(line);
    }
}

int main() {
    string filename;
    cout << "Enter the filename to open or create: ";
    cin >> filename;
    cin.ignore(); // Ignore the newline character left in the input buffer

    openFile(filename);
    displayBuffer();

    char choice;
    do {
        cout << "\nOptions:\n";
        cout << "1. Display file content\n";
        cout << "2. Add line\n";
        cout << "3. Save file\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore the newline character after the choice input

        switch (choice) {
            case '1':
                displayBuffer();
                break;
            case '2':
                addLine();
                break;
            case '3':
                saveFile(filename);
                break;
            case '4':
                cout << "Exiting editor." << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    } while (choice != '4');

    return 0;
}
