#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>  // Required for printing
using namespace std;

class User {
public:
    int userID;
    string userName;
    bool isAdmin;

    // Constructor for initializing all member variables
    User(int id, const string& userName, bool isAdmin)
        : userID(id), userName(userName), isAdmin(isAdmin) {}

    // Default constructor (optional)
    User() : userID(0), userName(""), isAdmin(false) {}

    // Display function for user details
    void display() const {
        cout << "User ID: " << userID << "\n";
        cout << "Name: " << userName << "\n";
        cout << "Admin: " << (isAdmin ? "Yes" : "No") << "\n";
        cout << "--------------------------------------\n";
    }
};

#endif
