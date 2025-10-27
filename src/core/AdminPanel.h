#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <vector>
#include "../models/User/User.h"

class AdminPanel {
private:
    std::vector<User> users;
    int nextUserId = 1;
    int nextListingId = 1;

public:
    void run();

private:
    void showMenu();
    void createUser();
    void deleteUser();
    void searchUser();
    void showAllUsers();
    void printUser(const User& u);
    void createListing();
    void deleteListing();
};

#endif
