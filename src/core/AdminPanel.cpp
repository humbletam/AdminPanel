#include "AdminPanel.h"
#include <iostream>
#include <limits>

using namespace std;

void AdminPanel::run() {
    int choice;
    do {
        showMenu();
        cout << "Make a choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createUser(); break;
            case 2: deleteUser(); break;
            case 3: searchUser(); break;
            case 4: showAllUsers(); break;
            case 5: createListing(); break;
            case 6: deleteListing(); break;
            case 0: cout << "Logout...\n"; break;
            default: cout << "Wrong choice!\n";
        }
    } while (choice != 0);
}

void AdminPanel::showMenu() {
    cout << "\n==== Admin Panel ====\n";
    cout << "1. Create user\n";
    cout << "2. Delete user\n";
    cout << "3. Find your by ID\n";
    cout << "4. Show all users\n";
    cout << "5. Create listing for certain user\n";
    cout << "6. Remove listing for certain user\n";
    cout << "0. Logout\n";
}

void AdminPanel::createUser() {
    User u;
    u.id = nextUserId++;

    cout << "Name: ";
    cin >> u.name;
    cout << "Last-name ";
    cin >> u.lastName;
    cout << "Age: ";
    cin >> u.age;
    cout << "Gender: ";
    cin >> u.gender;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Address: ";
    getline(cin, u.address);

    users.push_back(u);
    cout << "✅ User created! User-ID: " << u.id << endl;
}

void AdminPanel::deleteUser() {
    int id;
    cout << "Remove user by ID: ";
    cin >> id;

    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->id == id) {
            users.erase(it);
            cout << "✅ User deleted successfully\n";
            return;
        }
    }
    cout << "❌ User not found\n";
}

void AdminPanel::searchUser() {
    int id;
    cout << "Enter user ID: ";
    cin >> id;

    for (auto& u : users) {
        if (u.id == id) {
            printUser(u);
            return;
        }
    }
    cout << "❌ User not found\n";
}

void AdminPanel::showAllUsers() {
    if (users.empty()) {
        cout << "Users List is empty\n";
        return;
    }

    for (auto& u : users) {
        printUser(u);
    }
}

void AdminPanel::printUser(const User& u) {
    cout << "\nID: " << u.id
         << "\nName: " << u.name
         << "\nLast-name: " << u.lastName
         << "\nAge: " << u.age
         << "\nGender: " << u.gender
         << "\nAddress: " << u.address
         << "\nListings:\n";

    if (u.listings.empty()) {
        cout << "  Listings not found\n";
    } else {
        for (auto& l : u.listings) {
            cout << "  [" << l.id << "] " << l.title
                 << " | " << l.description
                 << " | Price: " << l.price << endl;
        }
    }
    cout << "-------------------------\n";
}

void AdminPanel::createListing() {
    int userId;
    cout << "Enter user ID to create a listing: ";
    cin >> userId;

    for (auto& u : users) {
        if (u.id == userId) {
            Listing l;
            l.id = nextListingId++;

            cout << "Title: ";
            cin.ignore();
            getline(cin, l.title);
            cout << "Description: ";
            getline(cin, l.description);
            cout << "Price: ";
            cin >> l.price;

            u.listings.push_back(l);
            cout << "✅ Listing created! ID: " << l.id << endl;
            return;
        }
    }
    cout << "❌ User with such ID not found\n";
}

void AdminPanel::deleteListing() {
    int userId, listingId;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "For removal, enter listing ID: ";
    cin >> listingId;

    for (auto& u : users) {
        if (u.id == userId) {
            for (auto it = u.listings.begin(); it != u.listings.end(); ++it) {
                if (it->id == listingId) {
                    u.listings.erase(it);
                    cout << "✅ Listing deleted\n";
                    return;
                }
            }
            cout << "❌ Listing not found\n";
            return;
        }
    }
    cout << "❌ User not found\n";
}
