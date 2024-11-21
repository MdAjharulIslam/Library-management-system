#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Book.h"
#include "User.h"

using namespace std;  

// Functions for different tasks
void displayBooksTab();
void addBookTab();
void addUserTab();
void borrowBookTab();
void returnBookTab();
void searchBookTab();
void displayMenu();

// Display available options to the user
void displayMenu() {
    system("cls");  // Clear the screen for a fresh display

    cout << "\nLibrary Management System\n";
    cout << "1. Display All Books\n";
    cout << "2. Add a Book\n";
    cout << "3. Add a User\n";
    cout << "4. Borrow a Book\n";
    cout << "5. Return a Book\n";
    cout << "6. Search for a Book\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

// Main function
int main() {
    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                displayBooksTab();
                break;
            case 2:
                addBookTab();
                break;
            case 3:
                addUserTab();
                break;
            case 4:
                borrowBookTab();
                break;
            case 5:
                returnBookTab();
                break;
            case 6:
                searchBookTab();
                break;
            case 7:
                cout << "Exiting the system.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}

// Simulate "New Tab" for displaying all books
void displayBooksTab() {
    system("cls");  // Clear screen before displaying books
    cout << "\n--- Display All Books ---\n";
    // Display book list (from file or memory)
    ifstream file("books.txt");
    if (!file) {
        cout << "Could not open the file! Exiting...\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        int bookID;
        string title, writer, type;
        bool available;
        long dueDate;

        ss >> bookID;
        ss.ignore();
        getline(ss, title, ',');
        getline(ss, writer, ',');
        getline(ss, type, ',');
        ss >> available;
        ss.ignore();
        ss >> dueDate;

        Book book(bookID, title, writer, type, available, dueDate, 0); // BorrowedUserID is ignored here
        book.display();
    }

    file.close();
    system("pause");  // Wait for user input before returning to menu
}

// Simulate "New Tab" for adding a book
void addBookTab() {
    system("cls");  // Clear screen for fresh input
    cout << "\n--- Add a New Book ---\n";
    string title, writer, type;
    int bookID;
    bool available = true;
    long dueDate = 0;

    cout << "Enter Book ID: ";
    cin >> bookID;
    cin.ignore();  // Ignore the newline character left in the input buffer

    cout << "Enter Book Title: ";
    getline(cin, title);

    cout << "Enter Book Writer: ";
    getline(cin, writer);

    cout << "Enter Book Type: ";
    getline(cin, type);

    ofstream file("books.txt", ios::app);
    if (file.is_open()) {
        file << bookID << "," << title << "," << writer << "," << type << "," << available << "," << dueDate << "\n";
        file.close();
        cout << "Book added successfully!\n";
    } else {
        cout << "Unable to open file to save the book.\n";
    }
    system("pause");
}

// Simulate "New Tab" for adding a user
void addUserTab() {
    system("cls");
    cout << "\n--- Add a New User ---\n";
    string userName;
    int userID;
    bool isAdmin;

    cout << "Enter User ID: ";
    cin >> userID;
    cin.ignore();

    cout << "Enter User Name: ";
    getline(cin, userName);

    cout << "Is this user an Admin? (1 for Yes, 0 for No): ";
    cin >> isAdmin;

    ofstream file("users.txt", ios::app);
    if (file.is_open()) {
        file << userID << "," << userName << "," << isAdmin << "\n";
        file.close();
        cout << "User added successfully!\n";
    } else {
        cout << "Unable to open file to save the user.\n";
    }
    system("pause");
}

// Simulate "New Tab" for borrowing a book
void borrowBookTab() {
    system("cls");
    displayBooksTab();  // Show all books before borrowing

    int bookID;
    cout << "Enter Book ID to Borrow: ";
    cin >> bookID;

    ifstream file("books.txt");
    ofstream tempFile("temp.txt");

    if (!file || !tempFile) {
        cout << "Error opening file.\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        istringstream ss(line);
        int id;
        string title, writer, type;
        bool available;
        long dueDate;

        ss >> id;
        ss.ignore();
        getline(ss, title, ',');
        getline(ss, writer, ',');
        getline(ss, type, ',');
        ss >> available;
        ss.ignore();
        ss >> dueDate;

        if (id == bookID && available == true) {
            available = false; // Mark as borrowed
            dueDate = 1678090800;  // Example due date (Unix timestamp)
            found = true;
        }

        tempFile << id << "," << title << "," << writer << "," << type << "," << available << "," << dueDate << "\n";
    }

    file.close();
    tempFile.close();

    if (found) {
        remove("books.txt");
        rename("temp.txt", "books.txt");
        cout << "Book borrowed successfully.\n";
    } else {
        cout << "Book is either not available or does not exist.\n";
    }
    system("pause");
}

// Simulate "New Tab" for returning a book
void returnBookTab() {
    system("cls");
    int bookID;
    cout << "Enter Book ID to Return: ";
    cin >> bookID;

    ifstream file("books.txt");
    ofstream tempFile("temp.txt");

    if (!file || !tempFile) {
        cout << "Error opening file.\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        istringstream ss(line);
        int id;
        string title, writer, type;
        bool available;
        long dueDate;

        ss >> id;
        ss.ignore();
        getline(ss, title, ',');
        getline(ss, writer, ',');
        getline(ss, type, ',');
        ss >> available;
        ss.ignore();
        ss >> dueDate;

        if (id == bookID && !available) {
            available = true; 
            dueDate = 0;  
            found = true;
        }

        tempFile << id << "," << title << "," << writer << "," << type << "," << available << "," << dueDate << "\n";
    }

    file.close();
    tempFile.close();

    if (found) {
        remove("books.txt");
        rename("temp.txt", "books.txt");
        cout << "Book returned successfully.\n";
    } else {
        cout << "Book not found or not borrowed.\n";
    }
    system("pause");
}

// Simulate "New Tab" for searching a book
void searchBookTab() {
    system("cls");
    string keyword;
    cout << "Enter a keyword to search (title, writer, or type): ";
    cin.ignore();
    getline(cin, keyword);

    ifstream file("books.txt");
    if (!file) {
        cout << "Could not open the file! Exiting...\n";
        return;
    }

    bool found = false;
    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        int bookID;
        string title, writer, type;
        bool available;
        long dueDate;

        ss >> bookID;
        ss.ignore();
        getline(ss, title, ',');
        getline(ss, writer, ',');
        getline(ss, type, ',');
        ss >> available;
        ss.ignore();
        ss >> dueDate;

        if (title.find(keyword) != string::npos || writer.find(keyword) != string::npos || type.find(keyword) != string::npos) {
            cout << "Book Found: " << title << " by " << writer << " (" << type << ")\n";
            found = true;
        }
    }

    file.close();

    if (!found) {
        cout << "No books found matching the keyword.\n";
    }
    system("pause");
}
