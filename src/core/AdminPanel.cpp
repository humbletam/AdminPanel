#include "AdminPanel.h"
#include <iostream>
#include <limits>
#include "repository/InMemoryUserRepository.h"

using namespace std;

AdminPanel::AdminPanel() {
    userRepo = new InMemoryUserRepository();
}

AdminPanel::~AdminPanel() {
    delete userRepo;
}

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
    cout << "3. Find user by ID\n";
    cout << "4. Show all users\n";
    cout << "5. Create listing for certain user\n";
    cout << "6. Remove listing for certain user\n";
    cout << "0. Logout\n";
}

void AdminPanel::createUser() {
    User u{};

    cout << "Name: ";
    cin >> u.name;
    cout << "Last-name: ";
    cin >> u.lastName;
    cout << "Age: ";
    cin >> u.age;
    cout << "Gender: ";
    cin >> u.gender;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Address: ";
    getline(cin, u.address);

    try {
        const User& created = userRepo->createUser(u);
        cout << "✅ User created! User-ID: " << created.id << endl;
    } catch (const ValidationException& ex) {
        cout << "❌ Validation error: " << ex.what() << "\n";
    } catch (const DuplicateEntryException& ex) {
        cout << "❌ Duplicate: " << ex.what() << "\n";
    } catch (const std::exception& ex) {
        cout << "❌ Error: " << ex.what() << "\n";
    }
}

void AdminPanel::deleteUser() {
    int id;
    cout << "Remove user by ID: ";
    cin >> id;

    try {
        userRepo->deleteUserById(id);
        cout << "✅ User deleted successfully\n";
    } catch (const NotFoundException& ex) {
        cout << "❌ " << ex.what() << "\n";
    }
}

void AdminPanel::searchUser() {
    int id;
    cout << "Enter user ID: ";
    cin >> id;

    User* u = userRepo->findUserById(id);
    if (u) {
        printUser(*u);
    } else {
        cout << "❌ User not found\n";
    }
}

void AdminPanel::showAllUsers() {
    const auto& users = userRepo->getAllUsers();
    if (users.empty()) {
        cout << "Users List is empty\n";
        return;
    }

    for (const auto& u : users) {
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

    Listing l{};
    cout << "Title: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, l.title);
    cout << "Description: ";
    getline(cin, l.description);
    cout << "Price: ";
    cin >> l.price;

    try {
        const Listing& created = userRepo->addListingToUser(userId, l);
        cout << "✅ Listing created! ID: " << created.id << endl;
    } catch (const NotFoundException& ex) {
        cout << "❌ " << ex.what() << "\n";
    } catch (const ValidationException& ex) {
        cout << "❌ Validation error: " << ex.what() << "\n";
    } catch (const DuplicateEntryException& ex) {
        cout << "❌ Duplicate: " << ex.what() << "\n";
    }
}

void AdminPanel::deleteListing() {
    int userId, listingId;
    cout << "Enter user ID: ";
    cin >> userId;
    cout << "For removal, enter listing ID: ";
    cin >> listingId;

    try {
        userRepo->deleteListingFromUser(userId, listingId);
        cout << "✅ Listing deleted\n";
    } catch (const NotFoundException& ex) {
        cout << "❌ " << ex.what() << "\n";
    }
}
