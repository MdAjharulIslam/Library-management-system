#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>  
using namespace std;

class Book {
public:
    int bookID;
    string title;
    string writer;  
    string type; 
    bool available;
    long dueDate;
    int borrowedUserID;

    // Constructor for initializing all member variables
    Book(int id, const string& title, const string& writer, const string& type, bool available, long dueDate, int borrowedUserID)
        : bookID(id), title(title), writer(writer), type(type), available(available), dueDate(dueDate), borrowedUserID(borrowedUserID) {}

    // Default constructor (optional)
    Book() : bookID(0), available(true), dueDate(0), borrowedUserID(0) {}

    // Display function
    void display() const {
        cout << "Book ID: " << bookID << "\n";
        cout << "Title: " << title << "\n";
        cout << "Writer: " << writer << "\n";  
        cout << "Type: " << type << "\n";  
        cout << "Availability: " << (available ? "Available" : "Not Available") << "\n";
        cout << "Due Date: " << (dueDate == 0 ? "None" : to_string(dueDate)) << "\n";
        if (!available) {
            cout << "Borrowed By User ID: " << borrowedUserID << "\n";
        }
        cout << "--------------------------------------\n";
    }
};

#endif
