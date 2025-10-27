#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "../Listing/Listing.h"
using namespace std;

struct User {
    int id;
    string name;
    string lastName;
    int age;
    string gender;
    string address;
    vector<Listing> listings;
};

#endif
