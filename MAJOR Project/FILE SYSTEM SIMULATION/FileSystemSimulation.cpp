#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Structure to represent a file or directory
struct Node {
    string name;
    bool isFile; // true if it's a file, false if it's a directory
    vector<Node*> children; // Children nodes (only for directories)
    Node* parent; // Pointer to the parent directory (null for root)
};

// Function to create a new node (file or directory)
Node* createNode(const string& name, bool isFile, Node* parent) {
    Node* newNode = new Node;
    newNode->name = name;
    newNode->isFile = isFile;
    newNode->parent = parent;
    return newNode;
}

// Function to display the contents of the current directory
void listContents(Node* currentDir) {
    if (currentDir->children.empty()) {
        cout << "Directory is empty." << endl;
        return;
    }

    cout << "\nContents of " << currentDir->name << ":" << endl;
    for (const auto& child : currentDir->children) {
        cout << (child->isFile ? "[File] " : "[Dir] ") << child->name << endl;
    }
}

// Function to create a new directory
void createDirectory(Node* currentDir) {
    string dirName;
    cout << "Enter the name of the new directory: ";
    cin >> dirName;

    Node* newDir = createNode(dirName, false, currentDir);
    currentDir->children.push_back(newDir);
    cout << "Directory '" << dirName << "' created successfully." << endl;
}

// Function to create a new file
void createFile(Node* currentDir) {
    string fileName;
    cout << "Enter the name of the new file: ";
    cin >> fileName;

    Node* newFile = createNode(fileName, true, currentDir);
    currentDir->children.push_back(newFile);
    cout << "File '" << fileName << "' created successfully." << endl;
}

// Function to change to a child directory
void changeDirectory(Node*& currentDir) {
    string dirName;
    cout << "Enter the name of the directory to navigate into: ";
    cin >> dirName;

    for (auto& child : currentDir->children) {
        if (!child->isFile && child->name == dirName) {
            currentDir = child;
            cout << "Moved into directory: " << currentDir->name << endl;
            return;
        }
    }

    cout << "Directory not found." << endl;
}

// Function to move up to the parent directory
void moveToParentDirectory(Node*& currentDir) {
    if (currentDir->parent != nullptr) {
        currentDir = currentDir->parent;
        cout << "Moved up to parent directory: " << currentDir->name << endl;
    } else {
        cout << "Already at the root directory." << endl;
    }
}

// Function to display the menu
void displayMenu() {
    cout << "\nFile System Simulator" << endl;
    cout << "1. List Contents" << endl;
    cout << "2. Create Directory" << endl;
    cout << "3. Create File" << endl;
    cout << "4. Change Directory" << endl;
    cout << "5. Move to Parent Directory" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    // Create the root directory
    Node* root = createNode("root", false, nullptr);
    Node* currentDir = root; // Start at the root directory

    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                listContents(currentDir);
                break;
            case 2:
                createDirectory(currentDir);
                break;
            case 3:
                createFile(currentDir);
                break;
            case 4:
                changeDirectory(currentDir);
                break;
            case 5:
                moveToParentDirectory(currentDir);
                break;
            case 6:
                cout << "Exiting the File System Simulator." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 6);

    // Cleanup dynamically allocated memory
    delete root;

    return 0;
}
