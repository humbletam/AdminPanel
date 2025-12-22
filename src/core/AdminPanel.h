#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <vector>
#include "../models/User/User.h"
#include "repository/IUserRepository.h"
#include "exceptions/DomainExceptions.h"

class AdminPanel {
private:
    IUserRepository* userRepo;

public:
    AdminPanel();
    ~AdminPanel();

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
